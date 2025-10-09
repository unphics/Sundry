#include "Entity/Charactar/IKUNCharacterBase.h"
#include "Control/Player/IKUNPCBase.h"
#include "Module/GAS/IKUNASC.h"
#include "Module/GAS/IKUNAttrSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/GameplayAbility_CharacterJump.h"

AIKUNCharacterBase::AIKUNCharacterBase() {
	PrimaryActorTick.bCanEverTick = true;
	
	this->AttrSet = CreateDefaultSubobject<UIKUNAttrSet>("IKUNAttrSet");

	this->ASC = CreateDefaultSubobject<UIKUNASC>("ASC");
	this->ASC->SetIsReplicated(true);

	this->bUseControllerRotationYaw = false;

	this->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AIKUNCharacterBase::BeginPlay() {
	Super::BeginPlay();
	
}

void AIKUNCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AIKUNCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AIKUNCharacterBase::GetAbilitySystemComponent() const {
	return this->ASC;
}

void AIKUNCharacterBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	if (AIKUNPCBase* PC = Cast<AIKUNPCBase>(NewController)) {
		PC->OwnerCharacter = this;
	}
	if (this->ASC) {
		FGameplayAbilitySpecHandle hanle = this->ASC->GiveAbility(FGameplayAbilitySpec(UGameplayAbility_CharacterJump::StaticClass(), 1, 1, this));
		// this->GAHandleArray.Add(hanle);
		this->GAHandleArray.push_back(hanle);
	}
}
