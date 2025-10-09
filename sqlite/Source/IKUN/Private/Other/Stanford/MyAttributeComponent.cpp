#include "Other/Stanford/MyAttributeComponent.h"

UMyAttributeComponent::UMyAttributeComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	this->Health = 100;
}

void UMyAttributeComponent::BeginPlay() {
	Super::BeginPlay();
}

void UMyAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UMyAttributeComponent::ApplyHealthChange(float Delta) {
	this->Health += Delta;
	return true;
}

