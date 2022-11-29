// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "AIController.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (Actor_1 && Actor_2)
	{
		SpawnArray.Add(Actor_1);
		SpawnArray.Add(Actor_2);
	}
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()
{
	FVector Extent = m_SpawningBox->GetScaledBoxExtent();
	FVector origin = m_SpawningBox->GetComponentLocation();
	FVector point = UKismetMathLibrary::RandomPointInBoundingBox(origin, Extent);
	return origin;
}

void ASpawnVolume::SpawnOurActor_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld();
		FActorSpawnParameters SpawnParams;

		if (World)
		{
			AActor* Actor = World->SpawnActor<AActor>(ToSpawn, Location, FRotator(0), SpawnParams);
			AEnemy* Enemy = Cast<AEnemy>(Actor);

			if (Enemy)
			{
				Enemy->SpawnDefaultController();

				AAIController* AIController = Cast<AAIController>(Enemy->GetController());

				if (AIController)
				{
					Enemy->AIController = AIController;
				}

				UE_LOG(LogTemp, Warning, TEXT("Enemy Controller State : %s  || %s"), AIController, Enemy);
			}
		}
	}
}

TSubclassOf<AActor> ASpawnVolume::GetSpawnActor()
{
	if (SpawnArray.Num() > 0)
	{
		int nSelection = FMath::RandRange(0, SpawnArray.Num() - 1);

		return SpawnArray[nSelection];
	}
	else
	{
		return nullptr;
	}
}