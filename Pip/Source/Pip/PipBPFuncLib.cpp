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