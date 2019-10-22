#include "PlayerPawn.h"
#include "KeylimeGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "PlayerMovementComponent.h"

APlayerPawn::APlayerPawn()
	: APawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

APlayerPawn::~APlayerPawn()
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	m_meshComponent = findMeshComponent();
	m_teleportIndicatorMeshComponent = findTeleportIndicatorMeshComponent();
	m_collisionComponent = findCollisionComponent();
	m_playerMovementComponent = findPlayerMovementComponent();
	if (m_playerMovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find player movement component."));
		return;
	}
	m_playerMovementComponent->setProjectileMovementComponent(findProjectileMovementComponent());
	removeAllEffects();
}

UStaticMeshComponent* APlayerPawn::findMeshComponent()
{
	auto meshComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("StaticMesh")));
	if (meshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("APlayerPawn::findMeshComponent - Could not find player mesh component."));
		return nullptr;
	}
	return meshComponent;
}

UStaticMeshComponent* APlayerPawn::findTeleportIndicatorMeshComponent()
{
	auto teleportIndicatorMeshComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("TeleportIndicatorMesh")));
	if (teleportIndicatorMeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("APlayerPawn::findMeshComponent - Could not find teleport indicator mesh component."));
		return nullptr;
	}
	return teleportIndicatorMeshComponent;
}

UShapeComponent* APlayerPawn::findCollisionComponent()
{
	auto collisionComponent = Cast<UShapeComponent>(GetDefaultSubobjectByName(TEXT("PlayerSphere")));
	if (collisionComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("APlayerPawn::findMeshComponent - Could not find collision component."));
		return nullptr;
	}
	return collisionComponent;
}

UProjectileMovementComponent* APlayerPawn::findProjectileMovementComponent()
{
	return findComponentByType<UProjectileMovementComponent>("UProjectileMovementComponent");
}

UPlayerMovementComponent* APlayerPawn::findPlayerMovementComponent()
{
	return findComponentByType<UPlayerMovementComponent>("UPlayerMovementComponent");
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::onInputMoveLeft()
{
	if (m_levelComplete) return;
	if (m_inputDirection == InputDirection::Right)
	{
		onInputStopMovingRight();
	}
	if (m_inputDirection == InputDirection::None)
	{
		m_playerMovementComponent->addInputAccelLeft();
		m_inputDirection = InputDirection::Left;
	}
}

void APlayerPawn::onInputStopMovingLeft()
{
	if (m_levelComplete) return;
	if (m_inputDirection == InputDirection::Left)
	{
		m_playerMovementComponent->addInputAccelRight();
		m_inputDirection = InputDirection::None;
	}
}

void APlayerPawn::onInputMoveRight()
{
	if (m_levelComplete) return;
	if (m_inputDirection == InputDirection::Left)
	{
		onInputStopMovingLeft();
	}
	if (m_inputDirection == InputDirection::None)
	{
		m_playerMovementComponent->addInputAccelRight();
		m_inputDirection = InputDirection::Right;
	}
}

void APlayerPawn::onInputStopMovingRight()
{
	if (m_levelComplete) return;
	if (m_inputDirection == InputDirection::Right)
	{
		m_playerMovementComponent->addInputAccelLeft();
		m_inputDirection = InputDirection::None;
	}
}

void APlayerPawn::onLevelEnd()
{
	m_levelComplete = true;
	m_playerMovementComponent->stop();
}

void APlayerPawn::onTimerExpired()
{
	m_levelComplete = false;
	m_playerMovementComponent->stop();
}

void APlayerPawn::applyEffect(const PlayerEffect& effect)
{
	if (effect == PlayerEffect::Undefined)
	{
		return;
	}

	if (!m_activeEffects.Contains(effect))
	{
		m_activeEffects.Add(effect);
	}
	switch (effect)
	{
	case PlayerEffect::Slow:
		m_playerMovementComponent->decreaseSpeed();
		return;
	case PlayerEffect::Fast:
		m_playerMovementComponent->increaseSpeed();
		return;
	case PlayerEffect::Small:
		adjustMeshSize(SHRINK_FACTOR);
		return;
	case PlayerEffect::Large:
		adjustMeshSize(GROW_FACTOR);
		return;
	case PlayerEffect::Teleporting:
		SetActorEnableCollision(false);
		auto gameInstance = Cast<UKeylimeGameInstance>(GetWorld()->GetGameInstance());
		m_teleportGoal = m_teleportIndicatorMeshComponent->GetComponentLocation().X;
		m_playerMovementComponent->startTeleportMovement();
		return;
	}
}

void APlayerPawn::removeEffect(const PlayerEffect& effect)
{
	if (effect == PlayerEffect::Undefined)
	{
		return;
	}

	if (!m_activeEffects.Contains(effect))
	{
		return;
	}
	m_activeEffects.Remove(effect);
	switch (effect)
	{
	case PlayerEffect::Slow:
		m_playerMovementComponent->increaseSpeed();
		return;
	case PlayerEffect::Fast:
		m_playerMovementComponent->decreaseSpeed();
		return;
	case PlayerEffect::Small:
	case PlayerEffect::Large:
		adjustMeshSize(1.f);
		return;
	case PlayerEffect::Teleporting:
		m_playerMovementComponent->endTeleportMovement();
		m_teleportGoal = 0.f;
		SetActorEnableCollision(true);
		return;
	}
}

void APlayerPawn::adjustMeshSize(float growBy)
{
	UE_LOG(LogTemp, Log, TEXT("MIKO6:Adjusting mesh size by %.2f"), growBy);
	// We are scaling the collision component because it is the parent of the mesh component
	m_collisionComponent->SetRelativeScale3D(FVector(growBy));
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::removeAllEffects()
{
	for (const auto& effect : m_activeEffects)
	{
		removeEffect(effect);
	}
}

bool APlayerPawn::effectIsActive(PlayerEffect effect)
{
	return m_activeEffects.Contains(effect);
}

bool APlayerPawn::finishedTeleporting()
{
	return m_meshComponent->GetComponentLocation().X >= m_teleportGoal;
}