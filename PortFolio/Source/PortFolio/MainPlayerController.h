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
	AMainPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class AMainCameraActor* MainCameraActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class AMainCharacter* m_MainCharacterActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class AEnemy* m_EnemyCharacterActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* m_FollowCamera;


	AMainCharacter* TestMainCharacterActor;
	void MainCharNoramlAttack();
	void EnemyCharNoramlAttack();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
