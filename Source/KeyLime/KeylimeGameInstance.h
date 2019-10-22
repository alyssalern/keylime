#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "KeylimeGameInstance.generated.h"

struct FPickupItemStruct;

UCLASS()
class KEYLIME_API UKeylimeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UKeylimeGameInstance() = default;
	virtual ~UKeylimeGameInstance() = default;

	FPickupItemStruct* getPickupItemDataTableRow(const FName& rowName) const;

	UPROPERTY(BlueprintReadWrite, Category = "Pickup Item Values")
	float teleportDistance{ 300.f };

	UPROPERTY(BlueprintReadWrite, Category = "Pickup Item Values")
	float teleportTimeInSecs{ 0.1f };

private:
	UPROPERTY(EditAnywhere) 
	UDataTable* pickupItemDataTable;
};
