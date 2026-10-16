#include "Domains/PCG/Discovery/McpPCGRead.h"
#include "Foundation/Reflection/McpPropertyReflection.h"
#include "MCP/Gateway/McpNativeGatewayCanonicalJson.h"
#include "Misc/SecureHash.h"
#include "UObject/UObjectHash.h"
#include "EdGraph/EdGraph.h"
#include "Domains/PCG/Editor/McpPCGEditor.h"

#if MCP_HAS_PCG
namespace McpPCGHandlers
{
namespace
{
TSharedPtr<FJsonObject> ReadAuthoredProperties(UObject* Object)
{
    auto Result = MakeShared<FJsonObject>();
    if (!Object) return Result;
    for (TFieldIterator<FProperty> It(Object->GetClass()); It; ++It)
    {
        if (!It->HasAnyPropertyFlags(CPF_Edit) || It->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated)) continue;
        Result->SetField(It->GetName(), McpPropertyReflection::ExportPropertyToJsonValueOrText(Object, *It));
    }
    return Result;
}

TArray<TSharedPtr<FJsonValue>> ReadPins(const TArray<TObjectPtr<UPCGPin>>& Pins)
{
    TArray<TSharedPtr<FJsonValue>> Result;
    for (UPCGPin* Pin : Pins)
    {
        if (!Pin) continue;
        auto Item = MakeShared<FJsonObject>();
        Item->SetStringField(TEXT("label"), Pin->Properties.Label.ToString());
        Item->SetBoolField(TEXT("allowsMultipleConnections"), Pin->AllowsMultipleConnections());
        Item->SetBoolField(TEXT("allowsMultipleData"), Pin->AllowsMultipleData());
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 7)
        Item->SetStringField(TEXT("currentTypes"), Pin->GetCurrentTypesID().ToString());
#else
        Item->SetNumberField(TEXT("currentTypes"), static_cast<uint32>(Pin->GetCurrentTypes()));
#endif
        Item->SetField(TEXT("properties"), McpPropertyReflection::ExportPropertyToJsonValueOrText(
            Pin, FindFProperty<FProperty>(Pin->GetClass(), TEXT("Properties"))));
        Result.Add(MakeShared<FJsonValueObject>(Item));
    }
    return Result;
}
}

UEdGraph* FindExistingPCGEditorGraph(UPCGGraph* Graph, bool& bOutAmbiguous)
{
    bOutAmbiguous = false;
    TArray<UObject*> Children;
    GetObjectsWithOuter(Graph, Children, false);
    UEdGraph* Result = nullptr;
    for (UObject* Child : Children)
    {
        UEdGraph* Candidate = Cast<UEdGraph>(Child);
        if (!IsValid(Candidate) || Candidate->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed) ||
            Candidate->GetClass()->GetFName() != FName(TEXT("PCGEditorGraph"))) continue;
        if (Result)
        {
            bOutAmbiguous = true;
            return nullptr;
        }
        Result = Candidate;
    }
    return Result;
}

TSharedPtr<FJsonObject> ReadPCGSettings(UObject* Settings)
{
    auto Result = ReadAuthoredProperties(Settings);
    if (!Settings) return Result;
    Result->SetStringField(TEXT("$class"), Settings->GetClass()->GetPathName());
    TArray<UObject*> Children;
    GetObjectsWithOuter(Settings, Children, true);
    Children.Sort([](const UObject& A, const UObject& B) { return A.GetPathName().Compare(B.GetPathName(), ESearchCase::CaseSensitive) < 0; });
    auto Owned = MakeShared<FJsonObject>();
    for (UObject* Child : Children)
    {
        if (!Child || Child->HasAnyFlags(RF_ClassDefaultObject)) continue;
        auto Data = ReadAuthoredProperties(Child);
        Data->SetStringField(TEXT("$class"), Child->GetClass()->GetPathName());
        Owned->SetObjectField(Child->GetPathName(Settings), Data);
    }
    Result->SetObjectField(TEXT("$ownedObjects"), Owned);
    return Result;
}

TSharedPtr<FJsonObject> ReadPCGNode(UPCGGraph* Graph, UPCGNode* Node, bool bIncludeSettings)
{
    auto Result = BuildNodeResult(Graph, Node, Graph->GetPathName());
    int32 X = 0, Y = 0;
    Node->GetNodePosition(X, Y);
    Result->SetNumberField(TEXT("x"), X);
    Result->SetNumberField(TEXT("y"), Y);
    Result->SetBoolField(TEXT("input"), Node == Graph->GetInputNode());
    Result->SetBoolField(TEXT("output"), Node == Graph->GetOutputNode());
    Result->SetBoolField(TEXT("hidden"), IsPCGNodeHidden(Node));
    Result->SetObjectField(TEXT("editorMetadata"), McpPropertyReflection::ExportPropertiesToJson(Node,
        {FName(TEXT("NodeComment")), FName(TEXT("NodeTitleColor")), FName(TEXT("bCommentBubblePinned")), FName(TEXT("bCommentBubbleVisible"))}));
    Result->SetArrayField(TEXT("inputPins"), ReadPins(Node->GetInputPins()));
    Result->SetArrayField(TEXT("outputPins"), ReadPins(Node->GetOutputPins()));
    if (UPCGSettings* Settings = Node->GetSettings())
    {
        Result->SetStringField(TEXT("settingsClass"), Settings->GetClass()->GetPathName());
        Result->SetObjectField(TEXT("bindings"), McpPropertyReflection::ExportPropertiesToJson(Settings,
            {FName(TEXT("PropertyGuid")), FName(TEXT("PropertyName")), FName(TEXT("PropertyPath"))}));
        if (bIncludeSettings) Result->SetObjectField(TEXT("settings"), ReadPCGSettings(Settings));
    }
    return Result;
}

