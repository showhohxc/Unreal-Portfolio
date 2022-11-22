// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
//#include "Weapon.h"
#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"
#include "MainPlayerController.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraBoom->SetupAttachment(GetRootComponent());
	m_CameraBoom->TargetArmLength = 400.f;	// 카메라와 플레이어 거리
	m_CameraBoom->bUsePawnControlRotation = true;	// 컨트롤러 기반 팔 회전

	GetCapsuleComponent()->SetCapsuleSize(48.f, 80.f);

	// Create Folow Camera
	m_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_FollowCamera->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);

	//m_FollowCamera->SetRelativeLocation(FVector(-100, 0, 300));
	//m_FollowCamera->SetRelativeRotation(FRotator(-45, 0, 0));

	m_FollowCamera->bUsePawnControlRotation = false;

	// Set Our TurnRate Trun
	m_fBaseTurnRate = 65.f;
	m_fBaseLookUpRate = 65.f;

	// 카메라에 영향을 미친다
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;  // 입력방향으로 캐릭터 이동
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);	// 캐릭터 회전 속도
	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = .2f;//공중 제어

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(GetController());

	AIController = Cast<AAIController>(GetController());
	UE_LOG(LogTemp, Warning, TEXT("MainCharacter BeginPlay AIController %s : "), AIController);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (MovemoentStatus == EMovementStatus::EMS_DEAD) return;

	//float DeltaStamina = fStaminaDrainRate * DeltaTime;

	//switch (StaminaStatus)
	//{
	//case EStaminaStatus::ESS_NORMAL:
	//{
	//	if (bShiftKeyDown)
	//	{
	//		if (fStamina - DeltaStamina <= fMinSprintStamina)
	//		{
	//			SetStaminaStatus(EStaminaStatus::ESS_BELOWMINIUM);
	//			fStamina -= DeltaStamina;
	//		}
	//		else
	//		{
	//			fStamina -= DeltaStamina;
	//		}

	//		if (bMovingForward || bMovingRight)
	//		{
	//			SetMovementStatus(EMovementStatus::EMS_SPRINTING);
	//		}
	//		else
	//		{
	//			SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//		}
	//	}
	//	else
	//	{
	//		// Shift Up
	//		if (fStamina + DeltaStamina >= fMaxStamina)
	//		{
	//			fStamina = fMaxStamina;
	//		}
	//		else
	//		{
	//			fStamina += DeltaStamina;
	//		}

	//		SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//	}

	//} break;

	//case EStaminaStatus::ESS_BELOWMINIUM:
	//{
	//	if (bShiftKeyDown)
	//	{
	//		if (fStamina - DeltaStamina <= 0.0f)
	//		{
	//			SetStaminaStatus(EStaminaStatus::ESS_EXHAUSTED);
	//			fStamina = 0;
	//			SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//		}
	//		else
	//		{
	//			fStamina -= DeltaStamina;

	//			if (bMovingForward || bMovingRight)
	//			{
	//				SetMovementStatus(EMovementStatus::EMS_SPRINTING);
	//			}
	//			else
	//			{
	//				SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		// Shift up
	//		if (fStamina + DeltaStamina >= fMinSprintStamina)
	//		{
	//			SetStaminaStatus(EStaminaStatus::ESS_NORMAL);
	//			fStamina += DeltaStamina;
	//		}
	//		else
	//		{
	//			fStamina += DeltaStamina;
	//		}

	//		SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//	}
	//} break;

	//case EStaminaStatus::ESS_EXHAUSTED:
	//{
	//	if (bShiftKeyDown)
	//	{
	//		fStamina = 0.0f;
	//	}
	//	else
	//	{
	//		SetStaminaStatus(EStaminaStatus::ESS_EXHAUSTEDRECOVERING);
	//		fStamina += DeltaStamina;
	//	}

	//	SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//} break;

	//case EStaminaStatus::ESS_EXHAUSTEDRECOVERING:
	//{
	//	if (fStamina + DeltaStamina >= fMinSprintStamina)\
	//	{
	//		SetStaminaStatus(EStaminaStatus::ESS_NORMAL);
	//		fStamina += DeltaStamina;
	//	}
	//	else
	//	{
	//		fStamina += DeltaStamina;
	//	}

	//	SetMovementStatus(EMovementStatus::EMS_NORMAL);
	//} break;

	//default:;
	//}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftKeyUp);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);

	/*PlayerInputComponent->BindAction(TEXT("MouseRight"), IE_Pressed, this, &AMain::InputRightClickPressed);
	PlayerInputComponent->BindAction(TEXT("MouseRight"), IE_Released, this, &AMain::InputRightClickReleased);*/
}

