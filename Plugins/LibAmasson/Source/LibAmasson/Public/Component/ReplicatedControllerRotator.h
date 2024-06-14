// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ReplicatedControllerRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIBAMASSON_API UReplicatedControllerRotator : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReplicatedControllerRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UFUNCTION(NetMulticast, Unreliable)
    void Multicast_UpdateRotation(FRotator NewRotation);

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
    UPROPERTY()
    TWeakObjectPtr<APawn> OwningPawn;

};
