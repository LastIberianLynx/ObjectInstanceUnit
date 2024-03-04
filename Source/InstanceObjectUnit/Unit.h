// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Unit.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class INSTANCEOBJECTUNIT_API Unit : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Destination;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Valid = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FIntPoint CurrentTile;


	//Unit();
	//~Unit();
};
