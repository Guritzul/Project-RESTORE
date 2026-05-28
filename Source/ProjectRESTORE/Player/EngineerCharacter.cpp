// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerCharacter.h"
#include "../Components/InputDataConfig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AEngineerCharacter::AEngineerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	FirstPersonCameraComponent->SetupAttachment(GetMesh());

	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 20.f, 160.f));

	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AEngineerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEngineerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEngineerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			if (InputMapping)
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input && InputActions)
	{
		if (InputActions->Move)
		{
			Input->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &AEngineerCharacter::Move);
		}
		if (InputActions->Look)
		{
			Input->BindAction(InputActions->Look, ETriggerEvent::Triggered, this, &AEngineerCharacter::Look);
		}
		if (InputActions->Jump)
		{
			Input->BindAction(InputActions->Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
			Input->BindAction(InputActions->Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
	}

}

void AEngineerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEngineerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