void AMainCharacter::MoveForward(float value)
{
	bMovingForward = false;

	if (Controller != nullptr && value != 0.f/* && (!bAttacking)*/ && (MovemoentStatus != EMovementStatus::EMS_DEAD))
	{
		// 캐릭터의 앞방향 위치를 찾는다.
		const FRotator Rot = Controller->GetControlRotation();		// 절대축 기준 회전값
		const FRotator YawRotation(0.f, Rot.Yaw, 0.f);
		// 순 방향 FRotMatrix 시스템으로 인하여 회전을 얻고 그 회전으로부터 전방 벡터를 구한다.

		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// 회전값을 행렬로 변환 -> 절대축 기준 회전값 가져오기 : X축 기준으로 얼마나 회전되었는지 계산
		AddMovementInput(Dir, value);

		UE_LOG(LogTemp, Warning, TEXT("MoveForward State : %f"), value);

		//FVector fForward = GetActorForwardVector();
		//AddMovementInput(fForward, value);

		bMovingForward = true;
	}
}

void AMainCharacter::MoveRight(float value)
{
	bMovingRight = false;

	if (Controller != nullptr && value != 0.f /*&& (!bAttacking)*/ && (MovemoentStatus != EMovementStatus::EMS_DEAD))
	{
		// 캐릭터의 앞방향 위치를 찾는다.
		const FRotator Rot = Controller->GetControlRotation();		// 절대축 기준 회전값
		const FRotator YawRotation(0.f, Rot.Yaw, 0.f);
		// 순 방향 FRotMatrix 시스템으로 인하여 회전을 얻고 그 회전으로부터 전방 벡터를 구한다.

		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// 회전값을 행렬로 변환 -> 절대축 기준 회전값 가져오기 : Y축 기준으로 얼마나 회전되었는지 계산
		AddMovementInput(Dir, value);

		/*FVector fRight = GetActorRightVector();
		AddMovementInput(fRight, value);*/
		bMovingRight = true;
	}
}


// 입력을 받아 축에서 컨트롤러를 구체적으로 회전하는 기능
void AMainCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * m_fBaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * m_fBaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AMainCharacter::LMBDown()
{
	bLMBDown = true;

	if (MovemoentStatus == EMovementStatus::EMS_DEAD) return;

	//if (ActiveOverlappingItem)
	//{
	//	AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);

	//	if (Weapon)
	//	{
	//		Weapon->Equip(this);
	//		SetActiveOverlappingItem(nullptr);
	//	}
	//}
	//else if (m_EquippedWeapon)	// 무기를 가지고 있다면
	//{
	//	Attack();
	//}
}

void AMainCharacter::LMBUp()
{
	bLMBDown = false;
}


void AMainCharacter::DecrementHealth(float amount)
{
	if (fHealth - amount <= 0.0f)
	{
		fHealth -= amount;
		//Die();
	}
	else
	{
		fHealth -= amount;
	}
}

void AMainCharacter::IncrementCoins(int32 amount)
{
	//nCoins += amount;
}

void AMainCharacter::IncrementHealth(float amount)
{
	if (fHealth + amount >= fMaxHealth)
	{
		fHealth = fMaxHealth;
	}
	else
	{
		fHealth += amount;
	}
}

//void AMainCharacter::Die()
//{
//	if (MovemoentStatus == EMovementStatus::EMS_DEAD) return;
//
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//
//	if (AnimInstance && CombatMontage)
//	{
//		AnimInstance->Montage_Play(CombatMontage, 1.0f);		// 값이 낮을수록 느리게
//		AnimInstance->Montage_JumpToSection(FName("Death"));
//	}
//
//	SetMovementStatus(EMovementStatus::EMS_DEAD);
//
//	//if (GetCombatTarget())
//	//{
//	//	GetCombatTarget()->GetMesh()->bPauseAnims = true;
//	//}
//}

void AMainCharacter::Jump()
{
	if (MovemoentStatus != EMovementStatus::EMS_DEAD)
	{
		//Super::Jump();
	}
}

/*void AMainCharacter::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
}*/

void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovemoentStatus = Status;

	if (MovemoentStatus == EMovementStatus::EMS_SPRINTING)
	{
		GetCharacterMovement()->MaxWalkSpeed = fSprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = fRunningSpeed;
	}
}

void AMainCharacter::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

void AMainCharacter::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

