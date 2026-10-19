#include "Misc/AutomationTest.h"
#include "Domains/PCG/Parameters/McpPCGParameters.h"
#include "UObject/StrongObjectPtr.h"

#if WITH_DEV_AUTOMATION_TESTS && MCP_HAS_PCG_PARAMETERS
namespace
{
bool CheckIntegerWireValue(FAutomationTestBase* Test, const TSharedPtr<FJsonValue>& Actual, int64 Expected)
{
    constexpr int64 MaxSafeInteger = 9007199254740991LL;
    const bool bString = Expected < -MaxSafeInteger || Expected > MaxSafeInteger;
    if (!Test->TestTrue(TEXT("Integer JSON type preserves exact values"), Actual.IsValid() &&
        Actual->Type == (bString ? EJson::String : EJson::Number))) return false;
    return bString ? Test->TestEqual(TEXT("Large integer is exact decimal text"), Actual->AsString(), LexToString(Expected)) :
        Test->TestEqual(TEXT("Safe integer stays a JSON number"), Actual->AsNumber(), static_cast<double>(Expected));
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMcpPCGIntegerReadbackTest, "EngineWire.PCG.Int64ReadbackPreservesExactValues",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FMcpPCGIntegerReadbackTest::RunTest(const FString& Parameters)
{
    using namespace McpPCGHandlers;
    TStrongObjectPtr<UPCGGraph> Graph(NewObject<UPCGGraph>(GetTransientPackage()));
    FPropertyBagPropertyDesc Scalar(FName(TEXT("Exact")), EPropertyBagPropertyType::Int64);
    FPropertyBagPropertyDesc Array(FName(TEXT("ExactArray")), EPropertyBagContainerType::Array, EPropertyBagPropertyType::Int64);
    Scalar.ID = FGuid::NewGuid();
    Array.ID = FGuid::NewGuid();
    if (!TestTrue(TEXT("Owned integer schema created"), Graph->AddUserParameters({Scalar, Array}) == EPropertyBagAlterationResult::Success)) return false;
    FPCGParameterTarget Target;
    Target.Interface = Graph.Get();
    Target.Graph = Graph.Get();
    Target.Scope = TEXT("graph");
    const TArray<int64> Values = {0, 9007199254740991LL, -9007199254740991LL, 9007199254740993LL,
        -9007199254740993LL, MIN_int64, MAX_int64};
    FString Error;
    FInstancedPropertyBag Staged;
    TArray<TSharedPtr<FJsonValue>> JsonValues;
    for (int64 Expected : Values)
    {
        auto Input = MakeShared<FJsonValueString>(LexToString(Expected));
        JsonValues.Add(Input);
        if (!TestTrue(TEXT("Exact integer string staged"), StagePCGParameterValue(*Graph->GetUserParametersStruct(), TEXT("Exact"), Input, Staged, Error)) ||
            !TestTrue(TEXT("Exact integer committed"), CommitPCGParameterValue(Graph.Get(), TEXT("Exact"), Staged, Error))) return false;
        const auto* Bag = Graph->GetUserParametersStruct();
        const auto* Property = CastFieldChecked<FInt64Property>(Bag->FindPropertyDescByName(TEXT("Exact"))->CachedProperty);
        TestEqual(TEXT("Native storage retains every integer bit"), Property->GetPropertyValue_InContainer(Bag->GetValue().GetMemory()), Expected);
        const auto Rows = ReadPCGParameters(Target, TEXT("Exact"));
        if (!TestEqual(TEXT("Scalar filtered row"), Rows.Num(), 1)) return false;
        CheckIntegerWireValue(this, Rows[0]->AsObject()->TryGetField(TEXT("value")), Expected);
        CheckIntegerWireValue(this, Rows[0]->AsObject()->TryGetField(TEXT("defaultValue")), Expected);
    }
    if (!TestTrue(TEXT("Integer array staged without floating conversion"), StagePCGParameterValue(*Graph->GetUserParametersStruct(),
        TEXT("ExactArray"), MakeShared<FJsonValueArray>(JsonValues), Staged, Error)) ||
        !TestTrue(TEXT("Integer array committed"), CommitPCGParameterValue(Graph.Get(), TEXT("ExactArray"), Staged, Error))) return false;
    const auto Rows = ReadPCGParameters(Target, TEXT("ExactArray"));
    if (!TestEqual(TEXT("Array filtered row"), Rows.Num(), 1)) return false;
    for (const TCHAR* Field : {TEXT("value"), TEXT("defaultValue")})
    {
        const auto& Items = Rows[0]->AsObject()->GetArrayField(Field);
        if (!TestEqual(TEXT("All integer array elements exported"), Items.Num(), Values.Num())) return false;
        for (int32 Index = 0; Index < Values.Num(); ++Index) CheckIntegerWireValue(this, Items[Index], Values[Index]);
    }
    TStrongObjectPtr<UPCGGraphInstance> Instance(NewObject<UPCGGraphInstance>(GetTransientPackage()));
    Instance->SetGraph(Graph.Get());
    TStrongObjectPtr<UPCGComponent> Component(NewObject<UPCGComponent>(GetTransientPackage()));
    Component->SetGraphLocal(Graph.Get());
    for (UPCGGraphInstance* Override : {Instance.Get(), Component->GetGraphInstance()})
    {
        if (!TestNotNull(TEXT("Owned override instance"), Override)) return false;
        const auto* Desc = Override->GetUserParametersStruct()->FindPropertyDescByName(TEXT("Exact"));
        if (!TestNotNull(TEXT("Inherited integer descriptor"), Desc)) return false;
        if (!TestTrue(TEXT("Instance integer override staged"), StagePCGParameterValue(*Override->GetUserParametersStruct(), TEXT("Exact"),
            MakeShared<FJsonValueString>(LexToString(static_cast<int64>(MIN_int64))), Staged, Error))) return false;
        Override->UpdatePropertyOverride(Desc->CachedProperty, true);
        if (!TestTrue(TEXT("Instance integer override committed"), CommitPCGParameterValue(Override, TEXT("Exact"), Staged, Error))) return false;
        Target.Interface = Override;
        Target.Component = Override == Component->GetGraphInstance() ? Component.Get() : nullptr;
        Target.Scope = Target.Component ? TEXT("component") : TEXT("graphInstance");
        auto OverrideRows = ReadPCGParameters(Target, TEXT("Exact"));
        if (!TestEqual(TEXT("Override filtered row"), OverrideRows.Num(), 1)) return false;
        CheckIntegerWireValue(this, OverrideRows[0]->AsObject()->TryGetField(TEXT("value")), MIN_int64);
        CheckIntegerWireValue(this, OverrideRows[0]->AsObject()->TryGetField(TEXT("defaultValue")), MAX_int64);
        TestTrue(TEXT("Exact integer remains an independent override"), OverrideRows[0]->AsObject()->GetBoolField(TEXT("overridden")));
        Override->ResetPropertyToDefault(Desc->CachedProperty);
        Override->UpdatePropertyOverride(Desc->CachedProperty, false);
        OverrideRows = ReadPCGParameters(Target, TEXT("Exact"));
        CheckIntegerWireValue(this, OverrideRows[0]->AsObject()->TryGetField(TEXT("value")), MAX_int64);
        TestFalse(TEXT("Reset resumes exact default inheritance"), OverrideRows[0]->AsObject()->GetBoolField(TEXT("overridden")));
    }
    return true;
}
#endif
