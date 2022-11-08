// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortFolioGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API APortFolioGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APortFolioGameModeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_MainFlowCamera;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cameras")
	//class AMainCameraActor* MainCameraActor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	//TSubclassOf<class AMainCameraActor> TCameraActor;

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