void AMainCharacter::ShowPickupLocations()
{
	//for (int i = 0; i < PickupLocations.Num(); ++i)
	//{
	//	UKismetSystemLibrary::DrawDebugSphere(this, PickupLocations[i], 25.f, 8, FLinearColor::Green, 15.f, .25f);
	//}	

	/*for (auto Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Green, 15.f, .25f);
	}*/

	for (FVector Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Green, 15.f, .25f);
	}
}

//void AMainCharacter::SetEquippedWeapon(AWeapon* WeaponToSet)
//{
//	if (m_EquippedWeapon)
//	{
//		m_EquippedWeapon->Destroy();
//	}
//
//	m_EquippedWeapon = WeaponToSet;
//}
//
//void AMainCharacter::Attack()
//{
//	if (!bAttacking && MovemoentStatus != EMovementStatus::EMS_DEAD)
//	{
//		SetInterToEnemy(true);
//
//		bAttacking = true;
//
//		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//
//		if (AnimInstance && CombatMontage)
//		{
//			int nSelection = FMath::RandRange(0, 1);
//
//			switch (nSelection)
//			{
//			case 0:
//			{
//				AnimInstance->Montage_Play(CombatMontage, 2.3f);		// 값이 낮을수록 느리게
//				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
//			} break;
//			case 1:
//			{
//				AnimInstance->Montage_Play(CombatMontage, 1.8f);
//				AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
//			} break;
//			}
//		}
//
//		/*if (m_EquippedWeapon->SwingSound)
//		{
//			UGameplayStatics::PlaySound2D(this, m_EquippedWeapon->SwingSound);
//		}*/
//	}
//}
//
//void AMainCharacter::AttackEnd()
//{
//	bAttacking = false;
//	SetInterToEnemy(false);
//
//	if (bLMBDown)
//	{
//		Attack();
//	}
//}
//
//void AMainCharacter::PlaySwingSound()
//{
//	if (m_EquippedWeapon->SwingSound)
//		UGameplayStatics::PlaySound2D(this, m_EquippedWeapon->SwingSound);
//}
//
//void AMainCharacter::SetInterToEnemy(bool bInterp)
//{
//	bInterToEnemy = bInterp;
//}

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	//DecrementHealth(DamageAmount);

	//if (fHealth - DamageAmount <= 0.0f)
	//{
	//	fHealth -= DamageAmount;
	//	Die();

	//	if (DamageCauser)
	//	{
	//		AEnemy* Enemy = Cast<AEnemy>(DamageCauser);

	//		if (Enemy)
	//		{
	//			Enemy->bHasValidTarget = false;
	//		}
	//	}
	//}
	//else
	//{
	//	fHealth -= DamageAmount;
	//}

	return DamageAmount;
}

//void AMainCharacter::UpdateCombatTarget()
//{
//	TArray<AActor*> OverlappingActors;
//
//	GetOverlappingActors(OverlappingActors, EnemyFillter);
//
//	if (OverlappingActors.Num() == 0)
//	{
//		if (MainPlayerController)
//		{
//			MainPlayerController->RemoveEnemyHeathBar();
//		}
//
//		return;
//	}
//
//	AEnemy* ClosestEnemy = Cast<AEnemy>(OverlappingActors[0]);
//
//	if (ClosestEnemy)
//	{
//		FVector Location = GetActorLocation();
//		float MinDistance = (ClosestEnemy->GetActorLocation() - Location).Size();
//
//		for (auto Actor : OverlappingActors)
//		{
//			AEnemy* Enemy = Cast<AEnemy>(Actor);
//
//			if (Enemy)
//			{
//				float fDistanceToActor = (Enemy->GetActorLocation() - Location).Size();
//
//				if (fDistanceToActor < MinDistance)
//				{
//					MinDistance = fDistanceToActor;
//					ClosestEnemy = Enemy;
//				}
//			}
//		}
//
//		if (MainPlayerController)
//		{
//			MainPlayerController->DisPlayEnemyHeathBar();
//		}
//
//		SetCombatTarget(ClosestEnemy);
//		bHasCombatTarget = true;
//	}
//}

void AMainCharacter::MoveToTarget(class AEnemy* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("MainCharacter AIController %s : "), AIController);

	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("MainCharacter to Enemy MoveToTarget()"));

		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		// 오브젝트와의 충돌 사이 자간??
		MoveRequest.SetAcceptanceRadius(25.0f);

		FNavPathSharedPtr NavPath;

		AIController->MoveTo(MoveRequest, &NavPath);
	}
}