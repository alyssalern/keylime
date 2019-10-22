#include "PlayerEffectApplierHelper.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

UWorld* PlayerEffectApplierHelper::m_world = nullptr;
std::shared_ptr<PlayerEffectApplierHelper> PlayerEffectApplierHelper::m_instance = nullptr;

void PlayerEffectApplierHelper::setWorld(UWorld* world)
{
	m_world = world;
}

std::shared_ptr<PlayerEffectApplierHelper> PlayerEffectApplierHelper::getInstance()
{
	if (m_instance = nullptr)
	{
		m_instance = std::shared_ptr<PlayerEffectApplierHelper>(new PlayerEffectApplierHelper());
	}
	return m_instance;
}

void PlayerEffectApplierHelper::applyEffectToPlayer(const ItemEffectType& effect)
{
	if (auto playerPawn = getPlayerPawn())
	{
		playerPawn->applyEffect(toPlayerEffectType(effect));
	}
}

void PlayerEffectApplierHelper::removeEffectFromPlayer(const ItemEffectType& effect)
{
	if (auto playerPawn = getPlayerPawn())
	{
		playerPawn->removeEffect(toPlayerEffectType(effect));
	}
}

bool PlayerEffectApplierHelper::teleportCompleted()
{
	auto playerPawn = getPlayerPawn();
	return playerPawn->finishedTeleporting();
}

APlayerPawn* PlayerEffectApplierHelper::getPlayerPawn() const
{
	if (m_world == nullptr) return nullptr;

	auto playerController = m_world->GetFirstPlayerController();
	if (playerController == nullptr) return nullptr;

	return Cast<APlayerPawn>(playerController->GetPawn());
}

APlayerPawn::PlayerEffect PlayerEffectApplierHelper::toPlayerEffectType(const ItemEffectType& effectType)
{
	switch (effectType)
	{
	case ItemEffectType::SLOWDOWN:
		return APlayerPawn::Slow;
	case ItemEffectType::SPEEDUP:
		return APlayerPawn::Fast;
	case ItemEffectType::GROW:
		return APlayerPawn::Large;
	case ItemEffectType::SHRINK:
		return APlayerPawn::Small;
	case ItemEffectType::TELEPORT:
		return APlayerPawn::Teleporting;
	default:
		return APlayerPawn::Undefined;
	}
}