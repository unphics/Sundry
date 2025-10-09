// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExClient.generated.h"

class UKBEMain;

UCLASS()
class IKUN_API AExClient : public AActor {
	GENERATED_BODY()
public:
	AExClient();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere)
	UKBEMain* KBEMain;
};
