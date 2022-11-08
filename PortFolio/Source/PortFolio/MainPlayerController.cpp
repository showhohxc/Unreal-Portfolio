// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainCameraActor.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCameraActor::StaticClass(), ActorsToFind);
	}

	for (AActor* MainCameraActor : ActorsToFind)
	{
		//�� ������ ������ FireEffect Ŭ�������� �����Դϴ�.
		AMainCameraActor* CameraActor = Cast<AMainCameraActor>(MainCameraActor);

		UE_LOG(LogTemp, Warning, TEXT("Get CameraActor %s"), *CameraActor->GetName());
		
		if (CameraActor)
		{
			//���̾� ��ƼŬ ������Ʈ�� ������ ��Ȱ��ȭ�մϴ�.            
			//CameraActor->GetMainCameraComponent()
			UE_LOG(LogTemp, Warning, TEXT("Get CameraActor %s"), *CameraActor->GetName());
		}
	}

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);


}