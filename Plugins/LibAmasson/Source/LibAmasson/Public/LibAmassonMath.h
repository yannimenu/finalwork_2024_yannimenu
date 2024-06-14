// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LibAmassonMath.generated.h"

/**
 * 
 */
UCLASS()
class LIBAMASSON_API ULibAmassonMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Trace")
	static void GetTraceForward(USceneComponent* Component, double Distance, FVector& StartPoint, FVector& EndPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Trace")
	static void TraceClampDistance(const FVector& StartPoint, const FVector& EndPoint, double MinDistance, double MaxDistance, FVector& NewStartPoint, FVector& NewEndPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static FVector AddLengthToVector(FVector Vector, double Length);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static FVector SetLengthToVector(FVector Vector, double Length);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static TArray<FVector> TransformPoints(const TArray<FVector>& Points, const FTransform& Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static TArray<FTransform> TransformTransforms(const TArray<FTransform>& Transforms, const FTransform& Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static void ArcPoints(float ArcAngle, int32 Count, float Distance, TArray<FVector>& Points);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Vector")
	static void ArcTransforms(float ArcAngle, int32 Count, float Distance, TArray<FTransform>& Transforms);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Math|Points")
    static TArray<FVector2D> SmoothPointsInRectangle(int32 NumPoints, FVector2D MinBound, FVector2D MaxBound, int32 NumIterations = 100, float Radius = 100.0f);

};
