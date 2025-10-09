// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Player/ExLoginPC.h"

void AExLoginPC::BeginPlay() {
	Super::BeginPlay();
	// 设置游戏窗口大小
	ConsoleCommand(FString::Printf(TEXT("r.setres %fx%fw"), this->ScreenSize.X, this->ScreenSize.Y));
	this->bShowMouseCursor = true;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	this->SetInputMode(InputMode);
}
