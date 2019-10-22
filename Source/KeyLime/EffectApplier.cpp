#include "EffectApplier.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EffectWidgetCollection.h"

void UEffectApplier::initialize(IEffectWidgetCollection* effectWidgetCollection)
{
	m_effectWidgets = effectWidgetCollection;
	setEffectProperties();
}

void UEffectApplier::setEffectProperties(){}

void UEffectApplier::applyEffect()
{
	// pure virtual
}

FString UEffectApplier::getName() const
{
	return m_effectName;
}

ItemEffectType UEffectApplier::getEffectType() const
{
	return m_effectType;
}
