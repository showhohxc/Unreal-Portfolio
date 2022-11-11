// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "MainCameraActor.h"

AMainPlayerController::AMainPlayerController()
{
	m_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_FollowCamera->SetupAttachment(GetRootComponent());
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay(); 

	m_FollowCamera = m_MainCharacterActor->m_FollowCamera;

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCameraActor::StaticClass(), ActorsToFind);
	}

	for (AActor* CameraActor : ActorsToFind)
	{
		//이 액터의 유형이 FireEffect 클래스인지 여부입니다.
		MainCameraActor = Cast<AMainCameraActor>(CameraActor);
		
		if (MainCameraActor)
		{
			//파이어 파티클 컴포넌트를 가져와 비활성화합니다.            
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