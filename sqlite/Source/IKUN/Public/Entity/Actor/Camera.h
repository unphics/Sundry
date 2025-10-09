#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

class AIKUNPCBase;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class IKUN_API ACamera : public AActor {
	GENERATED_BODY()
public:
	ACamera();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;
	
};
