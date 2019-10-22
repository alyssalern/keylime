#pragma once

#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectApplier.generated.h"

class IEffectWidgetCollection;

UCLASS()
class KEYLIME_API UEffectApplier : public UObject
{
	GENERATED_BODY()
public:
	UEffectApplier() = default;
	virtual ~UEffectApplier() = default;
	
	void initialize(IEffectWidgetCollection* effectWidgetCollection);

	virtual void setEffectProperties();
	virtual void applyEffect(); // = 0

	FString getName() const;
	ItemEffectType getEffectType() const;

protected:
	FString m_effectName;
	ItemEffectType m_effectType{ ItemEffectType::UNASSIGNED };

	IEffectWidgetCollection* m_effectWidgets{ nullptr };
};
