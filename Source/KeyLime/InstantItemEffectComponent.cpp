#include "InstantItemEffectComponent.h"
#include "KeyLimeGameModeBase.h"
#include "EffectApplierInterface.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/GameInstance.h"

void UInstantItemEffectComponent::onPlayerHit()
{
	if (auto effectApplierInterface = getKeylimeGameMode()->getEffectApplierInterface())
	{
		effectApplierInterface->applyEffect(m_effectType);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UInstantItemEffectComponent::onPlayerHit - Failed to obtain EffectApplierInterface"));
	}
}