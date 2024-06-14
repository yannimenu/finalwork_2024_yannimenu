// Copyright Amasson


#include "Component/ReplicatedControllerRotator.h"

UReplicatedControllerRotator::UReplicatedControllerRotator()
{
    SetIsReplicatedByDefault(true);

	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
}

void UReplicatedControllerRotator::BeginPlay()
{
	Super::BeginPlay();

    OwningPawn = Cast<APawn>(GetOwner());
    if (!OwningPawn.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("UReplicatedControllerRotator not owned by a Pawn actor"));
        return;
    }
    SetComponentTickEnabled(OwningPawn->HasAuthority());
}

void UReplicatedControllerRotator::Multicast_UpdateRotation_Implementation(FRotator NewRotation)
{
    SetWorldRotation(NewRotation);
}

void UReplicatedControllerRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!OwningPawn.IsValid())
    {
        return;
    }

    AController* Controller = OwningPawn->GetController();
    if (!IsValid(Controller))
    {
        return;
    }

    Multicast_UpdateRotation(Controller->GetControlRotation());
}
