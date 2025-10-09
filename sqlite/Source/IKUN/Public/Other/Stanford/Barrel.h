#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"


class URadialForceComponent;

UCLASS()
class IKUN_API ABarrel : public AActor {
	GENERATED_BODY()
public:
	ABarrel();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URadialForceComponent* RadialForceComp;
	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
