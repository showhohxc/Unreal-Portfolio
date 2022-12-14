// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MainCharacter.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	/*만약 애니메이션에 앞서 실행되는 게임 로직 단계에서 폰이 제거된다면 그 뒤에 실행되는 애니메이션 로직에서는 더 이상 유효하지 않은 폰 객체를 참조하는 사태가 발생할 것이다.
	그래서 이러한 사태를 방지하기 위해 애니메이션을 실행하기 전 폰이 유효한지 검사해야 한다. 이를 검사하는 명령이 TryGetPawnOwner()다.*/
	if (m_Pawn == nullptr)
	{
		m_Pawn = TryGetPawnOwner();

		if (m_Pawn)
		{
			m_Main = Cast<AMainCharacter>(m_Pawn);
		}
	}
}

void UMainAnimInstance::BeginPlayAnimationProperties()
{
	TCHAR* str = TEXT("Blueprint'/Game/BluePrint/CritterGameMode_BP.CritterGameMode_BP'");
	UBlueprintGeneratedClass* LoadBp = LoadObject<UBlueprintGeneratedClass>(nullptr, str, nullptr);
	//	AMain* MainBp = Cast<AMain>(LoadBp);
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if (m_Pawn == nullptr)
	{
		m_Pawn = TryGetPawnOwner();
	}

	if (m_Pawn)
	{
		FVector Speed = m_Pawn->GetVelocity();
		FVector LaterlaSpeed = FVector(Speed.X, Speed.Y, 0.f);
		m_fMoveMentSpeed = LaterlaSpeed.Size();

		//UE_LOG(LogTemp, Warning, TEXT("Character Speed : %f "), m_fMoveMentSpeed);

		m_bIsInAir = m_Pawn->GetMovementComponent()->IsFalling();

		if (m_Main == nullptr)
		{
			m_Main = Cast<AMainCharacter>(m_Pawn);
		}

		//UE_LOG(LogTemp, Warning, TEXT("JUMP State : %s"), m_bIsInAir ? TEXT("TRUE") : TEXT("FALSE") );
	}
}