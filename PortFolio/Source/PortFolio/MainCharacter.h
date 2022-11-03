// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_NORMAL UMETA(DisplayName = "Normal"),
	EMS_SPRINTING UMETA(DisplaName = "Sprinting"),
	EMS_DEAD UMETA(DisplaName = "Dead"),

	EMS_max UMETA(DisplaName = "max"),
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_NORMAL UMETA(DisplayName = "Normal"),
	ESS_BELOWMINIUM UMETA(DisplaName = "BelowMinimum"),

	ESS_EXHAUSTED UMETA(DisplaName = "Exhausted"),
	ESS_EXHAUSTEDRECOVERING UMETA(DisplaName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplaName = "DefaultMax"),
};

UCLASS()
class PORTFOLIO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool bHasTarget) { bHasCombatTarget = bHasTarget; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Contoller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class USoundCue* HitSound;

	TArray<FVector> PickupLocations;

	UFUNCTION(BlueprintCallable)
		void ShowPickupLocations();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EMovementStatus MovemoentStatus;

	// Set Movemnt Status and Running Speed
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float fStaminaDrainRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float fMinSprintStamina;




	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Running")
		float fRunningSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Running")
		float fSprintingSpeed;





	bool bShiftKeyDown;

	void ShiftKeyDown();
	void ShiftKeyUp();


	bool bLMBDown;
	void LMBDown();
	void LMBUp();


	/*
	Camera Boom positioning the camera
*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_CameraBoom;


	/* FollowCamera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_FollowCamera;

	// Base Turn Rated to Scale Turning Functions for the Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float m_fBaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float m_fBaseLookUpRate;

	// Character Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float fMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float fHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float fMaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float fStamina;


	void DecrementHealth(float amount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
		void IncrementCoins(int32 amount);

	UFUNCTION(BlueprintCallable)
		void IncrementHealth(float amount);

	//static float ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf< class UDamageType > DamageTypeClass) override;

	//void Die();

	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);

	bool bMovingForward;
	bool bMovingRight;
	/*
		Called via input to turn at a given rate
		* @param Rate This ia a normalized rate, i.e, 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float rate);

	// 주어진 속도의 위아래를 찾는 사용 - 정규화된 비율
	void LookUpAtRate(float rate);

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return m_CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return m_FollowCamera; }

};
