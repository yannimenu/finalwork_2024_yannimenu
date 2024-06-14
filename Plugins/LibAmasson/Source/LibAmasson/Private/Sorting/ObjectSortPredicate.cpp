// Amasson


#include "Sorting/ObjectSortPredicate.h"


bool UObjectSortPredicate::Compare(UObject* Left, UObject* Right) const
{
    if (CanScorify())
        return ScorifyElement(Left) < ScorifyElement(Right);

    return BP_Compare(Left, Right);
}

float UObjectSortPredicate::ScorifyElement(UObject* Element) const
{
    return BP_ScorifyElement(Element);
}

TArray<TPair<UObject*, float>> UObjectSortPredicate::ScorifyArray(const TArray<UObject*>& Array) const
{
    checkf(CanScorify(), TEXT("ScorifyArray used on predicate that cannot scorify"));

    TArray<TPair<UObject*, float>> ScorifiedElements;

    for (UObject* Element : Array)
    {
        TPair<UObject*, float> ScorifiedElement;
        ScorifiedElement.Key = Element;
        ScorifiedElement.Value = ScorifyElement(Element);
        ScorifiedElements.Add(ScorifiedElement);
    }
    return ScorifiedElements;
}
