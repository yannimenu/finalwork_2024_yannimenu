// Amasson


#include "UI/ControllableUserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "UI/WidgetControllerComponent.h"
#include "UI/WidgetController.h"


UWidgetControllerComponent* UControllableUserWidget::GetComponentFromControllerByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const
{
    if (!WidgetController) return nullptr;

    return WidgetController->GetComponentByClass(ComponentClass);
}

void UControllableUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (IsValid(WidgetController))
    {
        SetWidgetController(WidgetController);
        WidgetController->BroadcastValues();
    }
}

void UControllableUserWidget::SetWidgetController(UWidgetController* NewWidgetController)
{
    WidgetController = NewWidgetController;
    WidgetControllerSet(WidgetController);

    if (IsValid(WidgetController))
    {
        if (bUseStateBehavior)
        {
            WidgetController->OnControllerStateUpdate.AddDynamic(this, &ThisClass::OnWidgetControllerUpdateState);
        }
    }

    PropagateWidgetController(this);
}

bool UControllableUserWidget::AcceptWidgetController(UWidgetController* InWidgetController) const
{
    // We accept invalid objects as widget controllers
    if (!InWidgetController || !InWidgetController->GetClass())
        return true;

    // If we have no required class, we accept any of them
    if (AcceptedControllerClasses.IsEmpty())
        return true;

    if (AcceptedControllerClasses.Contains(InWidgetController->GetClass()))
        return true;

    for (TSubclassOf<UWidgetController> AcceptedControllerClass : AcceptedControllerClasses)
    {
        if (InWidgetController->GetClass()->IsChildOf(AcceptedControllerClass))
            return true;
    }

    return false;
}

void UControllableUserWidget::OnWidgetControllerUpdateState(FName State)
{
    SetVisibility(
        StateBehavior.VisibleStates.Contains(State) ?
        StateBehavior.Visible :
        StateBehavior.Invisible
    );

    SetIsEnabled(!StateBehavior.DisabledStates.Contains(State));
};

void UControllableUserWidget::PropagateWidgetController(UWidget* Parent)
{
    TArray<UWidget*> AllWidgets;
    WidgetTree->GetAllWidgets(AllWidgets);
    for (UWidget* Widget : AllWidgets)
    {
        if (!IsValid(Widget)) continue;

        if (UControllableUserWidget* ControlledWidget = Cast<UControllableUserWidget>(Widget))
        {
            if (ControlledWidget->TakeControllerFromParent && ControlledWidget->AcceptWidgetController(WidgetController))
            {
                ControlledWidget->SetWidgetController(WidgetController);
            }
        }
    }

    // TArray<UWidget*> ChildWidgets;
    // UWidgetTree::GetChildWidgets(Parent, ChildWidgets);

    // for (UWidget* ChildWidget : ChildWidgets)
    // {
    //     if (UControllableUserWidget* ControlledWidget = Cast<UControllableUserWidget>(ChildWidget))
    //     {
    //         if (ControlledWidget->TakeControllerFromParent)
    //         {
    //             ControlledWidget->SetWidgetController(WidgetController);
    //             PropagateWidgetController(ChildWidget);
    //         }
    //     }
    //     else
    //     {
    //         PropagateWidgetController(ChildWidget);
    //     }
    // }
}
