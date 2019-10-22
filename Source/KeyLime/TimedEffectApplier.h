#pragma once
#include "Engine\EngineTypes.h"
#include "EffectApplier.h"
#include "TimedEffectApplier.generated.h"

class FTimerManager;
class UCurrentEffectWidgetInterface;

UCLASS()
class KEYLIME_API UTimedEffectApplier : public UEffectApplier
{
	GENERATED_BODY()
public:
	UTimedEffectApplier() = default;
	virtual ~UTimedEffectApplier();

	virtual void applyEffect() override; // = 0
	virtual void clearEffect(); // = 0
	virtual bool isActive() const; // = 0

protected:
	virtual void setTimer();
	void onEffectExpired();
	float m_effectDuration{ 10.f };
	FTimerManager* m_timerManager{ nullptr };
	FTimerHandle m_effectTimerHandle;
};
