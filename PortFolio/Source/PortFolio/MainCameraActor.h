// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AMainCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	AMainCameraActor();

	class UCameraComponent* m_MainCamera;
	UCameraComponent* GetMainCameraComponent() const { return m_MainCamera; }

protected:
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
};
