// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExKbeGameMode.generated.h"

class UKBEventData;
/**
 * 
 */
UCLASS()
class IKUN_API AExKbeGameMode : public AGameModeBase {
	GENERATED_BODY()
public:
	AExKbeGameMode();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 注册kbe事件
	virtual void InstallEvent();
	// 注销kbe事件
	virtual void UnInstallEvent();
	
	virtual void OnKicked(const UKBEventData* PEventData);
	virtual void OnDisconnected(const UKBEventData* PEventData);
	virtual void OnConnectionState(const UKBEventData* PEventData);
	virtual void OnReloginBaseappSuccessfully(const UKBEventData* PEventData);
	virtual void OnReloginBaseappFailed(const UKBEventData* PEventData);

	void StartReloginBaseapp();
	void StopReloginBaseapp();
	void OnReloginBaseappTimer();
protected:
	FTimerHandle ReloginHandle;
	
};
