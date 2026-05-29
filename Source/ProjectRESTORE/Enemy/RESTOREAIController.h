// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RESTOREAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRESTORE_API ARESTOREAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARESTOREAIController();

protected:
	virtual void BeginPlay() override;

	void ModeChaseMultiplayer();

	FTimerHandle TimerHandle_Chase;
};
