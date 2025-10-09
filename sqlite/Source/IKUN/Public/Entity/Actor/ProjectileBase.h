#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class IKUN_API AProjectileBase : public AActor {
	GENERATED_BODY()
public:
	AProjectileBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION(BlueprintCallable)
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMoveComp;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSysComp;
};
