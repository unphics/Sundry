// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/HUD/ExLoginWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kbe/Center/ExLoginGameMode.h"
#include "KBEnginePlugins/Engine/KBEMain.h"

void UExLoginWidget::InitWidget() {
	this->TxtClientVersion->SetText(FText::FromString("Client Version :" + UKBEMain::getClientVersion()));
	this->TxtClientScriptVersion->SetText(FText::FromString("Client Script Version :" + UKBEMain::getClientScriptVersion()));
	this->TxtServerVersion->SetText(FText::FromString("Server Version :" + UKBEMain::getServerVersion()));
	this->TxtServerScriptVersion->SetText(FText::FromString("Server Script Version :" + UKBEMain::getServerScriptVersion()));
	
}
void UExLoginWidget::LoginEvent() {
	FString UserName = this->EditUserName->GetText().ToString();
	FString UserPwd = this->EditUserPwd->GetText().ToString();
	if (UserName.IsEmpty() || UserPwd.IsEmpty()) {
		return;
	}
	TArray<uint8> LoginData;
	FString ProjName("KBECrousePro");
	for (int i = 0; i < ProjName.Len(); ++i) {
		LoginData.Add((uint8)ProjName[i]);
	}
	this->LoginGM->KbeMain->login(UserName, UserPwd, LoginData);
}
void UExLoginWidget::RegEvent() {
	FString UserName = this->EditUserName->GetText().ToString();
	FString UserPwd = this->EditUserPwd->GetText().ToString();
	if (UserName.IsEmpty() || UserPwd.IsEmpty()) {
		return;
	}
	TArray<uint8> LoginData;
	FString ProjName("KBECrousePro");
	for (int i = 0; i < ProjName.Len(); ++i) {
		LoginData.Add((uint8)ProjName[i]);
	}
	this->LoginGM->KbeMain->createAccount(UserName, UserPwd, LoginData);
}
