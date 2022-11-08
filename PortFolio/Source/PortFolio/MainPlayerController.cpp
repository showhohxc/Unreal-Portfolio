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
		//이 액터의 유형이 FireEffect 클래스인지 여부입니다.
		AMainCameraActor* CameraActor = Cast<AMainCameraActor>(MainCameraActor);

		UE_LOG(LogTemp, Warning, TEXT("Get CameraActor %s"), *CameraActor->GetName());
		
		if (CameraActor)
		{
			//파이어 파티클 컴포넌트를 가져와 비활성화합니다.            
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