// Fill out your copyright notice in the Description page of Project Settings.

#include "PipBPFuncLib.h"

bool UPipBPFuncLib::Pip(USplineComponent* polygon, AActor* point)
{
	int32 vertexCnt=polygon->GetNumberOfSplinePoints();
	int32 intersectionCnt = 0;
	FVector p = point->GetActorLocation();

	for (int32 i = 0; i < vertexCnt; i++)
	{
		FVector p1 = polygon->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector p2 = polygon->GetLocationAtSplinePoint((i + 1) % vertexCnt, ESplineCoordinateSpace::World);
        if ((p.Y >  (p1.Y < p2.Y ? p1.Y : p2.Y)) &&
            (p.Y <= (p1.Y > p2.Y ? p1.Y : p2.Y)) &&
            (p.X <= (p1.X > p2.X ? p1.X : p2.X))
            )
        {
            double xIntersect = (p.Y - p1.Y) * (p2.X - p1.X) / (p2.Y - p1.Y) + p1.X;
            if (p1.X == p2.X || p.X <= xIntersect)
                intersectionCnt++;
        }
	}

	return intersectionCnt % 2 == 1;;
}

float UPipBPFuncLib::BorderDist(USplineComponent* polygon, AActor* point)
{
	FVector p = point->GetActorLocation();
	int32 vertexCnt = polygon->GetNumberOfSplinePoints();
	float dist = 0.0f;
	float distLast = 0.0f;

	for (int32 i = 0; i < vertexCnt; i++)
	{
		FVector p1 = polygon->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector p2 = polygon->GetLocationAtSplinePoint((i + 1) % vertexCnt, ESplineCoordinateSpace::World);

		// calculate line p1-p2 as y=kx+b
		float k = (p1.Y-p2.Y) / (p1.X-p2.X);
		float b = p1.Y - p1.X * (p2.Y - p1.Y) / (p2.X-p1.X);

		// vertex is segment not line
		float distLine = fabs(k * p.X - p.Y + b) / sqrt(1 + k * k);
		float p_p1 = FVector::Dist(p, p1);
		float p_p2 = FVector::Dist(p, p2);
		TArray<float> dists = {distLine,p_p1,p_p2};
		dist=FMath::Min(dists);

		if (i == 0)
		{
			distLast = dist;
			continue;
		}
		distLast = dist <= distLast ? dist : distLast;
	}
	// print distLast to log
	UE_LOG(LogTemp, Warning, TEXT("distance to border: %f"), distLast);
	return distLast;
}

bool UPipBPFuncLib::InsideCircle(float radius, FVector2D center, AActor* point)
{
	FVector p = point->GetActorLocation();
	return radius*radius > (p.X - center.X)*(p.X - center.X)+ (p.Y - center.Y) * (p.Y - center.Y);
}

