#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "IKUNPCBase.generated.h"

class AIKUNCharacterBase;
class ACamera;
class UInputMapping;
class UInputMappingContext;
class UInputAction;

UCLASS()
class IKUN_API AIKUNPCBase: public APlayerController {
	GENERATED_BODY()
public: 
	AIKUNPCBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void BindIAAction(const UInputAction* Action, ETriggerEvent TriggerEvent, UObject* Object, FName FunctionName);
protected:
	UFUNCTION(BlueprintCallable)
	void InitCamera();
	
	void MoveForward(const FInputActionValue& InputValue);
	void MoveRight(const FInputActionValue& InputValue);
	void TurnAtRate(const FInputActionValue& InputValue);
	void LookUpAtRate(const FInputActionValue& InputValue);
	void OnJump(const FInputActionValue& InputValue);
	void OnStopJump(const FInputActionValue& InputValue);
	void Test(const FInputActionValue& InputValue);
public:
	// TODO 更换为IKUNCharacterBase
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AIKUNCharacterBase* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACamera> CameraActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACamera* ViewCamera;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	bool bAutoBindMoveInput = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true")) // AllowPrivateAccess允许访问私有
	TObjectPtr<UInputMappingContext> IMC_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMC_MoveBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_MoveForward_Backward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_MoveRight_Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_TurnRight_Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_LookUp_Down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Jump;
};
