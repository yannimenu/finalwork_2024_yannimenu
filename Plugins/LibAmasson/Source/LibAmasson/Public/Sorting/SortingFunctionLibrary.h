// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sorting/ObjectSortPredicate.h"
#include "SortingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIBAMASSON_API USortingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Sort")
	static void SortInPlace(UPARAM(Ref) TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, Category = "Sort")
	static void SortInPlaceUsingPredicate(UPARAM(Ref) TArray<UObject*>& Array, UObjectSortPredicate* Predicate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort")
	static bool IsArraySorted(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort")
	static bool IsArraySortedUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate);


	/** Sort range */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static UObject* GetMin(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static UObject* GetMinUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static TArray<UObject*> GetNMin(const TArray<UObject*>& Array, int32 N, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static TArray<UObject*> GetNMinUsingPredicate(const TArray<UObject*>& Array, int32 N, UObjectSortPredicate* Predicate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static UObject* GetMax(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static UObject* GetMaxUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static TArray<UObject*> GetNMax(const TArray<UObject*>& Array, int32 N, TSubclassOf<UObjectSortPredicate> PredicateClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sort", meta = (DeterminesOutputType = "Array"))
	static TArray<UObject*> GetNMaxUsingPredicate(const TArray<UObject*>& Array, int32 N, UObjectSortPredicate* Predicate);


	/** Cast */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Array", meta = (DeterminesOutputType = "NewClass"))
	static TArray<UObject*>& CastArray(UPARAM(Ref) TArray<UObject*>& ObjectArray, TSubclassOf<UObject> NewClass, bool bSafe = false);

};
