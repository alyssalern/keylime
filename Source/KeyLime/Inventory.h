#pragma once

#include "CoreMinimal.h"
#include "ItemEffectTypes.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

class UEffectApplierInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemChangedDelegate, int, effectType);

UCLASS(Blueprintable)
class KEYLIME_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UInventory() = default;
	void initialize(UEffectApplierInterface* effectApplierInterface);
	void setItem(ItemEffectType effectType);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool useItem();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FItemChangedDelegate onItemChangedDelegate;

private:
	ItemEffectType m_effectType{ ItemEffectType::UNASSIGNED };
	UEffectApplierInterface* m_effectApplierInterface{ nullptr };
};
