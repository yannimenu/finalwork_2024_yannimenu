// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Sorting/ObjectSortPredicate.h"
#include "DistanceSortPredicate.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LIBAMASSON_API UDistanceSortPredicate : public UObjectSortPredicate
{
	GENERATED_BODY()

public:

    UDistanceSortPredicate();

	virtual float ScorifyElement(UObject* Element) const override;

    UPROPERTY(BlueprintReadWrite, Category = "Distance", meta = (ExposeOnSpawn = true))
    FVector ComparisonPoint;

};
