#include "Other/Stanford/MagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Other/Stanford/MyAttributeComponent.h"

AMagicProjectile::AMagicProjectile() {
	PrimaryActorTick.bCanEverTick = true;
	
	this->SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	// this->SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// this->SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// this->SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->SphereComp->SetCollisionProfileName("Projectile");
	this->SphereComp->SetSimulatePhysics(false);
	this->SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::OnActorBeginOverlap);
	RootComponent = this->SphereComp;
	

	this->ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	this->ProjectileMoveComp->InitialSpeed = 1000.0f;
	this->ProjectileMoveComp->bRotationFollowsVelocity = true;
	this->ProjectileMoveComp->bInitialVelocityInLocalSpace = true;
	this->ProjectileMoveComp->ProjectileGravityScale = 0.0f; // 重力

	this->ParticleSysComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSysComp");
	this->ParticleSysComp->SetupAttachment(this->SphereComp);
}

void AMagicProjectile::BeginPlay() {
	Super::BeginPlay();
	
}

void AMagicProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AMagicProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Log, TEXT("AMagicProjectile::OnActorBeginOverlap"))
	if (OtherActor) {
		UMyAttributeComponent* AttribComp = Cast<UMyAttributeComponent>(OtherActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if (AttribComp) {
			AttribComp->ApplyHealthChange(-20.f);
			UE_LOG(LogTemp, Log, TEXT("AttribComp->ApplyHealthChange(-20.f)"))
			Destroy();
		}
	}
}
