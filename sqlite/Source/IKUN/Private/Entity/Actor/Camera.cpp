#include "Entity/Actor/Camera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Control/Player/IKUNPCBase.h"

ACamera::ACamera() {
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->RootComponent = this->Mesh;
	this->Mesh->SetCollisionProfileName("NoCollision");
	
	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	this->SpringArmComp->SetupAttachment(this->RootComponent);
	this->SpringArmComp->bUsePawnControlRotation = true;
	this->SpringArmComp->TargetArmLength = 250.0f;
	this->SpringArmComp->SocketOffset = FVector(0.0f, 0.0f, 90.0f);
	this->SpringArmComp->bDoCollisionTest = false;
	
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	this->CameraComp->SetupAttachment(this->SpringArmComp);
}

void ACamera::BeginPlay() {
	Super::BeginPlay();
	
}

void ACamera::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
