// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitManager.h"

// Sets default values
AUnitManager::AUnitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ISM_Units = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh2"));
	//ISM_Units->SetupAttachment(CollisionMesh);
	ISM_Units->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ISM_Units->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ISM_Units->CanCharacterStepUp(false);
	ISM_Units->SetCastShadow(false);
	ISM_Units->SetComponentTickEnabled(false);
	ISM_Units->NumCustomDataFloats = 10;
	ISM_Units->SetGenerateOverlapEvents(false);
	ISM_Units->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void AUnitManager::BeginPlay()
{
	Super::BeginPlay();

	//Unit* Unit2;	
	//AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	//Unit2 = NewObject<Unit>(this, Unit::StaticClass(), FName("Unit"));

	SpawnUnit(FVector(100, 100, 100.f));
	Unit* A = SpawnUnit(FVector(100, 300, 100.f)); //unit 1
	A->Destination = A->Location + FVector(500.f, 0.f, 100.f);
	MovingUnits.Add(AllUnits[A->Index]);
	SpawnUnit(FVector(100, 600, 100.f));

	FTimerHandle T; GetWorld()->GetTimerManager().SetTimer(T, [&, A]() {
		DestroyUnit(A->Index);
		}, 6.f, false);

}

// Called every frame
void AUnitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTransform T;
	FVector	AdvanceLocation;
	int32 CurUnit;
	for (int32 i = MovingUnits.Num() - 1; i >= 0; --i) {
		if (!IsValid(MovingUnits[i]) || !MovingUnits[i]->Valid /*MovingUnits[i]->GetName()=="None"*/) {
			MovingUnits.RemoveAtSwap(i);
				continue;
		}
		CurUnit = MovingUnits[i]->Index;
		AdvanceLocation = FMath::VInterpConstantTo(MovingUnits[i]->Location, MovingUnits[i]->Destination, DeltaTime, 50.f/*A->Cur_Speed*/);
		MovingUnits[i]->Location = AdvanceLocation;
		T.SetTranslation(AdvanceLocation);
		ISM_Units->UpdateInstanceTransform(CurUnit, T, true);
	}
	ISM_Units->MarkRenderStateDirty();

}

Unit* AUnitManager::SpawnUnit(FVector Location) {

	Unit* NewUnit;
	NewUnit = NewObject<Unit>(this, Unit::StaticClass(), FName("Unit" + FString::FromInt(ISM_Units->GetInstanceCount())));
	NewUnit->Index = ISM_Units->GetInstanceCount();
	NewUnit->Location = Location;
	ISM_Units->AddInstanceWorldSpace(FTransform(Location));
	AllUnits.Add(NewUnit);
	return AllUnits[NewUnit->Index]; // ? //Debug check. &Unit; //
}

void AUnitManager::DestroyUnit(int32 index) {
	int32 LastIndex = AllUnits.Num() -1;
	FTransform T;
	//copy / swap last index to the index.
	ISM_Units->GetInstanceTransform(LastIndex, T, true);
	ISM_Units->UpdateInstanceTransform(index, T, true, true, false);
	ISM_Units->RemoveInstance(LastIndex);
	//Do the same for the array AllUnits and remove last index.
	//AllUnits[index]->ConditionalBeginDestroy(); /*MovingUnits[i]->GetName()=="None"*/
	AllUnits[index]->Valid = false;
	AllUnits[index] = AllUnits[LastIndex];
	AllUnits[index]->Index = index;
	AllUnits.RemoveAt(LastIndex);
	//this should work to keep the integrity of the indexes
}



