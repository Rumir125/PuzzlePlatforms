// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FString> ServerName);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;
private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinMenu;
	UPROPERTY(meta = (BindWidget))
	class UButton* Exit;
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;


	UFUNCTION()
	void HostServer();
	UFUNCTION()
	void JoinServer();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void ExitGame();

	TOptional<uint32> SelectedIndex;

};
