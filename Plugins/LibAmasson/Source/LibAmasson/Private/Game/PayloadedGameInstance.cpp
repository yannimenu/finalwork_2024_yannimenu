// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PayloadedGameInstance.h"


UObject* UPayloadedGameInstance::AddCrossLevelPayloadFromClass(TSubclassOf<UObject> PayloadClass, FName Key)
{
    UObject* NewPayload = NewObject<UObject>(this, PayloadClass, Key);
    CrossLevelPayloads.Add(Key, NewPayload);
    return NewPayload;
}

void UPayloadedGameInstance::RemoveCrossLevelPayloadWithkey(FName Key)
{
    CrossLevelPayloads.Remove(Key);
}

UObject* UPayloadedGameInstance::GetCrossLevelPayload(FName Key, TSubclassOf<UObject> PayloadClass) const
{
    const TObjectPtr<UObject>* Payload = CrossLevelPayloads.Find(Key);
    if (!Payload)
        return nullptr;

    if (!(*Payload)->IsA(PayloadClass))
        return nullptr;

    return *Payload;
}
