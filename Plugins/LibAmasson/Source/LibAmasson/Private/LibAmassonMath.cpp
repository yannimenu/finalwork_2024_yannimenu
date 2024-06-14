// Amasson


#include "LibAmassonMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


void ULibAmassonMath::GetTraceForward(USceneComponent* Component, double Distance, FVector& StartPoint, FVector& EndPoint)
{
    FVector Location = Component->GetComponentLocation();
    FVector Forward = Component->GetForwardVector();

    StartPoint = Location;
    EndPoint = Location + Forward * Distance;
}

void ULibAmassonMath::TraceClampDistance(const FVector& StartPoint, const FVector& EndPoint,
    double MinDistance, double MaxDistance,
    FVector& NewStartPoint, FVector& NewEndPoint)
{
    FVector StartToEnd = EndPoint - StartPoint;
    StartToEnd = UKismetMathLibrary::ClampVectorSize(StartToEnd, MinDistance, MaxDistance);
    NewStartPoint = StartPoint;
    NewEndPoint = StartPoint + StartToEnd;
}

FVector ULibAmassonMath::AddLengthToVector(FVector Vector, double Length)
{
    FVector NewVector = Vector;
    NewVector.Normalize();
    return Vector + NewVector * Length;
}

FVector ULibAmassonMath::SetLengthToVector(FVector Vector, double Length)
{
    FVector NewVector = Vector;
    NewVector.Normalize();
    return NewVector * Length;
}

TArray<FVector> ULibAmassonMath::TransformPoints(const TArray<FVector>& Points, const FTransform& Transform)
{
    TArray<FVector> NewPoints = Points;
    for (FVector& NewPoint : NewPoints)
    {
        NewPoint = Transform.TransformPosition(NewPoint);
    }
    return NewPoints;
}

TArray<FTransform> ULibAmassonMath::TransformTransforms(const TArray<FTransform>& Transforms, const FTransform& Transform)
{
    TArray<FTransform> NewTransforms = Transforms;
    for (FTransform& NewTransform : NewTransforms)
    {
        NewTransform = NewTransform * Transform;
    }
    return NewTransforms;
}

void ULibAmassonMath::ArcPoints(float ArcAngle, int32 Count, float Distance, TArray<FVector>& Points)
{
    if (Count <= 0)
        return;

    const float StepAngle = ArcAngle / (Count - 1);
    FVector Direction = Count == 1 ?
        FVector(1, 0, 0) :
        FVector(1, 0, 0).RotateAngleAxis(-ArcAngle / 2.0f, FVector::UpVector);

    for (int32 i = 0; i < Count; i++)
    {
        const FVector Location = Direction * Distance;

        Points.Add(Location);

        Direction = Direction.RotateAngleAxis(StepAngle, FVector::UpVector);
    }
}

void ULibAmassonMath::ArcTransforms(float ArcAngle, int32 Count, float Distance, TArray<FTransform>& Transforms)
{
    if (Count <= 0)
        return;

    if (Count == 1)
    {
        Transforms.Add(FTransform(FVector(Distance, 0.0f, 0.0f)));
        return;
    }

    float StepAngle = ArcAngle / static_cast<float>(Count - 1);
    FRotator DirectionRotator;

    for (int32 i = 0; i < Count; i++)
    {
        const FRotator Rotation(0.0f, -(ArcAngle / 2.0f) + i * StepAngle, 0.0f);
        const FQuat QuatRotation = Rotation.Quaternion();

        const FVector Location = QuatRotation.GetForwardVector() * Distance;

        const FTransform Transform = FTransform(QuatRotation, Location);
        Transforms.Add(Transform);
    }
}


TArray<FVector2D> ULibAmassonMath::SmoothPointsInRectangle(int32 NumPoints, FVector2D MinBound, FVector2D MaxBound, int32 NumIterations, float Radius)
{
    TArray<FVector2D> Points;
    for (int32 i = 0; i < NumPoints; ++i)
    {
        float X = FMath::FRandRange(MinBound.X, MaxBound.X);
        float Y = FMath::FRandRange(MinBound.Y, MaxBound.Y);
        Points.Add(FVector2D(X, Y));
    }

    for (int32 iter = 0; iter < NumIterations; iter++)
    {
        TArray<FVector2D> NewPoints;
        for (int32 i = 0; i < Points.Num(); ++i)
        {
            // Compute repulsion force from nearby points
            FVector2D RepulsionForce(0, 0);
            for (int32 j = 0; j < Points.Num(); ++j)
            {
                if (i != j)
                {
                    FVector2D Delta = Points[i] - Points[j];
                    float DistanceSquared = Delta.SizeSquared();
                    if (DistanceSquared < FMath::Square(Radius))
                    {
                        RepulsionForce += Delta / FMath::Max(1.0f, DistanceSquared);
                    }
                }
            }

            // Apply repulsion force
            FVector2D NewPoint = Points[i] + RepulsionForce;

            // Clamp new point within bounds
            NewPoint.X = FMath::Clamp(NewPoint.X, MinBound.X, MaxBound.X);
            NewPoint.Y = FMath::Clamp(NewPoint.Y, MinBound.Y, MaxBound.Y);

            NewPoints.Add(NewPoint);
        }

        Points = NewPoints;
    }

    return Points;
}