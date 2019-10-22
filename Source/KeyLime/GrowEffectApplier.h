#pragma once

#include "CoreMinimal.h"
#include "TimedEffectApplier.h"
#include "GrowEffectApplier.generated.h"

UCLASS()
class KEYLIME_API UGrowEffectApplier : public UTimedEffectApplier
{
	GENERATED_BODY()
public:
	UGrowEffectApplier() = default;
	virtual ~UGrowEffectApplier() = default;

	void setEffectProperties() override;
	virtual void applyEffect() override;
	virtual void clearEffect() override;
};
