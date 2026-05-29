// Fill out your copyright notice in the Description page of Project Settings.


#include "RESTOREAIController.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/EngineerCharacter.h"
#include "TimerManager.h"

ARESTOREAIController::ARESTOREAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARESTOREAIController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(TimerHandle_Chase, this, &ARESTOREAIController::ModeChaseMultiplayer, 0.5f, true);
	}
}

void ARESTOREAIController::ModeChaseMultiplayer()
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	TArray<AActor*> PlayersFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEngineerCharacter::StaticClass(), PlayersFound);

	AActor* ClosestPlayer = nullptr;
	float MinDistance = MAX_FLT;

	FVector EnemyLocation = ControlledPawn->GetActorLocation();

	for (AActor* Player : PlayersFound)
	{
		if (!Player) continue;

		float Distance = FVector::Dist(EnemyLocation, Player->GetActorLocation());
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestPlayer = Player;
		}
	}

	if (ClosestPlayer)
	{
		MoveToActor(ClosestPlayer, 60.f);
	}
}

