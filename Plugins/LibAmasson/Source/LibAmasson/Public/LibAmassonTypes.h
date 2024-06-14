// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LibAmassonTypes.generated.h"


USTRUCT(BlueprintType)
struct LIBAMASSON_API FObjectArray
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UObject>> Objects;
};

USTRUCT(BlueprintType)
struct LIBAMASSON_API FObjectSet
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSet<TObjectPtr<UObject>> Objects;
};
