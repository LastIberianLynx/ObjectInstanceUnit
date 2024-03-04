// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Unit.h"
#include "InstanceObjectUnitGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INSTANCEOBJECTUNIT_API AInstanceObjectUnitGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
		virtual void BeginPlay() override;
};
