#include "EffectApplierInterface.h"
#include "SlowdownEffectApplier.h"
#include "SpeedupEffectApplier.h"
#include "ShrinkEffectApplier.h"
#include "GrowEffectApplier.h"
#include "TeleportEffectApplier.h"
#include "AddTimeEffectApplier.h"
#include "PlayerPawn.h"
#include "CurrentEffectWidgetInterface.h"
#include "LevelTimerWidgetInterface.h"
#include "CurrentEffectWidgetInterface.h"

const std::set<std::set<ItemEffectType>> UEffectApplierInterface::CONFLICTING_EFFECT_TYPES = {
	{ ItemEffectType::SLOWDOWN, ItemEffectType::SPEEDUP },
	{ ItemEffectType::SHRINK, ItemEffectType::GROW }
};

void UEffectApplierInterface::initialize()
{
	m_levelTimerWidgetInterface = NewObject<ULevelTimerWidgetInterface>(this);
	m_currentEffectWidgetInterface = NewObject<UCurrentEffectWidgetInterface>(this);
	m_currentEffectWidgetInterface->initialize();
	createEffectAppliers();
}

void UEffectApplierInterface::applyEffect(ItemEffectType effectType)
{
	std::lock_guard<std::recursive_mutex> lock(m_effectApplierLock);
	if (m_effectAppliers.count(effectType) == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MIKO6:UEffectApplierInterface - Unrecognized item effect type"));
		return;
	}
	clearConflictingEffects(effectType);
	m_effectAppliers[effectType]->applyEffect();
}

UCurrentEffectWidgetInterface* UEffectApplierInterface::getCurrentEffectWidgetInterface() const
{
	return m_currentEffectWidgetInterface;
}

ULevelTimerWidgetInterface* UEffectApplierInterface::getLevelTimerWidgetInterface() const
{
	return m_levelTimerWidgetInterface;
}

void UEffectApplierInterface::createEffectAppliers()
{
	std::lock_guard<std::recursive_mutex> lock(m_effectApplierLock);

	m_slowdownApplier = NewObject<USlowdownEffectApplier>(this);
	m_speedupApplier = NewObject<USpeedupEffectApplier>(this);
	m_shrinkApplier = NewObject<UShrinkEffectApplier>(this);
	m_growApplier = NewObject<UGrowEffectApplier>(this);
	m_teleportApplier = NewObject<UTeleportEffectApplier>(this);
	m_addTimeApplier = NewObject<UAddTimeEffectApplier>(this);

	m_effectAppliers[ItemEffectType::SLOWDOWN] = m_slowdownApplier;
	m_effectAppliers[ItemEffectType::SPEEDUP] = m_speedupApplier;
	m_effectAppliers[ItemEffectType::SHRINK] = m_shrinkApplier;
	m_effectAppliers[ItemEffectType::GROW] = m_growApplier;
	m_effectAppliers[ItemEffectType::TELEPORT] = m_teleportApplier;
	m_effectAppliers[ItemEffectType::ADD_TIME] = m_addTimeApplier;

	auto effectWidgetCollection = Cast<IEffectWidgetCollection>(this);
	for (auto& effectApplier : m_effectAppliers)
	{
		effectApplier.second->initialize(effectWidgetCollection);
	}
}

void UEffectApplierInterface::clearConflictingEffects(ItemEffectType effectType)
{
	for (auto& conflictingEffectGroup : CONFLICTING_EFFECT_TYPES)
	{
		if (conflictingEffectGroup.count(effectType) == 1)
		{
			for (const auto& conflictingEffectType : conflictingEffectGroup)
			{
				auto timedEffectApplier = dynamic_cast<UTimedEffectApplier*>(m_effectAppliers[conflictingEffectType]);
				if (timedEffectApplier == nullptr)
				{
					UE_LOG(LogTemp, Error, TEXT("UEffectApplierInterface::clearConflictingEffects - UEffectApplier could not be cast to UTimedEffectApplier"))
					break;
				}
				if (timedEffectApplier->isActive() && conflictingEffectType != effectType)
				{
					timedEffectApplier->clearEffect();
				}
			}
		}
	}
}

void UEffectApplierInterface::clearAllEffects()
{
	std::lock_guard<std::recursive_mutex> lock(m_effectApplierLock);
	for (auto& effectApplier : m_effectAppliers)
	{
		auto timedEffectApplier = Cast<UTimedEffectApplier>(effectApplier.second);
		if (timedEffectApplier == nullptr) continue;

		if (timedEffectApplier->isActive())
		{
			timedEffectApplier->clearEffect();
		}
	}
}
