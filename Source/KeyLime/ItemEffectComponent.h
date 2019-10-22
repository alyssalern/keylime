#pragma once

#include <memory>

#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemEffectComponent.generated.h"

class UEffectApplierInterface;
class AKeyLimeGameModeBase;

UCLASS()
class KEYLIME_API UItemEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemEffectComponent() = default;
	virtual ~UItemEffectComponent() = default;
	virtual void initialize(ItemEffectType effectType, char icon);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void onPlayerHit(); // = 0;
	
protected:
	virtual void BeginPlay() override;
	AKeyLimeGameModeBase* getKeylimeGameMode() const;
	
	ItemEffectType m_effectType = ItemEffectType::UNASSIGNED;

};
