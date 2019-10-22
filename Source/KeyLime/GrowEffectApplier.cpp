#include "GrowEffectApplier.h"
#include "PlayerEffectApplierHelper.h"

void UGrowEffectApplier::setEffectProperties()
{
	m_effectType = ItemEffectType::GROW;
	m_effectName = FString("Grow");
}

void UGrowEffectApplier::applyEffect()
{
	UTimedEffectApplier::applyEffect();
	PlayerEffectApplierHelper::getInstance()->applyEffectToPlayer(ItemEffectType::GROW);
}

void UGrowEffectApplier::clearEffect()
{
	PlayerEffectApplierHelper::getInstance()->removeEffectFromPlayer(ItemEffectType::GROW);
	UTimedEffectApplier::clearEffect();
}