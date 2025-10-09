#include "Module/GAS/IKUNASC.h"
#include "AbilitySystemGlobals.h"

UIKUNASC::UIKUNASC() {
	PrimaryComponentTick.bCanEverTick = true;

}


void UIKUNASC::BeginPlay() {
	Super::BeginPlay();

	
}


void UIKUNASC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

UIKUNASC* UIKUNASC::GetASCFromActor(const AActor* Actor, bool LookForComponent) {
	return Cast<UIKUNASC>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}


