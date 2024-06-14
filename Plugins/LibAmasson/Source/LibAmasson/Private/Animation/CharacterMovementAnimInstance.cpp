// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterMovementAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterMovementAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (APawn* Owner = TryGetPawnOwner()) {
        CharacterMovementComponent = Owner->GetComponentByClass<UCharacterMovementComponent>();
        _PreviousYaw = Owner->GetActorRotation().Yaw;
    }
}

void UCharacterMovementAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (APawn* Owner = TryGetPawnOwner())
    {
        FRotator Rotation = Owner->GetActorRotation();
        TurnVelocity = (Rotation.Yaw - _PreviousYaw) / DeltaTime;

        if (CharacterMovementComponent)
        {
            bFalling = CharacterMovementComponent->IsFalling();
            bCrouching = CharacterMovementComponent->IsCrouching();
            bSwimming = CharacterMovementComponent->IsSwimming();

            LocalVelocity = Rotation.UnrotateVector(CharacterMovementComponent->Velocity);
            LocalVelocityAngle = LocalVelocity.IsNearlyZero() ? 0 : FMath::RadiansToDegrees(FMath::Atan2(LocalVelocity.Y, LocalVelocity.X));

        }

        _PreviousYaw = Rotation.Yaw;
    }
}

bool UCharacterMovementAnimInstance::IsPawnMoving() const
{
    return LocalVelocity.SquaredLength() > 10;
}

bool UCharacterMovementAnimInstance::IsJumpingUp() const
{
    return LocalVelocity.Z > 0 && bFalling;
}

bool UCharacterMovementAnimInstance::IsFallingDown() const
{
    return LocalVelocity.Z <= 0 && bFalling;
}
