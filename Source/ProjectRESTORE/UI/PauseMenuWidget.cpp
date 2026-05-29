#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h" 
#include "Blueprint/WidgetTree.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Player/EngineerCharacter.h"

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UCanvasPanel* RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
    WidgetTree->RootWidget = RootCanvas;

    UBackgroundBlur* ScreenBlur = WidgetTree->ConstructWidget<UBackgroundBlur>(UBackgroundBlur::StaticClass(), TEXT("ScreenBlur"));
    ScreenBlur->SetBlurStrength(15.f);
    RootCanvas->AddChild(ScreenBlur);

    UCanvasPanelSlot* BlurSlot = Cast<UCanvasPanelSlot>(ScreenBlur->Slot);
    if (BlurSlot)
    {
        BlurSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
        BlurSlot->SetOffsets(FMargin(0.f));
    }

    UImage* DarkOverlay = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("DarkOverlay"));
    DarkOverlay->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.6f));
    RootCanvas->AddChild(DarkOverlay);

    UCanvasPanelSlot* OverlaySlot = Cast<UCanvasPanelSlot>(DarkOverlay->Slot);
    if (OverlaySlot)
    {
        OverlaySlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
        OverlaySlot->SetOffsets(FMargin(0.f));
    }

    UVerticalBox* MenuBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("MenuBox"));
    RootCanvas->AddChild(MenuBox);

    UCanvasPanelSlot* BoxSlot = Cast<UCanvasPanelSlot>(MenuBox->Slot);
    if (BoxSlot)
    {
        BoxSlot->SetAnchors(FAnchors(0.5f, 0.5f));
        BoxSlot->SetAlignment(FVector2D(0.5f, 0.5f));
        BoxSlot->SetPosition(FVector2D(0.f, 0.f));
        BoxSlot->SetSize(FVector2D(450.f, 350.f));
    }

    UTextBlock* TitleText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TitleText"));
    TitleText->SetText(FText::FromString("CRITICAL ERROR: PAUSED"));
    TitleText->SetColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.0f, 0.0f, 1.0f)));
    TitleText->SetShadowColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.9f));
    TitleText->SetShadowOffset(FVector2D(3.f, 3.f));

    FSlateFontInfo TitleFont = TitleText->GetFont();
    TitleFont.Size = 32;
    TitleText->SetFont(TitleFont);
    TitleText->SetJustification(ETextJustify::Center);

    MenuBox->AddChild(TitleText);
    UVerticalBoxSlot* TitleSlot = Cast<UVerticalBoxSlot>(TitleText->Slot);
    if (TitleSlot)
    {
        TitleSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 40.f));
    }

    ResumeButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("ResumeButton"));
    ResumeButton->SetBackgroundColor(FLinearColor(0.02f, 0.02f, 0.02f, 0.8f));
    MenuBox->AddChild(ResumeButton);
    ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::HandleResumeClicked);

    UVerticalBoxSlot* ResumeSlot = Cast<UVerticalBoxSlot>(ResumeButton->Slot);
    if (ResumeSlot)
    {
        ResumeSlot->SetPadding(FMargin(0.f, 10.f));
    }

    UTextBlock* ResumeText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("ResumeText"));
    ResumeText->SetText(FText::FromString("RESUME SIMULATION"));
    ResumeText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f)));
    ResumeText->SetJustification(ETextJustify::Center);
    ResumeButton->AddChild(ResumeText);

    QuitButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("QuitButton"));
    QuitButton->SetBackgroundColor(FLinearColor(0.02f, 0.02f, 0.02f, 0.8f));
    MenuBox->AddChild(QuitButton);
    QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::HandleQuitClicked);

    UVerticalBoxSlot* QuitSlot = Cast<UVerticalBoxSlot>(QuitButton->Slot);
    if (QuitSlot)
    {
        QuitSlot->SetPadding(FMargin(0.f, 10.f));
    }

    UTextBlock* QuitText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("QuitText"));
    QuitText->SetText(FText::FromString("ABORT MISSION (QUIT)"));
    QuitText->SetColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f, 1.0f)));
    QuitText->SetJustification(ETextJustify::Center);
    QuitButton->AddChild(QuitText);
}

void UPauseMenuWidget::HandleResumeClicked()
{
    AEngineerCharacter* Engineer = Cast<AEngineerCharacter>(GetOwningPlayerPawn());
    if (Engineer)
    {
        Engineer->TogglePauseMenu();
    }
}

void UPauseMenuWidget::HandleQuitClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}