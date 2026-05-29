// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "EngineerCharacter.generated.h"

class UInputMappingContext;
class UInputDataConfig;
class UInputAction;

UCLASS()
class PROJECTRESTORE_API AEngineerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEngineerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// FP Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent *FirstPersonCameraComponent;

	// Enhanced Player Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext *InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputDataConfig *InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction *SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed = 600.f;

	UFUNCTION()
	void SprintStarted();

	UFUNCTION()
	void SprintStopped();

	UFUNCTION(Server, Reliable)
	void Server_SprintStarted();

	UFUNCTION(Server, Reliable)
	void Server_SprintStopped();

	UFUNCTION()
	void Move(const FInputActionValue &Value);

	UFUNCTION()
	void Look(const FInputActionValue &Value);

	void InteractPressed();

	UFUNCTION(Server, Reliable)
	void Server_TryPickupItem(class AItemBase *TargetItem);

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Inventory")
	class AItemBase *CurrentCarriedItem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void TogglePauseMenu();

private:
	UPROPERTY()
	class UUserWidget *PauseMenuInstance;
};
