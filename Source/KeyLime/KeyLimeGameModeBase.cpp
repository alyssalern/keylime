#include "KeyLimeGameModeBase.h"

#include "EffectApplierInterface.h"
#include "Inventory.h"
#include "CurrentEffectWidgetInterface.h"
#include "LevelTimerWidgetInterface.h"
#include "PlayerEffectApplierHelper.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

AKeyLimeGameModeBase::AKeyLimeGameModeBase()
	: AGameModeBase()
{

}

void AKeyLimeGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	m_effectApplierInterface = NewObject<UEffectApplierInterface>(this);
	m_effectApplierInterface->initialize();
	PlayerEffectApplierHelper::setWorld(GetWorld());

	m_inventory = NewObject<UInventory>(this);
	m_inventory->initialize(m_effectApplierInterface);
	
	AGameModeBase::InitGame(MapName, Options, ErrorMessage);
}

void AKeyLimeGameModeBase::StartPlay()
{
	m_levelStartTime = std::chrono::steady_clock::now();
	AGameModeBase::StartPlay();
}

void AKeyLimeGameModeBase::stopLevelTimer()
{
	m_levelDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_levelStartTime);
}

FString AKeyLimeGameModeBase::getLevelDuration() const
{
	if (m_levelDuration == std::chrono::duration_values<std::chrono::milliseconds>::min())
	{
		return FString();
	}
	int wholeSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_levelDuration).count();
	return FString::Printf(TEXT("%d.%d sec"), 
		wholeSeconds,
		m_levelDuration.count() - (wholeSeconds * 1000)
		);
}

UInventory* AKeyLimeGameModeBase::getInventory() const
{
	return m_inventory;
}

UEffectApplierInterface* AKeyLimeGameModeBase::getEffectApplierInterface() const
{
	return m_effectApplierInterface;
}

UCurrentEffectWidgetInterface* AKeyLimeGameModeBase::getCurrentEffectWidgetInterface() const
{
	return m_effectApplierInterface->getCurrentEffectWidgetInterface();
}

ULevelTimerWidgetInterface* AKeyLimeGameModeBase::getLevelTimerWidgetInterface() const
{
	return m_effectApplierInterface->getLevelTimerWidgetInterface();
}

