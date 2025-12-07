// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGCommonBlueprintLibraryBPLibrary.h"
#include "RPGCommonBlueprintLibrary.h"

#include "NiagaraComponent.h"
#include "Slate/SGameLayerManager.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "Factories/BlueprintFactory.h"
#include "PackageTools.h"
#include "FileHelpers.h"
#include "AssetViewUtils.h"
#include "Kismet2/KismetDebugUtilities.h"
#endif


bool URPGCommonBlueprintLibraryBPLibrary::IsInEditor()
{
	return GIsEditor;
}

#if WITH_EDITOR
void URPGCommonBlueprintLibraryBPLibrary::DeleteFolders(const TArray<FString>& PathsToDelete)
{
	AssetViewUtils::DeleteFolders(PathsToDelete);
}

UObject* URPGCommonBlueprintLibraryBPLibrary::LoadObjectByPathAndName(const FString& PackagePath,
	const FString& AssetName)
{
	FString FullPath;
	if (PackagePath.EndsWith(TEXT("/")))
	{
		FullPath = PackagePath + AssetName;
	}
	else
	{
		FullPath = PackagePath + "/" + AssetName;
	}
	
	UObject* TempObject = LoadObject<UObject>(nullptr, *FullPath, nullptr, LOAD_None, nullptr);

	if (!TempObject)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadObjectByPathAndName fail %s"), *FullPath);
	}
	return TempObject;
}

UClass* URPGCommonBlueprintLibraryBPLibrary::LoadClassByPathAndName(const FString& PackagePath,
	const FString& AssetName)
{
	FString FullPath;
    if (PackagePath.EndsWith(TEXT("/")))
    {
    	FullPath = PackagePath + AssetName;
    }
    else
    {
    	FullPath = PackagePath + "/" + AssetName;
    }

	FullPath = FullPath + "." + AssetName + "_C";
	
	UClass* TempClass = LoadClass<UObject>(nullptr,*FullPath);
	if (!TempClass)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadClassByPathAndName fail %s"), *FullPath);
	}
	return TempClass;
}

UObject* URPGCommonBlueprintLibraryBPLibrary::CreateNewClassPkg(const FString& PackagePath, const FString& AssetName,
	UClass* Class)
{
	FString FullPath;
	if (PackagePath.EndsWith(TEXT("/")))
	{
		FullPath = PackagePath + AssetName;
	}
	else
	{
		FullPath = PackagePath + "/" + AssetName;
	}
	
	FString FullAssetName = FullPath + "." + AssetName;
	
	UPackage* Pkg = nullptr;
	TSubclassOf<class UObject> FoundClass = nullptr;
	UObject* NewObj = LoadObject<UObject>(nullptr, *FullAssetName, nullptr, LOAD_None, nullptr);

	if (!NewObj)
	{
		UBlueprintFactory* BlueprintFactory = NewObject<UBlueprintFactory>();
		BlueprintFactory->ParentClass = Class;
		UClass* ClassToUse = BlueprintFactory->GetSupportedClass();

		Pkg = CreatePackage(*FullPath);
		EObjectFlags Flags = RF_Public | RF_Standalone;

		NewObj = BlueprintFactory->FactoryCreateNew(ClassToUse, Pkg, FName(*AssetName), Flags, nullptr, GWarn, NAME_None);
	}

	if (UBlueprint* ReferencedBlueprint = Cast<UBlueprint>(NewObj))
	{
		FoundClass = ReferencedBlueprint->GeneratedClass;
	}

	if (NewObj)
	{
		if (Pkg)
		{
			Pkg->SetIsExternallyReferenceable(true);
			FAssetRegistryModule::AssetCreated(NewObj);
			Pkg->MarkPackageDirty();
		}

		NewObj->GetOutermost()->MarkPackageDirty();//标星号
	}
	return FoundClass->GetDefaultObject();
}

UObject* URPGCommonBlueprintLibraryBPLibrary::CreateNewAssetPkg(const FString& PackagePath, const FString& AssetName,
	UClass* Class)
{
	FString FullPath;
	if (PackagePath.EndsWith(TEXT("/")))
	{
		FullPath = PackagePath + AssetName;
	}
	else
	{
		FullPath = PackagePath + "/" + AssetName;
	}
	
	FString FullAssetName = FullPath + "." + AssetName;

	UObject* TempObject = LoadObject<UObject>(nullptr, *FullAssetName, nullptr, LOAD_None, nullptr);
	if (!TempObject)
	{
		UPackage* MyPackage = CreatePackage(*FullPath);
		TempObject = NewObject<UObject>(MyPackage, Class, *AssetName, EObjectFlags::RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(TempObject);//告知资源浏览器
	}
	
	if (TempObject)
	{
		TempObject->GetOutermost()->MarkPackageDirty();//标星号
	}

	return TempObject;
}

void URPGCommonBlueprintLibraryBPLibrary::MarkPkgDirty(UObject* Asset)
{
	Asset->GetOutermost()->MarkPackageDirty();
}

void URPGCommonBlueprintLibraryBPLibrary::MarkDirtyAndSave(UObject* Asset)
{
	Asset->GetOutermost()->MarkPackageDirty();
	UEditorLoadingAndSavingUtils::SaveDirtyPackages(true,true);
}

void URPGCommonBlueprintLibraryBPLibrary::SaveAllPkg()
{
	UEditorLoadingAndSavingUtils::SaveDirtyPackages(true,true);
}

void URPGCommonBlueprintLibraryBPLibrary::ReloadPkg(UObject* Asset, const FString& AssetName)
{
	UPackage* Pkg = Asset->GetOutermost();
	TArray<UPackage*> PackagesToReload;
	PackagesToReload.Add(Pkg);
	UPackageTools::ReloadPackages(PackagesToReload);
}

#endif

void URPGCommonBlueprintLibraryBPLibrary::EmptyDataTable(UDataTable* const DataTable)
{
	DataTable->EmptyTable();
}

void URPGCommonBlueprintLibraryBPLibrary::ClearNiagaraOverrideParameters(UNiagaraComponent* Component)
{
	if (Component)
	{
		Component->SetUserParametersToDefaultValues();
	}
}

TArray<AActor*> URPGCommonBlueprintLibraryBPLibrary::SortByCustomData(TArray<AActor*> ActorsToSort, TArray<float> CustomData)
{
	ensure(ActorsToSort.Num() == CustomData.Num());
	
	if (ActorsToSort.Num() != CustomData.Num())
	{
		return ActorsToSort;
	}

	for (int32 i = 0; i < ActorsToSort.Num(); i++)
	{
		for (int32 j = i + 1; j < ActorsToSort.Num(); j++)
		{
			if (CustomData[i] > CustomData[j])
			{
				float TempData = CustomData[i];
				CustomData[i] = CustomData[j];
				CustomData[j] = TempData;

				AActor* TempActor = ActorsToSort[i];
				ActorsToSort[i] = ActorsToSort[j];
				ActorsToSort[j] = TempActor;
			}
		}
	}

	return ActorsToSort;
}

FVector URPGCommonBlueprintLibraryBPLibrary::FindLineAndPlaneIntersection(const FVector& PointInLine, const FVector& LineDirection,
	const FVector& PointInPlane, const FVector& PlaneNormal)
{
	float t = FVector::DotProduct(PlaneNormal, (PointInPlane - PointInLine)) / FVector::DotProduct(PlaneNormal, LineDirection);
	return PointInLine + t * LineDirection;
}
