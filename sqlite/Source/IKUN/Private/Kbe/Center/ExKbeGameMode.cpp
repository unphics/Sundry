// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Center/ExKbeGameMode.h"

#include "KBEnginePlugins/Engine/KBEvent.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
AExKbeGameMode::AExKbeGameMode() {
	this->PrimaryActorTick.bCanEverTick = false;
}

void AExKbeGameMode::BeginPlay() {
	Super::BeginPlay();
	this->InstallEvent();
}

void AExKbeGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	this->UnInstallEvent();
}

void AExKbeGameMode::InstallEvent() {
	// 注册最基本的回调事件
	// 被踢出, 断线, 当前连接状态
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState)
	// 断线重连
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed)
}

void AExKbeGameMode::UnInstallEvent() {
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AExKbeGameMode::OnKicked(const UKBEventData* PEventData){
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExKbeGameMode::OnKicked, failed code: %i, errorStr: %s"), ServerData->failedcode, *ServerData->errorStr);
}

void AExKbeGameMode::OnDisconnected(const UKBEventData* PEventData) {
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExKbeGameMode::OnDisconnected, eventname: %s"), *ServerData->eventName)
}

void AExKbeGameMode::OnConnectionState(const UKBEventData* PEventData) {
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExKbeGameMode::OnConnectionState, success: %i, address: %s"), ServerData->success, *ServerData->address)
}

void AExKbeGameMode::OnReloginBaseappSuccessfully(const UKBEventData* PEventData) {
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExKbeGameMode::OnReloginBaseappSuccessfully, eventname: %s"), *ServerData->eventName)
	this->StopReloginBaseapp();
}

void AExKbeGameMode::OnReloginBaseappFailed(const UKBEventData* PEventData) {
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(PEventData);
	UE_LOG(LogTemp, Log, TEXT("AExKbeGameMode::OnReloginBaseappFailed, failed code: %i, errorStr: %s"), ServerData->failedcode, *ServerData->errorStr);
}

void AExKbeGameMode::StartReloginBaseapp() {
	if (!ReloginHandle.IsValid()) {
		this->GetWorld()->GetTimerManager().SetTimer(this->ReloginHandle, this, &AExKbeGameMode::OnReloginBaseappTimer, 1.f, true, 1.f);
	}
}

void AExKbeGameMode::StopReloginBaseapp() {
	if (!ReloginHandle.IsValid()) {
		this->GetWorld()->GetTimerManager().ClearTimer(this->ReloginHandle);
	}
}

void AExKbeGameMode::OnReloginBaseappTimer() {
	// 断线重连事件
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();
}
