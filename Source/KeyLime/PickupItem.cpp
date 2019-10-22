#include "PickupItem.h"
#include "InstantItemEffectComponent.h"
#include "InventoryItemEffectComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "KeylimeGameInstance.h"
#include "PickupItemStruct.h"
#include "ItemEffectComponent.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

#if WITH_EDITOR
void APickupItem::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	AActor::PostEditChangeProperty(e);

	auto enumProperty = Cast<UNumericProperty>(e.MemberProperty);
	if (enumProperty == nullptr) return;

	ItemEffectType* effectType = enumProperty->ContainerPtrToValuePtr<ItemEffectType>(this);
	if (effectType == nullptr) return;

	UStaticMeshComponent* meshComponent = findMeshComponent();
	if (meshComponent == nullptr) return;

	FString pickupItemTableRowId = FString("pickupItem") + FString::FromInt(static_cast<int32>(*effectType));
	setMesh(meshComponent, FName(*pickupItemTableRowId));
}
#endif

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupItem::onPlayerHit()
{
	if (!HasBeenHit && m_itemEffectComponent != nullptr)
	{
		HasBeenHit = true;
		m_itemEffectComponent->onPlayerHit();
	}
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	createItemEffectComponent();
}

UStaticMeshComponent* APickupItem::findMeshComponent()
{
	TArray<UStaticMeshComponent*> meshComponents;
	GetComponents<UStaticMeshComponent>(meshComponents);

	for (const auto& meshComponent : meshComponents)
	{
		if (dynamic_cast<UStaticMeshComponent*>(meshComponent) != nullptr)
		{
			return meshComponent;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("MIKO6:APickupItem - Error: Failed to find static mesh"));
	return nullptr;
}

void APickupItem::createItemEffectComponent()
{
	if (effectType == ItemEffectType::TELEPORT)
	{
		m_itemEffectComponent = NewObject<UInventoryItemEffectComponent>(this);
	}
	else if(effectType != ItemEffectType::UNASSIGNED)
	{
		m_itemEffectComponent = NewObject<UInstantItemEffectComponent>(this);
	}

	if (m_itemEffectComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MIKO6:APickupItem - Failed to create ItemEffectComponent"))
		return;
	}
	if (m_itemEffectComponent)
	{
		m_itemEffectComponent->RegisterComponent();
		m_itemEffectComponent->initialize(effectType, 's');
	}
}

bool APickupItem::setMesh(UStaticMeshComponent* meshComponent, const FName& pickupItemTableRowId)
{
	auto world = GetWorld();
	auto gameInstance = Cast<UKeylimeGameInstance>(world->GetGameInstance());
	if (gameInstance == nullptr) return false;
	
	auto tableRow = gameInstance->getPickupItemDataTableRow(pickupItemTableRowId);
	if (tableRow == nullptr) return false;
	auto meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *(tableRow->meshLocation)));
	if (meshToUse == nullptr) return false;

	UE_LOG(LogTemp, Log, TEXT("MIKO6:Setting pickup item mesh to %s"), *(tableRow->meshLocation))
	meshComponent->SetStaticMesh(meshToUse);
	return true;
}
