// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize() 
{
	bool Success = Super::Initialize();
	if (!Success)return false;

	// TODO: Setup
	if (ensure(Host == nullptr))return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}
void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();

		UE_LOG(LogTemp, Warning, TEXT("Host a server, please!"));
	}
	
}
