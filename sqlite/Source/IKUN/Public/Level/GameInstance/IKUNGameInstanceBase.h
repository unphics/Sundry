// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JsEnv/Private/ContainerWrapper.h"
#include "IKUNGameInstanceBase.generated.h"

namespace puerts {
	class FJsEnv;
}

/**
 * 
 */
UCLASS()
class IKUN_API UIKUNGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	// 初始化顺序引擎启动时会执行一次PostInitProperties，然后play时PostInitProperties->Init->OnStart
	virtual void PostInitProperties() override;
	virtual void Init() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;
private:
	TSharedPtr<puerts::FJsEnv> JsEnv;
};
