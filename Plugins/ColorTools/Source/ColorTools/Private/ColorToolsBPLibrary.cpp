// Copyright Epic Games, Inc. All Rights Reserved.

#include "ColorToolsBPLibrary.h"
#include "ColorTools.h"

UColorToolsBPLibrary::UColorToolsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FColor UColorToolsBPLibrary::ProcessTexture(UTexture2D* InTexture, int32 PixelX, int32 PixelY)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, FString::FromInt(PixelX));


	FTexture2DMipMap* MyMipMap = &InTexture->PlatformData->Mips[0];
	FByteBulkData* RawImageData = &MyMipMap->BulkData;
	FColor* FormatedImageData = static_cast<FColor*>(InTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));
	
	uint32 TextureWidth = MyMipMap->SizeX, TextureHeight = MyMipMap->SizeY;
	FColor PixelColor;

	if (PixelX >= 0 && (uint32)PixelX < TextureWidth && PixelY >= 0 && (uint32)PixelY < TextureHeight)
	{
		PixelColor = FormatedImageData[PixelY * TextureWidth + PixelX];
	}
	
	
	RawImageData->Unlock();

	return PixelColor;
}

