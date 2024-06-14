// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerComponent.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class LIBAMASSON_API UWidgetControllerComponent : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Broadcast")
	virtual void BroadcastValues();

	UFUNCTION(BlueprintImplementableEvent, Category = "Broadcast", DisplayName = "BroadcastValues")
	void BP_BroadcastValues();

    UFUNCTION(BlueprintCallable, Category = "Widget Controller")
    class UWidgetController* GetParentController() const;

protected:

	UFUNCTION()
	virtual void BindCallbacksToDependencies();

	UFUNCTION(BlueprintImplementableEvent, Category = "Bind", DisplayName = "BindCallbacksToDependencies")
	void BP_BindCallbacksToDependencies();

	friend class UWidgetController;

};
