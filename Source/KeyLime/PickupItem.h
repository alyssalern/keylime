#pragma once
#include <memory>
#include <map>
#include "ItemEffectTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class UItemEffectComponent;

UCLASS()
class KEYLIME_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupItem();

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& e) override;
#endif

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void onPlayerHit();

	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	bool HasBeenHit = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TEnumAsByte<ItemEffectType> effectType = ItemEffectType::UNASSIGNED;

	UPROPERTY()
	UItemEffectComponent* m_itemEffectComponent{ nullptr };

private:
	UStaticMeshComponent* findMeshComponent();
	void createItemEffectComponent();
	bool setMesh(UStaticMeshComponent* meshComponent, const FName& pickupItemTableRowId);
};
