#pragma once

#include "CoreMinimal.h"
#include "ItemEffectComponent.h"
#include "InstantItemEffectComponent.generated.h"

UCLASS()
class KEYLIME_API UInstantItemEffectComponent : public UItemEffectComponent
{
	GENERATED_BODY()

public:
	UInstantItemEffectComponent() = default;
	virtual ~UInstantItemEffectComponent() = default;

	void onPlayerHit() override;
};
