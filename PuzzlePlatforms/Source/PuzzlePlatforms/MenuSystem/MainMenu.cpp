// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include"Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr))return;

	ServerRowClass = ServerRowBPClass.Class;

}


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
		/*const FString &Address = IPAddressField->Text.ToString();
		if (ensure(IPAddressField == nullptr)) return;
		MenuInterface->Join(Address);*/
		UWorld* World = this->GetWorld();
		if (ensure(World == nullptr))return;
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;
		ServerList->AddChild(Row);

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

