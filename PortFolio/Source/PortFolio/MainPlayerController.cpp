// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "MainCameraActor.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay(); 

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCameraActor::StaticClass(), ActorsToFind);
	}

	for (AActor* CameraActor : ActorsToFind)
	{
		//�� ������ ������ FireEffect Ŭ�������� �����Դϴ�.
		MainCameraActor = Cast<AMainCameraActor>(CameraActor);
		
		if (MainCameraActor)
		{
			//���̾� ��ƼŬ ������Ʈ�� ������ ��Ȱ��ȭ�մϴ�.            
			//CameraActor->GetMainCameraComponent()
			UE_LOG(LogTemp, Warning, TEXT("Get CameraActor %s"), *MainCameraActor->GetName());
		}
	}

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);


}