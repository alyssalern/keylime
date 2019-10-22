#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DataTableAccessor.generated.h"

UCLASS()
class KEYLIME_API ADataTableAccessor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADataTableAccessor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDataTable* pickupItemDataTable;
};
