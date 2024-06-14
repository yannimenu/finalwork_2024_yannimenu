// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GameManagementWcc.generated.h"


class APlayerController;

/**
 * 
 */
UCLASS()
class LIBAMASSON_API UGameManagementWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void Initialize(UObject* WorldContextObject);


	/** GameplayStatics */

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = "2", DisplayName = "Open Level (by Name)"), Category="Game")
	void OpenLevel(FName LevelName, bool bAbsolute = true, FString Options = FString(TEXT("")));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = "2", DisplayName = "Open Level (by Object Reference)"), Category="Game")
	void OpenLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld> Level, bool bAbsolute = true, FString Options = FString(TEXT("")));


protected:

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject;

};
