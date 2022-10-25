// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Reference to The UMG asset in the editor
	/// </summary>
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	///// <summary>
	///// Variable to hold the Widget after creating it
	///// </summary>
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	UUserWidget* HUDOverlay;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<class UUserWidget> wEnemyHealthBar;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	UUserWidget* EnemyHealthBar;

	bool bEnemyHealthBarVisible;

	void DisPlayEnemyHeathBar();
	void RemoveEnemyHeathBar();

	FVector EnemyLocation;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};
