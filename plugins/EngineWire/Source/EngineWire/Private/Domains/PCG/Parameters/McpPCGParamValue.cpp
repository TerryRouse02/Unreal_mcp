#include "Domains/PCG/Parameters/McpPCGParameters.h"
#include "Foundation/BridgeHelpers/Properties/McpPropApply.h"

#if MCP_HAS_PCG_PARAMETERS
namespace McpPCGHandlers
{
bool StagePCGParameterValue(const FInstancedPropertyBag& Source, FName Name, const TSharedPtr<FJsonValue>& Value,
    FInstancedPropertyBag& OutBag, FString& OutError)
{
    OutBag = Source;
    const FPropertyBagPropertyDesc* Desc = OutBag.FindPropertyDescByName(Name);
    if (!Desc || !Desc->CachedProperty)
    {
        OutError = TEXT("The named graph parameter does not exist.");
        return false;
    }
    if (Desc->ValueType == EPropertyBagPropertyType::Text || Desc->ValueType == EPropertyBagPropertyType::UInt32 ||
        Desc->ValueType == EPropertyBagPropertyType::UInt64 ||
        (Desc->ValueType == EPropertyBagPropertyType::Struct && Desc->ValueTypeObject != TBaseStructure<FVector>::Get() &&
         Desc->ValueTypeObject != TBaseStructure<FRotator>::Get() && Desc->ValueTypeObject != TBaseStructure<FTransform>::Get()))
    {
        OutError = TEXT("This existing parameter type is not supported by the typed PCG setter.");
        return false;
    }
    if (Desc->ContainerTypes.Num() > 1 || (!Desc->ContainerTypes.IsEmpty() && Desc->ContainerTypes.GetFirstContainerType() != EPropertyBagContainerType::Array))
    {
        OutError = TEXT("Only scalar and single-array graph parameters are supported.");
        return false;
    }
    if (Value.IsValid() && Value->Type == EJson::Array && Value->AsArray().Num() > 10000)
    {
        OutError = TEXT("Parameter arrays are limited to 10000 elements per edit.");
        return false;
    }
    if (const FArrayProperty* Array = CastField<FArrayProperty>(Desc->CachedProperty))
    {
        if (!Value.IsValid() || Value->Type != EJson::Array)
        {
            OutError = TEXT("An array parameter requires a JSON array value.");
            return false;
        }
        FScriptArrayHelper Values(Array, Array->ContainerPtrToValuePtr<void>(OutBag.GetMutableValue().GetMemory()));
        Values.EmptyValues();
        Values.AddValues(Value->AsArray().Num());
        for (int32 Index = 0; Index < Value->AsArray().Num(); ++Index)
        {
            if (!::ApplyJsonValueToProperty(Values.GetRawPtr(Index), Array->Inner, Value->AsArray()[Index], OutError)) return false;
        }
        return true;
    }
    return ::ApplyJsonValueToProperty(OutBag.GetMutableValue().GetMemory(), const_cast<FProperty*>(Desc->CachedProperty), Value, OutError);
}

bool CommitPCGParameterValue(UPCGGraphInterface* Target, FName Name, const FInstancedPropertyBag& Source, FString& OutError)
{
    const FPropertyBagPropertyDesc* Desc = Source.FindPropertyDescByName(Name);
    if (!Target || !Desc || !Desc->CachedProperty) return false;
    const FProperty* Property = Desc->CachedProperty;
    const void* Container = Source.GetValue().GetMemory();
    EPropertyBagResult Status = EPropertyBagResult::TypeMismatch;
    if (const FArrayProperty* Array = CastField<FArrayProperty>(Property))
    {
        FScriptArrayHelper Values(Array, Array->ContainerPtrToValuePtr<void>(Container));
        const bool bChanged = Target->UpdateArrayGraphParameter(Name, [&Values, Array](FPropertyBagArrayRef& Destination)
        {
            Destination.EmptyValues();
            Destination.AddValues(Values.Num());
            for (int32 Index = 0; Index < Values.Num(); ++Index) Array->Inner->CopyCompleteValue(Destination.GetRawPtr(Index), Values.GetRawPtr(Index));
            return true;
        });
        if (bChanged) return true;
    }
    else if (Desc->ValueType == EPropertyBagPropertyType::Enum)
    {
        const FEnumProperty* Enum = CastField<FEnumProperty>(Property);
        if (Enum) Status = Target->SetGraphParameter(Name,
            Enum->GetUnderlyingProperty()->GetUnsignedIntPropertyValue(Enum->ContainerPtrToValuePtr<void>(Container)), Enum->GetEnum());
    }
    else if (const FBoolProperty* Bool = CastField<FBoolProperty>(Property)) Status = Target->SetGraphParameter(Name, Bool->GetPropertyValue_InContainer(Container));
    else if (const FByteProperty* Byte = CastField<FByteProperty>(Property)) Status = Target->SetGraphParameter(Name, Byte->GetPropertyValue_InContainer(Container));
    else if (const FIntProperty* Int = CastField<FIntProperty>(Property)) Status = Target->SetGraphParameter(Name, Int->GetPropertyValue_InContainer(Container));
    else if (const FInt64Property* Integer64 = CastField<FInt64Property>(Property)) Status = Target->SetGraphParameter(Name, Integer64->GetPropertyValue_InContainer(Container));
    else if (const FFloatProperty* Float = CastField<FFloatProperty>(Property)) Status = Target->SetGraphParameter(Name, Float->GetPropertyValue_InContainer(Container));
    else if (const FDoubleProperty* Double = CastField<FDoubleProperty>(Property)) Status = Target->SetGraphParameter(Name, Double->GetPropertyValue_InContainer(Container));
    else if (const FNameProperty* NameProperty = CastField<FNameProperty>(Property)) Status = Target->SetGraphParameter(Name, NameProperty->GetPropertyValue_InContainer(Container));
    else if (const FStrProperty* String = CastField<FStrProperty>(Property)) Status = Target->SetGraphParameter(Name, String->GetPropertyValue_InContainer(Container));
    else if (const FSoftObjectProperty* SoftObject = CastField<FSoftObjectProperty>(Property))
    {
        const FSoftObjectPath Path = SoftObject->GetPropertyValue_InContainer(Container).ToSoftObjectPath();
        Status = Desc->ValueType == EPropertyBagPropertyType::SoftClass ? Target->SetGraphParameter(Name, TSoftClassPtr<UObject>(Path)) :
            Target->SetGraphParameter(Name, TSoftObjectPtr<UObject>(Path));
    }
    else if (const FClassProperty* ClassProperty = CastField<FClassProperty>(Property)) Status = Target->SetGraphParameter(Name, Cast<UClass>(ClassProperty->GetObjectPropertyValue_InContainer(Container)));
    else if (const FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property)) Status = Target->SetGraphParameter(Name, ObjectProperty->GetObjectPropertyValue_InContainer(Container));
    else if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
    {
        if (StructProperty->Struct == TBaseStructure<FVector>::Get()) Status = Target->SetGraphParameter(Name, *StructProperty->ContainerPtrToValuePtr<FVector>(Container));
        else if (StructProperty->Struct == TBaseStructure<FRotator>::Get()) Status = Target->SetGraphParameter(Name, *StructProperty->ContainerPtrToValuePtr<FRotator>(Container));
        else if (StructProperty->Struct == TBaseStructure<FTransform>::Get()) Status = Target->SetGraphParameter(Name, *StructProperty->ContainerPtrToValuePtr<FTransform>(Container));
    }
    if (Status == EPropertyBagResult::Success) return true;
    OutError = TEXT("The native graph parameter setter did not commit the staged value.");
    return false;
}
}
#endif
