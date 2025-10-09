#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "IKUNASC.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IKUN_API UIKUNASC : public UAbilitySystemComponent {
	GENERATED_BODY()
public:
	UIKUNASC();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	static UIKUNASC* GetASCFromActor(const AActor* Actor, bool LookForComponent = false);
};
