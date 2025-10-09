// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Center/ExLoginGameMode.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kbe/Center/ExClient.h"
#include "Kbe/HUD/ExLoginWidget.h"
#include "KBEnginePlugins/Engine/KBDebug.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AExLoginGameMode::InstallEvent() {
	Super::InstallEvent();
	// 创建用户入口实体回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	// 登录失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	// 版本匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	// 版本不匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	// 登录Baseapp失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//登录baseapp回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	// 登录成功回调，生成account后在__init__()时调用，在这里跳转到选择角色场景
	KBENGINE_REGISTER_EVENT("OnLoginSuccessfully", OnLoginSuccessfully);

}

void AExLoginGameMode::BeginPlay() {
	// 每次进入到登录界面时先清理一次KBE, 否则kbe插件缓存内容会一直存在
	KBEngine::KBEngineApp::getSingleton().reset();
	Super::BeginPlay();
	this->LoginWidget = CreateWidget<UExLoginWidget>(this->GetWorld(), this->ClassLoginWidget);
	this->LoginWidget->AddToViewport();
	this->LoginWidget->LoginGM = this;
	this->LoginWidget->InitWidget();
	for (TActorIterator<AExClient> It(this->GetWorld());It;++It) {
		this->KbeMain = (*It)->KBEMain;
	}
}

void AExLoginGameMode::OnCreateAccountResult(const UKBEventData* PEventData) {
	const UKBEventData_onCreateAccountResult* SvrData = Cast<UKBEventData_onCreateAccountResult>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnCreateAccountResult, errorcode: %i, errorstr: %s"), SvrData->errorCode, *SvrData->errorStr)
}

void AExLoginGameMode::OnLoginFailed(const UKBEventData* PEventData) {
	const UKBEventData_onLoginFailed* SvrData = Cast<UKBEventData_onLoginFailed>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnLoginFailed, failedcode: %i, errorstr: %s"), SvrData->failedcode, *SvrData->errorStr)
}

void AExLoginGameMode::OnVersionNotMatch(const UKBEventData* PEventData) {
	const UKBEventData_onVersionNotMatch* SvrData = Cast<UKBEventData_onVersionNotMatch>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnVersionNotMatch, clientVersion: %s, serverVersion: %s"), *SvrData->clientVersion, *SvrData->serverVersion)
}

void AExLoginGameMode::OnScriptVersionNotMatch(const UKBEventData* PEventData) {
	const UKBEventData_onScriptVersionNotMatch* SvrData = Cast<UKBEventData_onScriptVersionNotMatch>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnScriptVersionNotMatch, clientScriptVersion: %s, serverScriptVersion: %s"), *SvrData->clientScriptVersion, *SvrData->serverScriptVersion)
}

void AExLoginGameMode::OnLoginBaseappFailed(const UKBEventData* PEventData) {
	const UKBEventData_onCreateAccountResult* SvrData = Cast<UKBEventData_onCreateAccountResult>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnLoginBaseappFailed, errorcode: %i, errorstr: %s"), SvrData->errorCode, *SvrData->errorStr)
}

void AExLoginGameMode::OnLoginBaseapp(const UKBEventData* PEventData) {
	const UKBEventData_onLoginBaseapp* SvrData = Cast<UKBEventData_onLoginBaseapp>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnLoginBaseapp, eventName: %s"), *SvrData->eventName)
}

void AExLoginGameMode::OnLoginSuccessfully(const UKBEventData* PEventData) {
	const UKBEventData_onLoginSuccessfully* SvrData = Cast<UKBEventData_onLoginSuccessfully>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExLoginGameMode::OnLoginSuccessfully, entity_uuid: %llu, errorstr: %i"), SvrData->entity_uuid, SvrData->entity_id)
	UGameplayStatics::OpenLevel(this->GetWorld(), FName("RoleMap"));
}
