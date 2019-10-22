#include "KeylimeGameInstance.h"

#include "PickupItemStruct.h"

FPickupItemStruct* UKeylimeGameInstance::getPickupItemDataTableRow(const FName& rowName) const
{
	return pickupItemDataTable->FindRow<FPickupItemStruct>(rowName, TEXT(""));
}