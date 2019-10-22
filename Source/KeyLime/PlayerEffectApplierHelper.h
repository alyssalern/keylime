#pragma once

#include "PlayerPawn.h"
#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include <memory>

class UWorld;

class KEYLIME_API PlayerEffectApplierHelper
{
public:
	static void setWorld(UWorld* world);
	static std::shared_ptr<PlayerEffectApplierHelper> getInstance();
	~PlayerEffectApplierHelper() = default;

	void applyEffectToPlayer(const ItemEffectType& effect);
	void removeEffectFromPlayer(const ItemEffectType& effect);

	bool teleportCompleted();

private:
	PlayerEffectApplierHelper() = default;
	APlayerPawn* getPlayerPawn() const;
	static APlayerPawn::PlayerEffect toPlayerEffectType(const ItemEffectType& effectType);
	static UWorld* m_world;
	static std::shared_ptr<PlayerEffectApplierHelper> m_instance;
};
