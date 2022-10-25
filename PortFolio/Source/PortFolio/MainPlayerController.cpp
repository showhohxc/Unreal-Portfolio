// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//if (HUDOverlayAsset)
	//{
	//	HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	//}

	//HUDOverlay->AddToViewport();
	//HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	//if (wEnemyHealthBar)
	//{
	//	EnemyHealthBar = CreateWidget<UUserWidget>(this, wEnemyHealthBar);

	//	if (EnemyHealthBar)
	//	{
	//		EnemyHealthBar->AddToViewport();
	//		EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
	//	}

	//	FVector2D Aligment(0, 0);
	//	EnemyHealthBar->SetAlignmentInViewport(Aligment);
	//}

}


void AMainPlayerController::DisPlayEnemyHeathBar()
{
	//if (EnemyHealthBar)
	//{
	//	bEnemyHealthBarVisible = true;
	//	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
	//}
}

void AMainPlayerController::RemoveEnemyHeathBar()
{
	//if (EnemyHealthBar)
	//{
	//	bEnemyHealthBarVisible = false;
	//	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
	//}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (EnemyHealthBar)
	//{
	//	FVector2D PositionViewPort;
	//	ProjectWorldLocationToScreen(EnemyLocation, PositionViewPort);
	//	PositionViewPort.Y -= 85.0f;

	//	FVector2D SizeViewPort = FVector2D(550.0f, 25.0f);

	//	EnemyHealthBar->SetPositionInViewport(PositionViewPort);
	//	EnemyHealthBar->SetDesiredSizeInViewport(SizeViewPort);
	//}
}