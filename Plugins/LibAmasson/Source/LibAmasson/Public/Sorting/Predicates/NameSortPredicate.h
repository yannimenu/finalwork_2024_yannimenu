// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Sorting/ObjectSortPredicate.h"
#include "NameSortPredicate.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LIBAMASSON_API UNameSortPredicate : public UObjectSortPredicate
{
	GENERATED_BODY()

public:

    UNameSortPredicate();

	virtual bool Compare(UObject* Left, UObject* Right) const override;

};
