// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Components/InputComponent.h"
#include "AIController.h"
#include "MainCameraActor.h"

AMainPlayerController::AMainPlayerController()
{
	//m_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//m_FollowCamera->SetupAttachment(GetRootComponent());
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay(); 


	TArray<AActor*> ActorsToFind;
	TArray<AActor*> ActorsToFind2;

	// Test -> Null
	TestMainCharacterActor = Cast<AMainCharacter>(GetPawn());

	if (UWorld* World = GetWorld())
	{
		/*AActor* Main = UGameplayStatics::GetActorOfClass(GetWorld(), AMainCharacter::StaticClass());
		MainCameraActor = dynamic_cast<AMainCameraActor*>(Main);
		UE_LOG(LogTemp, Warning, TEXT("Get AMainCameraActor Name %s"), MainCameraActor);*/

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCameraActor::StaticClass(), ActorsToFind);
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCharacter::StaticClass(), ActorsToFind2);
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Get Actor Number %d"), ActorsToFind.Num());

	for (int i = 0; i < ActorsToFind.Num(); ++i)
	{
		MainCameraActor= dynamic_cast<AMainCameraActor*>(ActorsToFind[i]);
		UE_LOG(LogTemp, Warning, TEXT("Get AMainCameraActor Name %s"), *MainCameraActor->GetName());
	}

	//for (int i = 0; i < ActorsToFind.Num(); ++i)
	//{
	//	m_MainCharacterActor = dynamic_cast<AMainCharacter*>(ActorsToFind2[i]);
	//	UE_LOG(LogTemp, Warning, TEXT("Get AMainCharacter Name %s"), *m_MainCharacterActor->GetName());
	//}

	//for (AActor* CameraActor : ActorsToFind)
	//{
	//	//이 액터의 유형이 FireEffect 클래스인지 여부입니다.
	//	MainCameraActor = Cast<AMainCameraActor>(CameraActor);
	//	m_MainCharacterActor = Cast<AMainCharacter>(CameraActor);
	//	
	//	if (MainCameraActor)
	//	{
	//		//파이어 파티클 컴포넌트를 가져와 비활성화합니다.            
	//		//CameraActor->GetMainCameraComponent()
	//		UE_LOG(LogTemp, Warning, TEXT("Get CameraActor %s"), *MainCameraActor->GetName());
	//	}
	//	
	//	if (m_MainCharacterActor)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Get AMainCharacter %s"), *m_MainCharacterActor->GetName());
	//	}
	//}

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	//=================================================================================================

	//UWorld* World = GetWorld();

	//if (World)
	//{
	//	AMainCharacter* Main = Cast<AMainCharacter>(m_MainCharacterActor);

	//	UE_LOG(LogTemp, Warning, TEXT("MainCharacter State %s"), m_MainCharacterActor);

	//	if (Main)
	//	{
	//		Main->SpawnDefaultController();

	//		AAIController* AIController = Cast<AAIController>(Main->GetController());
	//		UE_LOG(LogTemp, Warning, TEXT("MainCharacter Controller %s"), AIController);

	//		if (AIController)
	//		{
	//			Main->AIController = AIController;
	//		}

	//		UE_LOG(LogTemp, Warning, TEXT("MainCharacter Controller State : %s  || %s"), AIController, Main);
	//	}
	//}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MainCharacterAttack_1", IE_Pressed, this, &AMainPlayerController::MainCharNoramlAttack);
}

void AMainPlayerController::MainCharNoramlAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("MainCharacter Normal Attack %s : Enemy Type : "), *m_EnemyCharacterActor->GetName());

	SetViewTargetWithBlend(m_MainCharacterActor);
	m_MainCharacterActor->MoveToTarget(m_EnemyCharacterActor);
}


