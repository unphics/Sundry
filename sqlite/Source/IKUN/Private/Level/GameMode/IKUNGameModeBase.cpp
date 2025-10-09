// Copyright Epic Games, Inc. All Rights Reserved.

#include "Level/GameMode/IKUNGameModeBase.h"
#include "Other/3DMath/Math.h"
#include "Module/SQLite/SQLiteMgr.h"

void AIKUNGameModeBase::StartPlay() {
	Super::StartPlay();
	UE_LOG(LogTemp, Warning, TEXT("=========== GameModeBase StartPlay =========="));
	this->SqliteMgr = NewObject<USQLiteMgr>();
	
	Math::run();
}

void AIKUNGameModeBase::BeginDestroy() {
	Super::BeginDestroy();
	
}