#include "InventoryItemEffectComponent.h"
#include "KeylimeGameModeBase.h"
#include "Inventory.h"

void UInventoryItemEffectComponent::initialize(ItemEffectType effectType, char icon)
{
	UItemEffectComponent::initialize(effectType, icon);

	auto gameMode = getKeylimeGameMode();
	if (gameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MIKO6:UInventoryItemEffectComponent - Failed to find game mode"));
		return;
	}

	m_inventory = gameMode->getInventory();
	if (m_inventory == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryItemEffectComponent::initialize - Failed to find inventory"));
		return;
	}
}

void UInventoryItemEffectComponent::onPlayerHit()
{
	if (m_inventory == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryItemEffectComponent::onPlayerHit - Inventory missing"));
		return;
	}
	m_inventory->setItem(m_effectType);
}
