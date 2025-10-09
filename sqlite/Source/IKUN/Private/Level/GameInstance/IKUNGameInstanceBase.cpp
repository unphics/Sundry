#include "Level/GameInstance/IKUNGameInstanceBase.h"
#include "JsEnv.h"

void UIKUNGameInstanceBase::PostInitProperties() {
	Super::PostInitProperties();
	
	UE_LOG(LogTemp,Log,TEXT("======= GameInstance PostInitProperties ======="));
}

void UIKUNGameInstanceBase::Init() {
	Super::Init();
	
	UE_LOG(LogTemp,Log,TEXT("======= GameInstance Init ======="));
}

void UIKUNGameInstanceBase::OnStart() {
	Super::OnStart();

	UE_LOG(LogTemp,Log,TEXT("======= GameInstance OnStart ======="));
	
	// this->JsEnv = MakeShared<puerts::FJsEnv>();
	// TArray<TPair<FString, UObject*>> Arguments;
	// Arguments.Add(TPair<FString, UObject*>(TEXT("GameInstance"), this));
	// JsEnv->Start("GameInit", Arguments);
	
	
}

void UIKUNGameInstanceBase::Shutdown() {
	Super::Shutdown();

	UE_LOG(LogTemp,Log,TEXT("======= GameInstance Shutdown ======="));
}
