#include "Entity/Actor/ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase() {
	PrimaryActorTick.bCanEverTick = true;

	this->SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	this->SphereComp->SetCollisionProfileName("Projectile");
	this->SphereComp->SetSimulatePhysics(false);
	this->SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnActorBeginOverlap);
	RootComponent = this->SphereComp;

	this->ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	this->ProjectileMoveComp->InitialSpeed = 1000.0f;
	this->ProjectileMoveComp->bRotationFollowsVelocity = true;
	this->ProjectileMoveComp->bInitialVelocityInLocalSpace = true;
	this->ProjectileMoveComp->ProjectileGravityScale = 0.0f; // 重力

	this->ParticleSysComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSysComp");
	this->ParticleSysComp->SetupAttachment(this->SphereComp);
}

void AProjectileBase::BeginPlay() {
	Super::BeginPlay();
	
}

void AProjectileBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Log, TEXT("AProjectileBase::OnActorBeginOverlap"))
	if (OtherActor) {
		UE_LOG(LogTemp, Log, TEXT("AProjectileBase:HitOtherActor"))
		//this->Destroy();
	}
}