// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGCommonBlueprintLibraryBPLibrary.generated.h"

class UNiagaraComponent;

UCLASS()
class URPGCommonBlueprintLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Editor")
	static bool IsInEditor();

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static void DeleteFolders(const TArray<FString>& PathsToDelete);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static UObject* LoadObjectByPathAndName(const FString& PackagePath, const FString& AssetName);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static UClass* LoadClassByPathAndName(const FString& PackagePath, const FString& AssetName);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static UObject* CreateNewClassPkg(const FString& PackagePath, const FString& AssetName, UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static UObject* CreateNewAssetPkg(const FString& PackagePath, const FString& AssetName, UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static void MarkPkgDirty(UObject* Asset);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static void MarkDirtyAndSave(UObject* Asset);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static void SaveAllPkg();

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting")
	static void ReloadPkg(UObject* Asset, const FString& AssetName);
	
#endif

	UFUNCTION(BlueprintCallable, Category = "DataTable")
	static void EmptyDataTable(UDataTable* const DataTable);

	UFUNCTION(BlueprintCallable, Category = "Niagara")
	static void ClearNiagaraOverrideParameters(UNiagaraComponent* Component);

	UFUNCTION(BlueprintCallable, Category = Sort)
	static TArray<AActor*> SortByCustomData(TArray<AActor*> ActorsToSort, TArray<float> CustomData);

	//求一条线和一个平面的交点
	UFUNCTION(BlueprintCallable, Category = Math)
	static FVector FindLineAndPlaneIntersection(const FVector& PointInLine, const FVector& LineDirection, const FVector& PointInPlane, const FVector& PlaneNormal);
};
