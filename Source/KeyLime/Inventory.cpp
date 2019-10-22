#include "Inventory.h"
#include "EffectApplierInterface.h"

void UInventory::initialize(UEffectApplierInterface* effectApplierInterface)
{
	m_effectApplierInterface = effectApplierInterface;
	onItemChangedDelegate.Broadcast(static_cast<int>(ItemEffectType::UNASSIGNED));
}

void UInventory::setItem(ItemEffectType newEffectType)
{
	if (newEffectType == m_effectType) return;
	
	m_effectType = newEffectType;
	onItemChangedDelegate.Broadcast(static_cast<int>(newEffectType));
	
}

bool UInventory::useItem()
{
	bool itemUsed = false;
	if (m_effectType != ItemEffectType::UNASSIGNED)
	{
		m_effectApplierInterface->applyEffect(m_effectType);
		itemUsed = true;
	}
	
	setItem(ItemEffectType::UNASSIGNED);
	return itemUsed;
}
