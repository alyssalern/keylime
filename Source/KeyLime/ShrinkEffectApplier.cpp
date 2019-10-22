#include "ShrinkEffectApplier.h"
#include "PlayerEffectApplierHelper.h"

void UShrinkEffectApplier::setEffectProperties()
{
	m_effectType = ItemEffectType::SHRINK;
	m_effectName = FString("Shrink");
}

void UShrinkEffectApplier::applyEffect()
{
	UTimedEffectApplier::applyEffect();
	PlayerEffectApplierHelper::getInstance()->applyEffectToPlayer(ItemEffectType::SHRINK);
}

void UShrinkEffectApplier::clearEffect()
{
	PlayerEffectApplierHelper::getInstance()->removeEffectFromPlayer(ItemEffectType::SHRINK);
	UTimedEffectApplier::clearEffect();
}