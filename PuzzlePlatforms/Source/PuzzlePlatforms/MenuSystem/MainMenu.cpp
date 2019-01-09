// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include"Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize() 
{
	bool Success = Super::Initialize();
	if (!Success)return false;

	// Setup
	if (ensure(HostButton == nullptr))return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (ensure(JoinButton == nullptr))return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (ensure(CancelJoinMenuButton == nullptr))return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (ensure(ConfirmJoinMenu == nullptr))return false;
	ConfirmJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (ensure(Exit == nullptr))return false;
	Exit->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	return true;
}


void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();

		UE_LOG(LogTemp, Warning, TEXT("Host a server, please!"));
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		const FString &Address = IPAddressField->Text.ToString();
		if (ensure(IPAddressField == nullptr)) return;
		MenuInterface->Join(Address);
		UE_LOG(LogTemp, Warning, TEXT("Join a server, please!"));
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (ensure(MenuSwitcher == nullptr)) return;
	if (ensure(JoinMenu == nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (ensure(MenuSwitcher == nullptr)) return;
	if (ensure(MainMenu == nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::ExitGame()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (ensure(PlayerController == nullptr)) return;
	PlayerController->ConsoleCommand(FString(TEXT("quit")), true);
}

