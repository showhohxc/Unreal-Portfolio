// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraActor.h"
#include "Camera/CameraComponent.h"

AMainCameraActor::AMainCameraActor()
{
	//const FVector CameraLoc(550.0f, 3220.0f, 460.0f);
	//const FRotator CameraRot(0.0f, -30.0f, 180.0f);
	//const FVector CameraSca(1.0f, 1.0f, 1.0f);
	//const FTransform CameraTransform(CameraRot, CameraLoc, CameraSca);

	//m_MainCamera = GetCameraComponent();
	//m_MainCamera->SetRelativeTransform(CameraTransform);

	m_MainCamera = GetCameraComponent();
}

void AMainCameraActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AMainCameraActor::BeginPlay()"));

	//const FVector CameraLoc(550.0f, 3220.0f, 460.0f);
	//const FRotator CameraRot(0.0f, -30.0f, 180.0f);
	//const FVector CameraSca(1.0f, 1.0f, 1.0f);
	//const FTransform CameraTransform(CameraRot, CameraLoc, CameraSca);

	//m_MainCamera = GetCameraComponent();
	//m_MainCamera->SetRelativeTransform(CameraTransform);
}