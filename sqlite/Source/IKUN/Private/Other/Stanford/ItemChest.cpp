#include "Other/Stanford/ItemChest.h"

AItemChest::AItemChest() {
	PrimaryActorTick.bCanEverTick = true;

	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = this->BaseMesh;

	this->LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	this->LidMesh->SetupAttachment(this->BaseMesh);

	// 不常在构造函数中使用
	// this->LidMesh->AttachToComponent(this->BaseMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true/*是否焊接Collision*/));

	this->TargetPitch = 140;
}

void AItemChest::BeginPlay() {
	Super::BeginPlay();
	
}

void AItemChest::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AItemChest::Interact_Implementation(APawn* InstigatorPawn) {
	IMyInterface::Interact_Implementation(InstigatorPawn);

	this->LidMesh->SetRelativeRotation(FRotator(this->TargetPitch,0,0));
}