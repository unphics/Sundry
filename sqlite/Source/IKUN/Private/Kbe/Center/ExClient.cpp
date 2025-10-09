// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Center/ExClient.h"
#include "KBEnginePlugins/Engine/KBEMain.h"

// Sets default values
AExClient::AExClient() {
	PrimaryActorTick.bCanEverTick = false;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	this->KBEMain = CreateDefaultSubobject<UKBEMain>(TEXT("UKBEMain"));
}

// Called when the game starts or when spawned
void AExClient::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AExClient::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

