// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterMovementAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LIBAMASSON_API UCharacterMovementAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	FVector LocalVelocity;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = Movement)
	bool IsPawnMoving() const;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float LocalVelocityAngle = 0;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	float TurnVelocity = 0;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bFalling = false;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = Movement)
	bool IsJumpingUp() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category = Movement)
	bool IsFallingDown() const;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bCrouching = false;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bSwimming = false;


private:
	float _PreviousYaw = 0;
};
