#include "Other/Stanford/InteractionComponent.h"

#include "Animation/AnimInstanceProxy.h"
#include "Other/Stanford/MyInterface.h"

UInteractionComponent::UInteractionComponent() {
	PrimaryComponentTick.bCanEverTick = true;

}

void UInteractionComponent::BeginPlay() {
	Super::BeginPlay();

}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractionComponent::PrimaryInteract() {
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* OwnerActor = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerActor->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = FVector(EyeLocation + (EyeRotation.Vector() * 1500));

#if 0 // 线性检测示例
	FHitResult HitResult;
	bool bBlockedHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation,
		End, ObjectQueryParams);
	FColor LineColor = bBlockedHit ? FColor::Red : FColor::Green;
	AActor* HitActor = HitResult.GetActor();
	if (HitActor && HitActor->Implements<UMyInterface>()) {
		APawn* MyPawn = Cast<APawn>(OwnerActor);
		IMyInterface::Execute_Interact(HitActor, MyPawn);
	}
#else
	TArray<FHitResult> arrHitResult;
	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	bool bBlockedHit = GetWorld()->SweepMultiByObjectType(arrHitResult, EyeLocation,
		End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockedHit ? FColor::Red : FColor::Green;
	for(auto HitResult : arrHitResult) {
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<UMyInterface>()) {
			APawn* MyPawn = Cast<APawn>(OwnerActor);
			IMyInterface::Execute_Interact(HitActor, MyPawn);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint/*Hit冲击点*/, Radius, /*绘制的线的数量*/32, LineColor,
				/*连续*/false, 2.0f);
			break;
		}
	}
#endif
	DrawDebugLine(GetWorld(), EyeLocation, FVector(EyeLocation + (EyeRotation.Vector() * 1500)),
	LineColor, false , /*lifetime*/2.0f);
}

