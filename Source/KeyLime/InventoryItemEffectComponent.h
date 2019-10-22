#pragma once

#include <memory>
#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include "ItemEffectComponent.h"
#include "InventoryItemEffectComponent.generated.h"

class UInventory;

UCLASS()
class KEYLIME_API UInventoryItemEffectComponent : public UItemEffectComponent
{
	GENERATED_BODY()

public:
	UInventoryItemEffectComponent() = default;
	virtual ~UInventoryItemEffectComponent() = default;
	virtual void initialize(ItemEffectType effectType, char icon);
	
	void onPlayerHit() override;

protected:
	UInventory* m_inventory{ nullptr };
};
