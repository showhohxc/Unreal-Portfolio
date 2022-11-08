// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "PortFolioGameModeBase.h"
#include "MainCameraActor.h"
#include "Camera/CameraComponent.h"

APortFolioGameModeBase::APortFolioGameModeBase()
{
	m_MainFlowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainFlowCamera"));
	m_MainFlowCamera->SetupAttachment(GetRootComponent());


}

void APortFolioGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const FVector CameraLoc(550.0f, 3220.0f, 460.0f);
	const FRotator CameraRot(0.0f, -30.0f, 180.0f);
	const FVector CameraSca(1.0f, 1.0f, 1.0f);
	const FTransform CameraTransform(CameraRot, CameraLoc, CameraSca);

	m_MainFlowCamera->SetRelativeTransform(CameraTransform);

	/*MainCameraActor = Cast<AMainCameraActor>(TCameraActor);*/
	//MainCameraActor->SetCameraData();
}

void APortFolioGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Warning, TEXT("APortFolioGameModeBase::InitGame %s"), *ErrorMessage);
}