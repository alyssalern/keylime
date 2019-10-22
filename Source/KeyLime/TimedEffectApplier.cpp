#include "TimedEffectApplier.h"
#include "KeylimeGameInstance.h"
#include "TimerManager.h"
#include "EffectWidgetCollection.h"
#include "CurrentEffectWidgetInterface.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

UTimedEffectApplier::~UTimedEffectApplier()
{
	
}

void UTimedEffectApplier::applyEffect()
{
	if (isActive())
	{
		clearEffect();
	}
	
	UE_LOG(LogTemp, Log, TEXT("MIKO6:UTimedEffectApplier - Applying effect : %s"), *m_effectName);

	auto world = GetWorld();
	if (world == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MIKO6:UTimedEffectApplier:applyEffect - Cannot find world."))
		return;
	}
	m_timerManager = &(world->GetTimerManager());
	setTimer();
	UE_LOG(LogTemp, Log, TEXT("MIKO6: Timer Rate: %.2f"), m_timerManager->GetTimerRate(m_effectTimerHandle));

	m_effectWidgets->getCurrentEffectWidgetInterface()->effectApplied(m_effectType);
}

void UTimedEffectApplier::setTimer()
{
	m_timerManager->SetTimer(m_effectTimerHandle, this, &UTimedEffectApplier::onEffectExpired, m_effectDuration, false);
}

void UTimedEffectApplier::clearEffect()
{
	if (isActive())
	{
		auto world = GetWorld();
		if (world == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("MIKO6:UTimedEffectApplier:clearEffect - Cannot find world."))
			return;
		}
		auto& timerManager = world->GetTimerManager();
		timerManager.ClearTimer(m_effectTimerHandle);
	}
}

bool UTimedEffectApplier::isActive() const
{
	auto world = GetWorld();
	if (world == nullptr) return false;
	auto& timerManager = world->GetTimerManager();
	bool bActive = timerManager.IsTimerActive(m_effectTimerHandle);
	UE_LOG(LogTemp, Log, TEXT("MIKO6:UTimedEffectApplier - Effect %s active: %s"), *m_effectName, (bActive ? *FString("yes") : *FString("no")));
	return bActive;
}

void UTimedEffectApplier::onEffectExpired()
{
	clearEffect();
	m_effectWidgets->getCurrentEffectWidgetInterface()->effectTimedOut(m_effectType);
}