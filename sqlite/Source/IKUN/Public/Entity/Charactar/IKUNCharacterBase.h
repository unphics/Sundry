#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include <vector>
#include "GameplayAbilitySpecHandle.h"
#include "IKUNCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

struct FGameplayAbilitySpecHandle;
class UIKUNAttrSet;
class UIKUNASC;

UCLASS()
class IKUN_API AIKUNCharacterBase : public ACharacter, public IAbilitySystemInterface{
	GENERATED_BODY()
public:
	AIKUNCharacterBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;
public:
	// TArray<FGameplayAbilitySpecHandle> GAHandleArray;
	std::vector<FGameplayAbilitySpecHandle> GAHandleArray;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS")
	UIKUNAttrSet* AttrSet;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS")
	UIKUNASC* ASC;
	
};