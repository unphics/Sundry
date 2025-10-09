// Fill out your copyright notice in the Description page of Project Settings.
#include  "Control/AI/TeamAI/TeamAIComp.h"

#include "NavigationSystem/Public/NavigationSystem.h"

UTeamAIComp::UTeamAIComp() {
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTeamAIComp::BeginPlay() {
	Super::BeginPlay();
	
}

void UTeamAIComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}
void UTeamAIComp::_GetNavData() {
	// UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(this->GetOwner()->GetWorld())
}
