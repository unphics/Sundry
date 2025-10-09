// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IKUNGameModeBase.generated.h"

class USQLiteMgr;

/**
 * 
 */
UCLASS()
class IKUN_API AIKUNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void StartPlay() override;
	virtual void BeginDestroy() override;
	UPROPERTY()
	USQLiteMgr* SqliteMgr;

private:
};