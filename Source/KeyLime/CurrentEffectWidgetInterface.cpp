#include "CurrentEffectWidgetInterface.h"

void UCurrentEffectWidgetInterface::initialize()
{
	m_currentEffects.clear();
	broadcastCurrentEffects();
}

void UCurrentEffectWidgetInterface::effectApplied(ItemEffectType effectType)
{
	if (m_currentEffects.count(effectType) == 1) return;

	m_currentEffects.insert(static_cast<int>(effectType));
	broadcastCurrentEffects();
}

void UCurrentEffectWidgetInterface::effectTimedOut(ItemEffectType effectType)
{
	if (!m_currentEffects.count(effectType) == 1) return;

	m_currentEffects.erase(effectType);
	broadcastCurrentEffects();
}

void UCurrentEffectWidgetInterface::broadcastCurrentEffects() const
{
	int effectsToBroadcast[4] = { 0, 0, 0, 0 };

	uint16_t i = 0;
	for (const auto& currentEffect : m_currentEffects)
	{
		if (i <= m_currentEffects.size()) effectsToBroadcast[i] = currentEffect;
		else break;
		++i;
	}

	onCurrentEffectsChangedDelegate.Broadcast(effectsToBroadcast[0], effectsToBroadcast[1], effectsToBroadcast[2], effectsToBroadcast[3]);
}
