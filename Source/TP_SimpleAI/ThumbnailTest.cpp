// Fill out your copyright notice in the Description page of Project Settings.


#include "ThumbnailTest.h"
#include "Editor/UnrealEdEngine.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"

UTexture2D* UThumbnailTest::GetThumbnailForAsset(UObject* Asset)
{
    if (!Asset)
    {
        return nullptr;
    }

    FThumbnailRenderingInfo* RenderInfo = GUnrealEd->GetThumbnailManager()->GetRenderingInfo(Asset);
    if (!RenderInfo || !RenderInfo->Renderer)
    {
        return nullptr;
    }

    FIntRect ViewportRect(0, 0, 256, 256);
    FRenderTarget* RenderTarget = RenderInfo->Renderer->CreateRenderTargetForThumbnail(Asset, ViewportRect);
    if (!RenderTarget)
    {
        return nullptr;
    }

    // Now read the pixels from the render target
    TArray<FColor> Bitmap;
    RenderTarget->ReadPixels(Bitmap);

    // Create the texture
    UTexture2D* ThumbnailTexture = UTexture2D::CreateTransient(256, 256);
    if (!ThumbnailTexture)
    {
        return nullptr;
    }

    // Copy the pixels
    void* TextureData = ThumbnailTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, Bitmap.GetData(), Bitmap.Num() * sizeof(FColor));
    ThumbnailTexture->PlatformData->Mips[0].BulkData.Unlock();

    // Update the texture
    ThumbnailTexture->UpdateResource();

    return ThumbnailTexture;
}