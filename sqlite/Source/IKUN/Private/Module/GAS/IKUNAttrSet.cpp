#include "Module/GAS/IKUNAttrSet.h"
#include "GameplayEffectExtension.h"
#include "Module/GAS/IKUNASC.h"
#include "Net/UnrealNetwork.h"


UIKUNAttrSet::UIKUNAttrSet(): Health(100.f), MaxHealth(100.f), AttackPower(30.f) {
	
}

void UIKUNAttrSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);

	// 当调整最大生命值的时候要改变当前生命值
	if (Attribute == GetMaxHealthAttribute()) {
		AdjustAttributeForMaxChange(this->Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UIKUNAttrSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	// 调整当前声明值的时候让其不要超过最大生命值也不要为负
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}

void UIKUNAttrSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UIKUNAttrSet, Health)
	DOREPLIFETIME(UIKUNAttrSet, MaxHealth)
	DOREPLIFETIME(UIKUNAttrSet, AttackPower)
	DOREPLIFETIME(UIKUNAttrSet, Speed)
}

void UIKUNAttrSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
	const FGameplayAttribute& AffectedAttributeProperty) {
	UIKUNASC* asc = Cast<UIKUNASC>(GetOwningAbilitySystemComponent());
	const float curMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(curMaxValue, NewMaxValue) && asc) {
		const float curValue = AffectedAttribute.GetCurrentValue();
		float newDelta = (curMaxValue > 0.0f) ? (curValue * NewMaxValue / curMaxValue) - curValue : NewMaxValue;
		asc->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, newDelta);
	}
}

FGameplayAttribute UIKUNAttrSet::GetAttribute(FName Name) {
	FProperty* Prop = FindFieldChecked<FProperty>(StaticClass(), Name);
	return Prop;
}

void UIKUNAttrSet::OnRep_Health(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIKUNAttrSet, Health, OldValue)
}

void UIKUNAttrSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIKUNAttrSet, MaxHealth, OldValue)
}

void UIKUNAttrSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIKUNAttrSet, AttackPower, OldValue)
}

void UIKUNAttrSet::OnRep_Speed(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIKUNAttrSet, Speed, OldValue)
}
