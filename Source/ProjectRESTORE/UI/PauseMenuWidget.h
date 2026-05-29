// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRESTORE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

    UPROPERTY()
    UButton* ResumeButton;

    UPROPERTY()
    UButton* QuitButton;

private:
    UFUNCTION()
    void HandleResumeClicked();

    UFUNCTION()
    void HandleQuitClicked();
};