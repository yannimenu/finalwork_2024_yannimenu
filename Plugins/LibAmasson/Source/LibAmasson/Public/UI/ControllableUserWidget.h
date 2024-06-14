// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControllableUserWidget.generated.h"

class UWidgetController;
class UWidgetControllerComponent;


USTRUCT(BlueprintType)
struct FWidgetStateBehavior
{
	GENERATED_BODY()

public:
	/** Set of states that makes the widget visible */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> VisibleStates;

	/** Set of states that makes the widget disabled */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> DisabledStates;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESlateVisibility Visible = ESlateVisibility::SelfHitTestInvisible;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESlateVisibility Invisible = ESlateVisibility::Hidden;
};

/**
 * 
 */
UCLASS()
class LIBAMASSON_API UControllableUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Controller|Component", meta = (DeterminesOutputType = "ComponentClass"))
	UWidgetControllerComponent* GetComponentFromControllerByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const;

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void SetWidgetController(UWidgetController* NewWidgetController);

    /** Whether or not the Widget Controller triggers some state behavior */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State Behavior")
    bool bUseStateBehavior = false;

    /** Triggered behavior from the Widget Controller */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State Behavior", meta = (EditCondition="bUseStateBehavior"))
    FWidgetStateBehavior StateBehavior;

protected:

    virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Controller")
	void WidgetControllerSet(UWidgetController* NewWidgetController);

	UFUNCTION(Category = "Controller|Propagation")
	virtual bool AcceptWidgetController(UWidgetController* InWidgetController) const;

    UFUNCTION()
    virtual void OnWidgetControllerUpdateState(FName State);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller", meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	TObjectPtr<UWidgetController> WidgetController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller|Propagation")
	bool TakeControllerFromParent = true;

	UPROPERTY(EditDefaultsOnly, Category = "Controller|Propagation")
	TSet<TSubclassOf<UWidgetController>> AcceptedControllerClasses;

private:

	UFUNCTION()
	void PropagateWidgetController(UWidget* Parent);

};
