// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "ThumbnailTest.generated.h"

/**
 * 
 */
UCLASS()
class TP_SIMPLEAI_API UThumbnailTest : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Editor|Thumbnail")
	static UTexture2D* GetThumbnailForAsset(UObject* Asset);


};
