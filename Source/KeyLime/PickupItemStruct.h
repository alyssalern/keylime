#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "PickupItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FPickupItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int typeIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString meshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString iconLocation;
};
