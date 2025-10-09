// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExLoginPC.generated.h"

/**
 * 
 */
UCLASS()
class IKUN_API AExLoginPC : public APlayerController {
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	FVector2D ScreenSize;
};
