#pragma once

#include "CoreMinimal.h"
#include "TimedEffectApplier.h"
#include "SpeedupEffectApplier.generated.h"

UCLASS()
class KEYLIME_API USpeedupEffectApplier : public UTimedEffectApplier
{
	GENERATED_BODY()
public:
	USpeedupEffectApplier() = default;
	virtual ~USpeedupEffectApplier() = default;

	void setEffectProperties() override;
	virtual void applyEffect() override;
	virtual void clearEffect() override;
};
