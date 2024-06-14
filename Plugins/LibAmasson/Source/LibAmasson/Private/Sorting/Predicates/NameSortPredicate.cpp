// Amasson


#include "Sorting/Predicates/NameSortPredicate.h"
#include "Kismet/KismetSystemLibrary.h"


UNameSortPredicate::UNameSortPredicate()
{
    bCanScorify = false;
}

bool UNameSortPredicate::Compare(UObject* Left, UObject* Right) const
{
    const FString LeftName = UKismetSystemLibrary::GetDisplayName(Left);
    const FString RightName = UKismetSystemLibrary::GetDisplayName(Right);

    return LeftName <= RightName;
}
