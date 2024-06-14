// Amasson


#include "Sorting/SortingFunctionLibrary.h"

void USortingFunctionLibrary::SortInPlace(TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    if (!IsValid(PredicateClass))
        return;

    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);
    SortInPlaceUsingPredicate(Array, Predicate);
}

void USortingFunctionLibrary::SortInPlaceUsingPredicate(TArray<UObject*>& Array, UObjectSortPredicate* Predicate)
{
    if (!IsValid(Predicate))
        return;

    const bool bAscending = Predicate->bSortAscending;
    if (Predicate->CanScorify())
    {
        TArray<TPair<UObject*, float>> ScorifiedArray = Predicate->ScorifyArray(Array);

        ScorifiedArray.Sort([bAscending](TPair<UObject*, float> Left, TPair<UObject*, float> Right) {
	        return bAscending ? Left.Value <= Right.Value : Right.Value <= Left.Value;
        });

        for (int i = 0; i < ScorifiedArray.Num(); i++)
        {
            Array[i] = ScorifiedArray[i].Key;
        }
    }
    else
    {
        Array.Sort([Predicate, bAscending](UObject& Left, UObject& Right) {
            return bAscending ? Predicate->Compare(&Left, &Right) : Predicate->Compare(&Right, &Left);
        });
    }
}

bool USortingFunctionLibrary::IsArraySorted(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);
    return IsArraySortedUsingPredicate(Array, Predicate);
}

bool USortingFunctionLibrary::IsArraySortedUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate)
{
    // Array of 0 or 1 element is always sorted
    if (Array.Num() <= 1)
        return true;

    if (Predicate->CanScorify())
    {
        float PreviousElementScore = Predicate->ScorifyElement(Array[0]);
        for (int32 i = 1; i < Array.Num(); i++)
        {
            const float ElementScore = Predicate->ScorifyElement(Array[i]);

            const bool bSorted = Predicate->bSortAscending ?
                PreviousElementScore <= ElementScore :
                ElementScore <= PreviousElementScore;

            if (!bSorted)
                return false;

            PreviousElementScore = ElementScore;
        }
        return true;
    }
    else
    {
        for (int32 i = 1; i < Array.Num(); i++)
        {
            const bool bSorted = Predicate->bSortAscending ?
                Predicate->Compare(Array[i - 1], Array[i]) :
                Predicate->Compare(Array[i], Array[i - 1]);

            if (!bSorted)
                return false;
        }
        return true;
    }
}


/** Sort range */

UObject* USortingFunctionLibrary::GetMin(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);

    return GetMinUsingPredicate(Array, Predicate);
}

UObject* USortingFunctionLibrary::GetMinUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate)
{
    if (Array.IsEmpty())
        return nullptr;

    UObject* MinElement = Array[0];
    for (int i = 1; i < Array.Num(); i++)
    {
        if (Predicate->Compare(Array[i], MinElement))
            MinElement = Array[i];
    }
    return MinElement;
}

TArray<UObject*> USortingFunctionLibrary::GetNMin(const TArray<UObject*>& Array, int32 N, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);

    return GetNMinUsingPredicate(Array, N, Predicate);
}

TArray<UObject*> USortingFunctionLibrary::GetNMinUsingPredicate(const TArray<UObject*>& Array, int32 N, UObjectSortPredicate* Predicate)
{
    TArray<UObject*> SortedArray(Array);

    SortInPlaceUsingPredicate(SortedArray, Predicate);

    if (SortedArray.Num() > N)
        SortedArray.SetNum(N, true);

    return SortedArray;
}

UObject* USortingFunctionLibrary::GetMax(const TArray<UObject*>& Array, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);

    return GetMaxUsingPredicate(Array, Predicate);
}

UObject* USortingFunctionLibrary::GetMaxUsingPredicate(const TArray<UObject*>& Array, UObjectSortPredicate* Predicate)
{
    if (Array.IsEmpty())
        return nullptr;

    UObject* MaxElement = Array[0];
    for (int i = 1; i < Array.Num(); i++)
    {
        if (Predicate->Compare(MaxElement, Array[i]))
            MaxElement = Array[i];
    }
    return MaxElement;
}

TArray<UObject*> USortingFunctionLibrary::GetNMax(const TArray<UObject*>& Array, int32 N, TSubclassOf<UObjectSortPredicate> PredicateClass)
{
    UObjectSortPredicate *Predicate = NewObject<UObjectSortPredicate>(GetTransientPackage(), PredicateClass);

    return GetNMaxUsingPredicate(Array, N, Predicate);
}

TArray<UObject*> USortingFunctionLibrary::GetNMaxUsingPredicate(const TArray<UObject*>& Array, int32 N, UObjectSortPredicate* Predicate)
{
    TArray<UObject*> SortedArray(Array);

    SortInPlaceUsingPredicate(SortedArray, Predicate);

    for (int32 i = 0; N + i - 1 < SortedArray.Num(); i++)
    {
        SortedArray[i] = SortedArray[N + i - 1];
    }

    if (SortedArray.Num() > N)
        SortedArray.SetNum(N, true);

    return SortedArray;
}


/** Cast */

TArray<UObject*>& USortingFunctionLibrary::CastArray(TArray<UObject*>& ObjectArray, TSubclassOf<UObject> NewClass, bool bSafe)
{
    if (!bSafe)
        return ObjectArray;

    for (UObject*& ElementPtr : ObjectArray)
    {
        if (IsValid(ElementPtr) && !ElementPtr->IsA(NewClass))
            ElementPtr = nullptr;
    }

    return ObjectArray;
}
