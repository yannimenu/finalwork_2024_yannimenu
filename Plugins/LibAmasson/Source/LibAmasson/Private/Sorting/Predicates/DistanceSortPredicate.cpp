// Amasson


#include "Sorting/Predicates/DistanceSortPredicate.h"


UDistanceSortPredicate::UDistanceSortPredicate()
{
    bCanScorify = true;
}

float UDistanceSortPredicate::ScorifyElement(UObject* Element) const
{
    FVector Location;

    if (IsValid(Element))
    {
        if (AActor* AsActor = Cast<AActor>(Element))
            Location = AsActor->GetActorLocation();
        else if (USceneComponent* AsSceneComponent = Cast<USceneComponent>(Element))
            Location = AsSceneComponent->GetComponentLocation();
    }
    else
        Location = FVector::ZeroVector;

    return (Location - ComparisonPoint).SquaredLength();
}
