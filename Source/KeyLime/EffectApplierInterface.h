#pragma once

#include <set>
#include <map>
#include <mutex>
#include <memory>
#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "UObject/NoExportTypes.h"
#include "EffectWidgetCollection.h"
#include "EffectApplierInterface.generated.h"

class UEffectApplier;
class APlayerPawn;
class UCurrentEffectWidgetInterface;

UCLASS()
class KEYLIME_API UEffectApplierInterface : public UObject, public IEffectWidgetCollection
{
	GENERATED_BODY()
public:
	UEffectApplierInterface() = default;
	virtual ~UEffectApplierInterface() = default;
	
	void initialize();
	void applyEffect(ItemEffectType effectType);

	UCurrentEffectWidgetInterface* getCurrentEffectWidgetInterface() const override;
	ULevelTimerWidgetInterface* getLevelTimerWidgetInterface() const override;

private:
	void createEffectAppliers();
	void clearConflictingEffects(ItemEffectType effectType);
	void clearAllEffects();

	static const std::set<std::set<ItemEffectType>> CONFLICTING_EFFECT_TYPES;

	std::recursive_mutex m_effectApplierLock;

	std::map<ItemEffectType, UEffectApplier*> m_effectAppliers;

	// Must keep these references to prevent early garbage collection
	UPROPERTY()
	UEffectApplier* m_slowdownApplier{ nullptr };
	UPROPERTY()
	UEffectApplier* m_speedupApplier{ nullptr };
	UPROPERTY()
	UEffectApplier* m_growApplier{ nullptr };
	UPROPERTY()
	UEffectApplier* m_shrinkApplier{ nullptr };
	UPROPERTY()
	UEffectApplier* m_teleportApplier{ nullptr };
	UPROPERTY()
	UEffectApplier* m_addTimeApplier{ nullptr };

	UPROPERTY()
	UCurrentEffectWidgetInterface* m_currentEffectWidgetInterface{ nullptr };

	UPROPERTY()
	ULevelTimerWidgetInterface* m_levelTimerWidgetInterface{ nullptr };
};
