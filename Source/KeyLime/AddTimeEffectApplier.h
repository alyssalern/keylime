#pragma once

#include "CoreMinimal.h"
#include "EffectApplier.h"
#include "AddTimeEffectApplier.generated.h"

UCLASS()
class KEYLIME_API UAddTimeEffectApplier : public UEffectApplier
{
	GENERATED_BODY()
public:
	UAddTimeEffectApplier() = default;

	void setEffectProperties() override;
	void applyEffect() override;

private:
	int m_secondsToAdd{ 5 };
};
