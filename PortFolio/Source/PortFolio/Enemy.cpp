// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "MainPlayerController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraBoom->SetupAttachment(GetRootComponent());
	m_CameraBoom->TargetArmLength = 400.f;	// 카메라와 플레이어 거리
	m_CameraBoom->bUsePawnControlRotation = true;	// 컨트롤러 기반 팔 회전

	// Create Folow Camera
	m_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_FollowCamera->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);
	m_FollowCamera->bUsePawnControlRotation = false;


	m_CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ComBatCollision"));
	m_CombatCollision->SetupAttachment(GetMesh(), FName("EnemySocket"));

	EnemyMovementStatus = EEnemyMovemntStatus::EMS_IDLE;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AIController = Cast<AAIController>(GetController());

	m_CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	m_CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("EnemyCharacterAttack_1", IE_Pressed, this, &AEnemy::NormalAttack);
}

void AEnemy::NormalAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("AEnemy Normal Attack "));
}

void AEnemy::MoveToTarget(class AMainCharacter* Target)
{
	SetEnemyMovementStatus(EEnemyMovemntStatus::EMS_MoveToTarget);

	if (AIController)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveToTarget()"));
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		// 오브젝트와의 충돌 사이 자간??
		MoveRequest.SetAcceptanceRadius(25.0f);

		FNavPathSharedPtr NavPath;

		AIController->MoveTo(MoveRequest, &NavPath);

		//TArray<FNavPathPoint> PathPoints = NavPath->GetPathPoints();
		/* 나중에 사용하자 */
		//auto PathPoints = NavPath->GetPathPoints();

		//for (auto Point : PathPoints)
		//{
		//	//FNavLocation
		//	FVector Location = Point.Location;

		//	UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Red, 15.f, 1.5f);
		//}
	}
}

