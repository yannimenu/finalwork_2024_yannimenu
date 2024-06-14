// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectSortPredicate.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class LIBAMASSON_API UObjectSortPredicate : public UObject
{
	GENERATED_BODY()

public:

	virtual bool Compare(UObject* Left, UObject* Right) const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Compare", Category = "Sorting")
	bool BP_Compare(UObject* Left, UObject* Right) const;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort", meta = (ExposeOnSpawn = true))
    bool bSortAscending = true;

	/** Scorify */

	FORCEINLINE float CanScorify() const { return bCanScorify; }

	virtual float ScorifyElement(UObject* Element) const;

	/** CanScorify must be activated for this function to be used */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "ScorifyElement", Category = "Score")
	float BP_ScorifyElement(UObject* Element) const;

	TArray<TPair<UObject*, float>> ScorifyArray(const TArray<UObject*>& Array) const;

protected:

	/** When activated, the sort algorithm will not use the Compare function,
	 * but Instead, will attribute a float value to each elements using the
	 * ScorifyElement function and sort them with this value.
	 * Allowing us to do performance intensive calculations only once per
	 * elements like calculating a distance from a point.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Score")
	bool bCanScorify = false;

};
