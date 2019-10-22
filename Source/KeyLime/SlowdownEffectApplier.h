#pragma once

#include "CoreMinimal.h"
#include "TimedEffectApplier.h"
#include "SlowdownEffectApplier.generated.h"

UCLASS()
class KEYLIME_API USlowdownEffectApplier : public UTimedEffectApplier
{
	GENERATED_BODY()
public:
	USlowdownEffectApplier() = default;
	virtual ~USlowdownEffectApplier() = default;

	void setEffectProperties() override;
	virtual void applyEffect() override;
	virtual void clearEffect() override;
};
