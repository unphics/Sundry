#include "Control/Player/IKUNPCBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputLibrary.h"
#include "EnhancedInputComponent.h"
#include "Entity/Actor/Camera.h"
#include "Entity/Charactar/IKUNCharacterBase.h"

AIKUNPCBase::AIKUNPCBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AIKUNPCBase::BeginPlay() {
	Super::BeginPlay();

	this->OwnerCharacter = Cast<AIKUNCharacterBase>(GetPawn());
	// this->InitCamera();
}

void AIKUNPCBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AIKUNPCBase::SetupInputComponent() {
	Super::SetupInputComponent();
}

void AIKUNPCBase::InitCamera() {
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto location = this->K2_GetActorLocation();
	auto rotation = this->K2_GetActorRotation();
	this->ViewCamera = Cast<ACamera>(GetWorld()->SpawnActor(this->CameraActorClass, &location, &rotation, SpawnParam));
	if (this->ViewCamera) {
		this->SetViewTarget(this->ViewCamera);
		FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
		this->ViewCamera->AttachToActor(this, AttachRule);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed To Spawn Player Camera !!"))
	}
}
