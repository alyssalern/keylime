#pragma once

#include <chrono>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KeyLimeGameModeBase.generated.h"

class APlayerPawn;
class UInventory;
class UCurrentEffectWidgetInterface;
class ULevelTimerWidgetInterface;

UCLASS()
class KEYLIME_API AKeyLimeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AKeyLimeGameModeBase();
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Timers")
	void stopLevelTimer();

	UFUNCTION(BlueprintCallable, Category = "Timers")
	FString getLevelDuration() const;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	UInventory* getInventory() const;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	UEffectApplierInterface* getEffectApplierInterface() const;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	UCurrentEffectWidgetInterface* getCurrentEffectWidgetInterface() const;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	ULevelTimerWidgetInterface* getLevelTimerWidgetInterface() const;

private:
	std::chrono::steady_clock::time_point m_levelStartTime;
	std::chrono::milliseconds m_levelDuration{ std::chrono::duration_values<std::chrono::milliseconds>::min() };

	UPROPERTY()
	UEffectApplierInterface* m_effectApplierInterface { nullptr };

	UPROPERTY()
	UInventory* m_inventory { nullptr };
};
