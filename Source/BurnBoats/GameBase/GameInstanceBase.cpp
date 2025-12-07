// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceBase.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UGameInstanceBase::UGameInstanceBase()
{
	PlayerName = TEXT("Player");
}

void UGameInstanceBase::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();

		// 绑定委托
		CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UGameInstanceBase::OnCreateSessionComplete);
		FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UGameInstanceBase::OnFindSessionsComplete);
		JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UGameInstanceBase::OnJoinSessionComplete);
		DestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UGameInstanceBase::OnDestroySessionComplete);
	}
}

void UGameInstanceBase::CreateSession(FName SessionName, FString GameMode)
{
	if (SessionInterface.IsValid())
	{
		SessionSettings = MakeShareable(new FOnlineSessionSettings());
		SessionSettings->bIsLANMatch = true; // 局域网
		SessionSettings->NumPublicConnections = 4; // 最大玩家数
		SessionSettings->bShouldAdvertise = true;
		SessionSettings->bAllowJoinInProgress = true;
		SessionSettings->bAllowJoinViaPresence = true;
		SessionSettings->bUsesPresence = true;
		SessionSettings->Set(FName("GAMEMODE"), GameMode, EOnlineDataAdvertisementType::ViaOnlineService);

		// 创建会话
		CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
		SessionInterface->CreateSession(0, SessionName, *SessionSettings);
	}
}

void UGameInstanceBase::FindSessions()
{
	if (SessionInterface.IsValid())
	{
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

		FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UGameInstanceBase::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (SessionInterface.IsValid())
	{
		JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
		SessionInterface->JoinSession(0, NAME_GameSession, SessionResult);
	}
}

void UGameInstanceBase::DestroySession()
{
	if (SessionInterface.IsValid())
	{
		DestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);
		SessionInterface->DestroySession(NAME_GameSession);
	}
}

void UGameInstanceBase::StartGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// 切换到游戏地图
		FString MapPath = TEXT("/Game/Maps/GameplayMap");
		World->ServerTravel(MapPath + "?listen");
	}
}

FString UGameInstanceBase::GetCurrentSessionIP() const
{
	FString ConnectInfo;
	if (SessionInterface.IsValid() && SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectInfo))
	{
		return ConnectInfo;
	}
	return TEXT("");
}

void UGameInstanceBase::JoinByIP(const FString& IPAddress)
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		FString TravelURL = FString::Printf(TEXT("%s:7777"), *IPAddress);
		PlayerController->ClientTravel(TravelURL, TRAVEL_Absolute);
	}
}

void UGameInstanceBase::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session created successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session"));
	}
}

void UGameInstanceBase::OnFindSessionsComplete(bool bWasSuccessful)
{
	SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
	if (bWasSuccessful && SessionSearch.IsValid())
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		// 在这里可以处理搜索到的会话，例如更新UI
		UE_LOG(LogTemp, Log, TEXT("Found %d sessions"), SearchResults.Num());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find sessions"));
	}
}

void UGameInstanceBase::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			FString TravelURL;
			if (SessionInterface->GetResolvedConnectString(SessionName, TravelURL))
			{
				PlayerController->ClientTravel(TravelURL, TRAVEL_Absolute);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to join session"));
	}
}

void UGameInstanceBase::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session destroyed successfully"));
	}
}