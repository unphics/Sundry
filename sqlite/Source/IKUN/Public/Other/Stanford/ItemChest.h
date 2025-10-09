#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "GameFramework/Actor.h"
#include "ItemChest.generated.h"

UCLASS()
class IKUN_API AItemChest : public AActor, public IMyInterface{
	GENERATED_BODY()
	void Interact_Implementation(APawn* InstigatorPawn) override;
public:
	AItemChest();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TargetPitch;
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* BaseMesh; // 底座
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* LidMesh; // 盖子

};
