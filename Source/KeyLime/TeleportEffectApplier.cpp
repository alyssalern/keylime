#include "TeleportEffectApplier.h"
#include "PlayerEffectApplierHelper.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/World.h"
#include "KeylimeGameInstance.h"

void UTeleportEffectApplier::setEffectProperties()
{
	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UTeleportEffectApplier:setEffectProperties: Failed to get world"))
		return;
	}
	auto gameInstance = Cast<UKeylimeGameInstance>(GetWorld()->GetGameInstance());
	m_effectDuration = 1.f / 50.f;
	m_effectType = ItemEffectType::TELEPORT;
	m_effectName = FString("Teleport");
}

void UTeleportEffectApplier::applyEffect()
{
	UTimedEffectApplier::applyEffect();
	PlayerEffectApplierHelper::getInstance()->applyEffectToPlayer(ItemEffectType::TELEPORT);
}

void UTeleportEffectApplier::setTimer()
{
	m_timerManager->SetTimer(m_effectTimerHandle, this, &UTeleportEffectApplier::checkIfDestinationReached, m_effectDuration, true);
}

void UTeleportEffectApplier::checkIfDestinationReached()
{
	if (PlayerEffectApplierHelper::getInstance()->teleportCompleted())
	{
		onEffectExpired();
	}
}

void UTeleportEffectApplier::clearEffect()
{
	UTimedEffectApplier::clearEffect();
	PlayerEffectApplierHelper::getInstance()->removeEffectFromPlayer(ItemEffectType::TELEPORT);
}