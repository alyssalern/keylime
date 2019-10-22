#pragma once

#include <set>
#include "CoreMinimal.h"
#include "ItemEffectTypes.h"
#include "UObject/NoExportTypes.h"
#include "CurrentEffectWidgetInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FCurrentEffectsChangedDelegate, int, effectType0, int, effectType1, int, effectType2, int, effectType3);

UCLASS(Blueprintable)
class KEYLIME_API UCurrentEffectWidgetInterface : public UObject
{
	GENERATED_BODY()
public:
	UCurrentEffectWidgetInterface() = default;
	void initialize();

	void effectApplied(ItemEffectType effectType);
	void effectTimedOut(ItemEffectType effectType);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FCurrentEffectsChangedDelegate onCurrentEffectsChangedDelegate;
	
private:
	void broadcastCurrentEffects() const;
	std::set<int> m_currentEffects;
};
