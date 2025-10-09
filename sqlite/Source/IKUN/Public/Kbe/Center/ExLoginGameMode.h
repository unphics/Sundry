// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kbe/Center/ExKbeGameMode.h"
#include "ExLoginGameMode.generated.h"

class UKBEMain;
class UExLoginWidget;
class UKBEventData;
/**
 * 
 */
UCLASS()
class IKUN_API AExLoginGameMode : public AExKbeGameMode {
	GENERATED_BODY()
public:
	virtual void InstallEvent() override;
	virtual void BeginPlay() override;
	
	void OnCreateAccountResult(const UKBEventData* PEventData);
	void OnLoginFailed(const UKBEventData* PEventData);
	void OnVersionNotMatch(const UKBEventData* PEventData);
	void OnScriptVersionNotMatch(const UKBEventData* PEventData);
	void OnLoginBaseappFailed(const UKBEventData* PEventData);
	void OnLoginBaseapp(const UKBEventData* PEventData);
	void OnLoginSuccessfully(const UKBEventData* PEventData);
public:
	UKBEMain* KbeMain;
protected:
	UExLoginWidget*	LoginWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UExLoginWidget> ClassLoginWidget;
	
};
