#include "UserInterface/Interaction/LootWindowWidget.h"

//==========================================================================
// INCLUDES
//==========================================================================
#include "AlphaCharacter.h"
#include "UserInterface/Interaction/LootRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "TimerManager.h"

//==========================================================================
// WIDGET LIFECYCLE
//==========================================================================
void ULootWindowWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetVisibility(ESlateVisibility::Collapsed);

    // Auto-bind to player character on construction
    if (const APlayerController* PlayerController = GetOwningPlayer();
        PlayerController && PlayerController->GetPawn())
    {
        if (AAlphaCharacter* Character = Cast<AAlphaCharacter>(PlayerController->GetPawn()))
        {
            BindToCharacter(Character);
        }
    }
}

void ULootWindowWidget::NativeDestruct()
{
    UnbindFromCharacter();
    Super::NativeDestruct();
}

//==========================================================================
// CHARACTER BINDING SYSTEM
//==========================================================================
void ULootWindowWidget::BindToCharacter(AAlphaCharacter* Character)
{
    if (Character && !BoundCharacter)
    {
        BoundCharacter = Character;
        Character->OnLootPickedUp.AddDynamic(this, &ULootWindowWidget::OnLootPickedUp);
        UE_LOG(LogTemp, Log, TEXT("LootWindowWidget bound to character"));
    }
}

void ULootWindowWidget::UnbindFromCharacter()
{
    if (BoundCharacter)
    {
        BoundCharacter->OnLootPickedUp.RemoveDynamic(this, &ULootWindowWidget::OnLootPickedUp);
        BoundCharacter = nullptr;
        UE_LOG(LogTemp, Log, TEXT("LootWindowWidget unbound from character"));
    }
}

//==========================================================================
// LOOT EVENT HANDLING
//==========================================================================
void ULootWindowWidget::OnLootPickedUp(const FInteractableData& LootData)
{
    PushLoot(LootData);
}

void ULootWindowWidget::PushLoot(const FInteractableData& Data)
{
    // Validate required components
    if (!LootListBox || !RowClass) 
    { 
        UE_LOG(LogTemp, Warning, TEXT("LootWindow: LootListBox/RowClass null")); 
        return; 
    }

    // Create new loot row widget
    APlayerController* PC = GetOwningPlayer();
    ULootRowWidget* Row = PC
        ? CreateWidget<ULootRowWidget>(PC, RowClass)
        : CreateWidget<ULootRowWidget>(GetWorld(), RowClass); // fallback

    if (!Row) 
    { 
        UE_LOG(LogTemp, Warning, TEXT("LootWindow: Create row failed (RowClass=%s)"), *GetNameSafe(*RowClass)); 
        return; 
    }

    // Configure and add row to display
    Row->Setup(Data);
    LootListBox->InsertChildAt(0, Row); // Add new entry at the TOP

    // Maintain maximum visible entries
    while (LootListBox->GetChildrenCount() > MaxVisibleEntries)
    {
        if (UWidget* Last = LootListBox->GetChildAt(LootListBox->GetChildrenCount() - 1))
        {
            LootListBox->RemoveChild(Last);
        }
    }

    // Show widget if hidden
    if (GetVisibility() != ESlateVisibility::Visible) 
        SetVisibility(ESlateVisibility::Visible);

    // Schedule automatic removal
    ScheduleRemoval(Row);
}

//==========================================================================
// ROW MANAGEMENT SYSTEM
//==========================================================================
void ULootWindowWidget::ScheduleRemoval(ULootRowWidget* Row)
{
    if (!Row) return;

    FTimerHandle Handle;
    FTimerDelegate Delegate;

    // Use weak pointer to avoid keeping object alive
    TWeakObjectPtr<ULootRowWidget> WeakRow = Row;

    Delegate.BindLambda([this, WeakRow]()
    {
        if (!LootListBox) return;

        // Remove the row if it's still valid
        if (WeakRow.IsValid())
        {
            LootListBox->RemoveChild(WeakRow.Get());
        }

        // Hide entire widget when no entries remain
        if (LootListBox->GetChildrenCount() == 0)
        {
            SetVisibility(ESlateVisibility::Collapsed);
        }
    });

    // Set timer for automatic removal
    GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, EntryLifetime, false);
    RowTimers.Add(WeakRow, Handle);
}