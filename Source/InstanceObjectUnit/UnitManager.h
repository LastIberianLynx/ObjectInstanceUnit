// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.h"
//#include "GameFramework/GameModeBase.h"
//#include "Kismet/GameplayStatics.h"
#include "UnitManager.generated.h"

UCLASS()
class INSTANCEOBJECTUNIT_API AUnitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	Unit* SpawnUnit(FVector Location);
	void DestroyUnit(int32 index/*, Unit& Unit*/);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<Unit*> AllUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*, meta = (ExposeOnSpawn = "true")*/
		UInstancedStaticMeshComponent* ISM_Units;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<Unit*> MovingUnits;


};
