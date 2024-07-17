// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SplineComponent.h"

#include "PipBPFuncLib.generated.h"

using namespace ESplinePointType;

UCLASS()
class PIP_API UPipBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "point in polygon\ncheck if actor inside spline", CompactNodeTitle = "Pip"))
	static bool Pip(USplineComponent* polygon, AActor* point);	
};
