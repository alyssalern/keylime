#include "SlowdownEffectApplier.h"
#include "PlayerEffectApplierHelper.h"

void USlowdownEffectApplier::setEffectProperties()
{
	m_effectType = ItemEffectType::SLOWDOWN;
	m_effectName = FString("Slowdown");
}

void USlowdownEffectApplier::applyEffect()
{
	UTimedEffectApplier::applyEffect();
	PlayerEffectApplierHelper::getInstance()->applyEffectToPlayer(ItemEffectType::SLOWDOWN);
}

void USlowdownEffectApplier::clearEffect()
{
	PlayerEffectApplierHelper::getInstance()->removeEffectFromPlayer(ItemEffectType::SLOWDOWN);
	UTimedEffectApplier::clearEffect();
}