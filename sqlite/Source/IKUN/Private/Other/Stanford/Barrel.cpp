#include "Other/Stanford/Barrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

ABarrel::ABarrel() {
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.5f));
	this->Mesh->SetCollisionProfileName("PhysicsActor");
	this->Mesh->SetSimulatePhysics(true);

	this->RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	this->RadialForceComp->SetupAttachment(this->Mesh);
	this->RadialForceComp->Radius = 750.0f;
	this->RadialForceComp->ImpulseStrength = 2500.0f;
	this->RadialForceComp->bImpulseVelChange = true;

	this->Mesh->OnComponentHit.AddDynamic(this, &ABarrel::OnMeshHit);
}

void ABarrel::BeginPlay() {
	Super::BeginPlay();

}

void ABarrel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABarrel::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit) {
	this->RadialForceComp->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("At Game Itme: %f"), GetWorld()->TimeSeconds); // 获取游戏进行的时间
	FString fstr = FString::Printf(TEXT("qqqqqqqqqqqqqqqqqqqqqqqqq"));
	DrawDebugString(GetWorld(), Hit.ImpactPoint, fstr, nullptr, FColor::Green, 2.0f, true);
}

