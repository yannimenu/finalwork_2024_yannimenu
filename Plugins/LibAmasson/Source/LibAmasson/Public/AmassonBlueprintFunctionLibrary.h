// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/GameInstance.h"
#include "AmassonBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIBAMASSON_API UAmassonBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game", meta = (DefaultToSelf = "WorldContextObject", DeterminesOutputType = "GameStateClass"))
	static AGameStateBase* GetGameState(const UObject* WorldContextObject, TSubclassOf<AGameStateBase> GameStateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game", meta = (DefaultToSelf = "WorldContextObject", DeterminesOutputType = "GameModeClass"))
	static AGameModeBase* GetGameMode(const UObject* WorldContextObject, TSubclassOf<AGameModeBase> GameModeClass);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game" , meta = (DefaultToSelf = "WorldContextObject", DeterminesOutputType = "GameInstanceClass"))
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject, TSubclassOf<UGameInstance> GameInstanceClass);


    UFUNCTION(BlueprintCallable)
    static bool RenameObject(UObject* Object, FString NewName, UObject* NewOuter);

};
