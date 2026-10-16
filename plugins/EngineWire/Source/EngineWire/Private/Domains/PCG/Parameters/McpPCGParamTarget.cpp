#include "Domains/PCG/Parameters/McpPCGParameters.h"
#include "Foundation/Reflection/McpPropertyReflection.h"

#if MCP_HAS_PCG_PARAMETERS
namespace McpPCGHandlers
{
bool ResolvePCGParameterTarget(const TSharedPtr<FJsonObject>& Payload, FPCGParameterTarget& Target, FString& OutError)
{
    Target.Scope = GetJsonStringField(Payload, TEXT("target"), TEXT("graph"));
    if ((Target.Scope != TEXT("graph") && Payload->HasField(TEXT("graphPath"))) ||
        (Target.Scope != TEXT("graphInstance") && Payload->HasField(TEXT("graphInstancePath"))) ||
        (Target.Scope != TEXT("component") && Payload->HasField(TEXT("componentPath"))))
    {
        OutError = TEXT("Supply only the asset/component path appropriate to the explicit parameter target.");
        return false;
    }
    FString Resolved;
    if (Target.Scope == TEXT("graph"))
    {
        Target.Interface = LoadPCGAsset<UPCGGraph>(GetJsonStringField(Payload, TEXT("graphPath")), TEXT("PCG graph"), Resolved, OutError);
    }
    else if (Target.Scope == TEXT("graphInstance"))
    {
        Target.Interface = LoadPCGAsset<UPCGGraphInstance>(GetJsonStringField(Payload, TEXT("graphInstancePath")), TEXT("PCG graph instance"), Resolved, OutError);
    }
    else if (Target.Scope == TEXT("component"))
    {
        UWorld* World = McpHandlerUtils::GetEditorWorld();
        AActor* Actor = nullptr;
        const FString Selector = GetJsonStringField(Payload, TEXT("componentPath"));
        if (!World || !Selector.StartsWith(TEXT("/")))
        {
            OutError = TEXT("Component parameters require the absolute componentPath returned by PCG component discovery or execution.");
            return false;
        }
        Target.Component = FindPCGComponent(World, FString(), Selector, Actor);
        if (!Target.Component || !Target.Component->GetPathName().Equals(Selector, ESearchCase::IgnoreCase))
        {
            OutError = TEXT("componentPath did not resolve exactly to a current editor-world PCG component.");
            return false;
        }
        Target.Interface = Target.Component->GetGraphInstance();
    }
    else
    {
        OutError = TEXT("Parameter target must be graph, graphInstance or component.");
        return false;
    }
    Target.Graph = Target.Interface ? Target.Interface->GetGraph() : nullptr;
    if (!Target.Interface || !Target.Graph || !Target.Interface->GetUserParametersStruct())
    {
        if (OutError.IsEmpty()) OutError = TEXT("Could not resolve the PCG parameter target or its parent graph.");
        return false;
    }
    if (Target.Scope != TEXT("graph") && Target.Interface->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
    {
        OutError = TEXT("Instance parameter edits cannot target a CDO or archetype.");
        return false;
    }
    return true;
}

TArray<TSharedPtr<FJsonValue>> ReadPCGParameters(const FPCGParameterTarget& Target)
{
    TArray<TSharedPtr<FJsonValue>> Result;
    const FInstancedPropertyBag* Bag = Target.Interface->GetUserParametersStruct();
    const FInstancedPropertyBag* Defaults = Target.Graph->GetUserParametersStruct();
    if (!Bag || !Bag->GetPropertyBagStruct()) return Result;
    const UPCGGraphInstance* Instance = Cast<UPCGGraphInstance>(Target.Interface);
    for (const FPropertyBagPropertyDesc& Desc : Bag->GetPropertyBagStruct()->GetPropertyDescs())
    {
        auto Row = MakeShared<FJsonObject>();
        Row->SetStringField(TEXT("name"), Desc.Name.ToString());
        Row->SetStringField(TEXT("id"), Desc.ID.ToString(EGuidFormats::DigitsWithHyphens));
        Row->SetStringField(TEXT("type"), StaticEnum<EPropertyBagPropertyType>()->GetNameStringByValue(static_cast<int64>(Desc.ValueType)));
        Row->SetStringField(TEXT("container"), Desc.ContainerTypes.IsEmpty() ? TEXT("none") : Desc.ContainerTypes.GetFirstContainerType() == EPropertyBagContainerType::Array ? TEXT("array") : TEXT("unsupported"));
        if (Desc.ValueTypeObject) Row->SetStringField(TEXT("typeObject"), Desc.ValueTypeObject->GetPathName());
        if (Desc.CachedProperty)
        {
            Row->SetField(TEXT("value"), McpPropertyReflection::ExportPropertyToJsonValueOrText(const_cast<uint8*>(Bag->GetValue().GetMemory()), const_cast<FProperty*>(Desc.CachedProperty)));
            Row->SetBoolField(TEXT("overridden"), Instance && Instance->IsPropertyOverridden(Desc.CachedProperty));
        }
        const FPropertyBagPropertyDesc* Default = Defaults ? Defaults->FindPropertyDescByID(Desc.ID) : nullptr;
        if (Default && Default->CachedProperty)
        {
            Row->SetField(TEXT("defaultValue"), McpPropertyReflection::ExportPropertyToJsonValueOrText(const_cast<uint8*>(Defaults->GetValue().GetMemory()), const_cast<FProperty*>(Default->CachedProperty)));
        }
        Result.Add(MakeShared<FJsonValueObject>(Row));
    }
    return Result;
}
}
#endif
