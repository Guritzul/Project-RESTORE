// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRESTORE_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Walk
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Move;

	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Look;
	
	// Jump
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Jump;

	// Sprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Sprint;

	//Interact
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* Interact;

	//Flashlight
};
