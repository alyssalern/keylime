#include "SpeedupEffectApplier.h"
#include "PlayerEffectApplierHelper.h"

void USpeedupEffectApplier::setEffectProperties()
{
	m_effectType = ItemEffectType::SPEEDUP;
	m_effectName = FString("Speedup");
}

void USpeedupEffectApplier::applyEffect()
{
	UTimedEffectApplier::applyEffect();
	PlayerEffectApplierHelper::getInstance()->applyEffectToPlayer(ItemEffectType::SPEEDUP);
}

void USpeedupEffectApplier::clearEffect()
{
	PlayerEffectApplierHelper::getInstance()->removeEffectFromPlayer(ItemEffectType::SPEEDUP);
	UTimedEffectApplier::clearEffect();
}
