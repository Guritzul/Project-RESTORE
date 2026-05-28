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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UInputAction* Look;
	
	//Interact

	//Flashlight
};