TSharedPtr<FJsonObject> ReadPCGGraph(UPCGGraph* Graph, bool bIncludeSettings)
{
    auto Result = MakeShared<FJsonObject>();
    TArray<UPCGNode*> Nodes;
    if (Graph->GetInputNode()) Nodes.Add(Graph->GetInputNode());
    for (UPCGNode* Node : Graph->GetNodes()) if (Node) Nodes.AddUnique(Node);
    if (Graph->GetOutputNode()) Nodes.AddUnique(Graph->GetOutputNode());
    TArray<TSharedPtr<FJsonValue>> NodeData, Edges;
    for (UPCGNode* Node : Nodes)
    {
        NodeData.Add(MakeShared<FJsonValueObject>(ReadPCGNode(Graph, Node, bIncludeSettings)));
        for (UPCGPin* Pin : Node->GetOutputPins())
        {
            if (!Pin) continue;
            for (UPCGEdge* Edge : Pin->Edges)
            {
                UPCGPin* Target = Edge && Edge->IsValid() ? Edge->GetOtherPin(Pin) : nullptr;
                if (!Target || !Target->Node) continue;
                auto Data = MakeShared<FJsonObject>();
                Data->SetStringField(TEXT("sourceNodeId"), Node->GetName());
                Data->SetStringField(TEXT("sourcePin"), Pin->Properties.Label.ToString());
                Data->SetStringField(TEXT("targetNodeId"), Target->Node->GetName());
                Data->SetStringField(TEXT("targetPin"), Target->Properties.Label.ToString());
                Edges.Add(MakeShared<FJsonValueObject>(Data));
            }
        }
    }
    Result->SetArrayField(TEXT("nodes"), NodeData);
    Result->SetArrayField(TEXT("edges"), Edges);
    Result->SetObjectField(TEXT("graphSettings"), ReadAuthoredProperties(Graph));
    Result->SetObjectField(TEXT("editorData"), McpPropertyReflection::ExportPropertiesToJson(Graph,
        {FName(TEXT("CommentNodes")), FName(TEXT("ExtraEditorNodes"))}));
    TArray<TSharedPtr<FJsonValue>> Notes;
    const auto EditorSnapshot = ReadPCGEditorGraphSnapshot(Graph);
    for (const auto& Value : EditorSnapshot->GetArrayField(TEXT("nodes")))
    {
        if (Value->AsObject()->HasField(TEXT("extraNode"))) Notes.Add(Value);
    }
    Result->SetArrayField(TEXT("liveEditorNotes"), Notes);
    return Result;
}

FString GetPCGGraphRevision(UPCGGraph* Graph)
{
    if (!Graph) return FString();
    auto State = ReadPCGGraph(Graph, true);
    auto Exact = MakeShared<FJsonObject>();
    TArray<UObject*> Objects;
    GetObjectsWithOuter(Graph, Objects, true);
    Objects.Insert(Graph, 0);
    const TArray<FName> ExtraProperties = { FName(TEXT("PositionX")), FName(TEXT("PositionY")), FName(TEXT("NodeTitle")),
        FName(TEXT("NodeTitleColor")), FName(TEXT("NodeComment")), FName(TEXT("CommentNodes")), FName(TEXT("bHidden")),
        FName(TEXT("bCommentBubblePinned")), FName(TEXT("bCommentBubbleVisible")), FName(TEXT("UserParameters")) };
    bool bAmbiguous = false;
    UEdGraph* Editor = FindExistingPCGEditorGraph(Graph, bAmbiguous);
    if (bAmbiguous) return FString();
    for (UObject* Object : Objects)
    {
        if (!Object || Object->HasAnyFlags(RF_ClassDefaultObject) || (Editor && (Object == Editor || Object->IsIn(Editor)))) continue;
        const FString Hash = McpPropertyReflection::FingerprintEditableProperties(Object, ExtraProperties);
        if (Hash.IsEmpty()) return FString();
        Exact->SetStringField(Object == Graph ? TEXT("$graph") : Object->GetPathName(Graph), Hash);
    }
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
    const FInstancedPropertyBag* Bag = Graph->GetUserParametersStruct();
    if (Bag && Bag->GetPropertyBagStruct())
    {
        for (const FPropertyBagPropertyDesc& Desc : Bag->GetPropertyBagStruct()->GetPropertyDescs())
        {
            if (!Desc.CachedProperty) continue;
            const FString Hash = McpPropertyReflection::FingerprintReflectedValue(Desc.CachedProperty,
                const_cast<uint8*>(Bag->GetValue().GetMemory()));
            if (Hash.IsEmpty()) return FString();
            Exact->SetStringField(TEXT("$parameter:") + Desc.ID.ToString(), Hash);
        }
    }
#endif
    State->SetObjectField(TEXT("exactAuthoredState"), Exact);
    FString Json;
    if (!McpCanonicalJsonObject(State, Json, true)) return FString();
    return FMD5::HashAnsiString(*Json);
}

bool CheckPCGGraphRevision(UPCGGraph* Graph, const TSharedPtr<FJsonObject>& Payload, FString& OutError)
{
    FString Expected;
    if (Payload->TryGetStringField(TEXT("expectedGraphRevision"), Expected) && Expected != GetPCGGraphRevision(Graph))
    {
        OutError = TEXT("The PCG graph changed since it was read; read it again before editing.");
        return false;
    }
    return true;
}
}
#endif
