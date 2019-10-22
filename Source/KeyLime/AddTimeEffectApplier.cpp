#include "AddTimeEffectApplier.h"
#include "KeylimeGameInstance.h"
#include "EffectWidgetCollection.h"
#include "LevelTimerWidgetInterface.h"
#include "Engine/World.h"

void UAddTimeEffectApplier::setEffectProperties()
{
	m_effectType = ItemEffectType::ADD_TIME;
	m_effectName = FString("AddTime");
}

void UAddTimeEffectApplier::applyEffect()
{
	m_effectWidgets->getLevelTimerWidgetInterface()->addTime(m_secondsToAdd);
}
