// Fill out your copyright notice in the Description page of Project Settings.


#include "AmassonBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


AGameStateBase* UAmassonBlueprintFunctionLibrary::GetGameState(const UObject* WorldContextObject, TSubclassOf<AGameStateBase> GameStateClass)
{
    return UGameplayStatics::GetGameState(WorldContextObject);
}

AGameModeBase* UAmassonBlueprintFunctionLibrary::GetGameMode(const UObject* WorldContextObject, TSubclassOf<AGameModeBase> GameModeClass)
{
    return UGameplayStatics::GetGameMode(WorldContextObject);
}

UGameInstance* UAmassonBlueprintFunctionLibrary::GetGameInstance(const UObject* WorldContextObject, TSubclassOf<UGameInstance> GameInstanceClass)
{
    return UGameplayStatics::GetGameInstance(WorldContextObject);
}

bool UAmassonBlueprintFunctionLibrary::RenameObject(UObject* Object, FString NewName, UObject* NewOuter)
{
    return Object->Rename(*NewName, NewOuter);
}
