#pragma once

#include "CoreMinimal.h"
#include "TimedEffectApplier.h"
#include "ShrinkEffectApplier.generated.h"

UCLASS()
class KEYLIME_API UShrinkEffectApplier : public UTimedEffectApplier
{
	GENERATED_BODY()
public:
	UShrinkEffectApplier() = default;
	virtual ~UShrinkEffectApplier() = default;

	void setEffectProperties() override;
	virtual void applyEffect() override;
	virtual void clearEffect() override;
};
