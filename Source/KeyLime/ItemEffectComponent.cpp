#include "ItemEffectComponent.h"
#include "KeyLimeGameModeBase.h"
#include "Engine/World.h"

void UItemEffectComponent::initialize(ItemEffectType effectType, char icon)
{
	m_effectType = effectType;
}

void UItemEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemEffectComponent::onPlayerHit()
{
	// pure virtual
}

void UItemEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

AKeyLimeGameModeBase* UItemEffectComponent::getKeylimeGameMode() const
{
	auto world = GetWorld();
	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MIKO6:UInstantItemEffectComponent - Failed to find world"));
		return nullptr;
	}

	return world->GetAuthGameMode<AKeyLimeGameModeBase>();
}

