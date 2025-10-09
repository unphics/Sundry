#include "Module/Utils/BPFuncLib.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Module/Utils/UtilType.h"

UUserWidget* UBPFuncLib::CreateWidget(UWorld* World, UClass* Class) {
	return ::CreateWidget<UUserWidget>(World, Class);
}

void UBPFuncLib::BindAction(UEnhancedInputComponent* EnhancedInputComp, const UInputAction* Action,
	ETriggerEvent TriggerEvent, UObject* Object, FName FunctionName) {
	FEnhancedInputActionEventBinding& binding = EnhancedInputComp->BindAction(Action, TriggerEvent, Object, FunctionName);
	if (&binding == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Failed to bind action"))
	}
}

FGameplayTag UBPFuncLib::RequestGameplayTag(FName TagName) {
	return FGameplayTag::RequestGameplayTag(TagName);
}

void UBPFuncLib::AddTagToContainer(FGameplayTagContainer& Container, FGameplayTag& Tag) {
	Container.AddTag(Tag);
}

AActor* UBPFuncLib::SpawnActor(UWorld* World, UClass* Class, FTransform Transform, const FSpawnParamters& Param) {
	FActorSpawnParameters param;
	param.Name = Param.Name;
	param.Owner = Param.Owner;
	param.Instigator = Param.Instigator;
	param.Template = Param.TemplateActor;
	param.SpawnCollisionHandlingOverride = Param.CollisionHandling;
	param.OverrideLevel = Param.OverrideLevel;
	return World->SpawnActor(Class, &Transform, param);
}

FQuat UBPFuncLib::MakeQuatFromRot(FRotator& Rot) {
	return Rot.Quaternion();
}
