#pragma once

#include "CoreMinimal.h"
#include "TimedEffectApplier.h"
#include "TeleportEffectApplier.generated.h"

class FTimerManager;

UCLASS()
class KEYLIME_API UTeleportEffectApplier : public UTimedEffectApplier
{
	GENERATED_BODY()
public:
	UTeleportEffectApplier() = default;
	virtual ~UTeleportEffectApplier() = default;

	void setEffectProperties() override;
	virtual void applyEffect() override;
	virtual void clearEffect() override;

protected:
	void setTimer();

private:
	void checkIfDestinationReached();
};
