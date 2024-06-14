// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/WidgetControllerComponent.h"
#include "WidgetController.generated.h"

class AController;
class APlayerState;
class APawn;
class ACharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnControllerStateUpdateSignature, FName, State);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LIBAMASSON_API UWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UWidgetController();

	/** Make and construct a widget controller from the specific class.
	 * If there is an observed actor given, it will cast it to the correct type and
	 * call SetObserved_X with it.
	*/
	UFUNCTION(BlueprintCallable, Category = "WidgetController|Construct", meta = (HidePin = "Outer", DefaultToSelf = "Outer"), meta = (DeterminesOutputType = "WidgetControllerClass"))
	static UWidgetController* MakeWidgetController(UObject* Outer, TSubclassOf<UWidgetController> WidgetControllerClass, AActor* ObservedActor);

	UFUNCTION(BlueprintCallable, Category = "Observed")
	virtual void SetObservedController(AController* InController);

	UFUNCTION(BlueprintCallable, Category = "Observed")
	virtual void SetObservedPlayerState(APlayerState* InPlayerState);

	UFUNCTION(BlueprintCallable, Category = "Observed")
	virtual void SetObservedPawn(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "Observed")
	virtual void SetObservedActor(AActor* InActor, bool bTryCast = false);

	UFUNCTION(BlueprintCallable, Category = "Broadcast")
	virtual void BroadcastValues();

	UFUNCTION(BlueprintCallable, Category = "Observed")
	FORCEINLINE AController* GetController() const { return Controller; }
	UFUNCTION(BlueprintCallable, Category = "Observed")
	FORCEINLINE APlayerState* GetPlayerState() const { return PlayerState; }
	UFUNCTION(BlueprintCallable, Category = "Observed")
	FORCEINLINE APawn* GetPawn() const { return Pawn; }
	UFUNCTION(BlueprintCallable, Category = "Observed")
	AActor* GetObservedActor() const { return Actor; }

    UPROPERTY(BlueprintAssignable)
    FOnControllerStateUpdateSignature OnControllerStateUpdate;

    UFUNCTION(BlueprintCallable, Category = "State Behavior")
    void BroadcastState(FName State);

    /** Components */

	template<class TComponentType>
	TComponentType* GetComponent()
	{
		static_assert(std::is_base_of<UWidgetControllerComponent, TComponentType>::value, "TComponentType must be a subclass of UWidgetControllerComponent.");

		for (UWidgetControllerComponent* Component : Components)
		{
			if (TComponentType* CastComponent = Cast<TComponentType>(Component))
			{
				return CastComponent;
			}
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Component", meta = (DeterminesOutputType = "ComponentClass"))
	UWidgetControllerComponent* GetComponentByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const;

	UFUNCTION(BlueprintCallable, Category = "Component", meta = (DeterminesOutputType = "ComponentClass"))
	UWidgetControllerComponent* GetComponentByClassAndName(TSubclassOf<UWidgetControllerComponent> ComponentClass, FName ComponentName) const;

	UFUNCTION(BlueprintCallable, Category = "Component", meta = (DeterminesOutputType = "ComponentClass"))
	TArray<UWidgetControllerComponent*> GetComponentsByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const;

	template<class TComponentType>
	TComponentType* AddComponent(FName ComponentName)
	{
		static_assert(std::is_base_of<UWidgetControllerComponent, TComponentType>::value, "TComponentType must be a subclass of UWidgetControllerComponent.");

		TComponentType* NewComponent = NewObject<TComponentType>(this, TComponentType::StaticClass(), ComponentName);
		Components.Add(NewComponent);
		return NewComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Component", meta = (DeterminesOutputType = "ComponentClass"))
	UWidgetControllerComponent* AddComponentByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass, FName ComponentName);


protected:

	UFUNCTION()
	virtual void Construct() {}

	UFUNCTION(BlueprintImplementableEvent, Category = "Construction", DisplayName = "Construct")
	void BP_Construct();

	UFUNCTION()
    virtual void ObservedActorSet() {}

	UFUNCTION(BlueprintImplementableEvent, Category = "Observed", DisplayName = "ObservedActorSet")
	void BP_ObservedActorSet();

	UFUNCTION()
	virtual void BindCallbacksToDependencies();

	UFUNCTION(BlueprintImplementableEvent, Category = "Broadcast", DisplayName = "BindCallbacksToDependencies")
	void BP_BindCallbacksToDependencies();

	/** Called at the end of controller SetObserved_X */
	UFUNCTION(BlueprintCallable, Category = "Observed")
	void FinishSetObserved();

	UFUNCTION(BlueprintImplementableEvent, Category = "Broadcast", DisplayName = "BroadcastValues")
	void BP_BroadcastValues();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AController> Controller;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APawn> Pawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AActor> Actor;

	UPROPERTY()
	TArray<TObjectPtr<UWidgetControllerComponent>> Components;

};
