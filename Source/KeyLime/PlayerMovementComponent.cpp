
#include "PlayerMovementComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "KeylimeGameInstance.h"

const float UPlayerMovementComponent::ACCEL_Y = 500.f;
const float UPlayerMovementComponent::SPEED_CHANGE = 200.f;
const float UPlayerMovementComponent::INPUT_ACCEL_X = 1400.f;

UPlayerMovementComponent::UPlayerMovementComponent()
	: UActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UPlayerMovementComponent::~UPlayerMovementComponent()
{

}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!m_active) return;
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	tickX();
	tickY();

	m_projectileMovementComponent->Velocity.X = FMath::Clamp(m_projectileMovementComponent->Velocity.X, -m_motionVals.maxAbsVelocityX, m_motionVals.maxAbsVelocityX);
	m_projectileMovementComponent->Velocity.Y = FMath::Clamp(m_projectileMovementComponent->Velocity.Y, -m_motionVals.maxAbsVelocityY, m_motionVals.maxAbsVelocityY);
}

void UPlayerMovementComponent::setProjectileMovementComponent(UProjectileMovementComponent* projectileMovementComponent)
{
	m_projectileMovementComponent = projectileMovementComponent;
}

void UPlayerMovementComponent::addInputAccelLeft()
{
	addAccelX(-INPUT_ACCEL_X);
}

void UPlayerMovementComponent::addInputAccelRight()
{
	addAccelX(INPUT_ACCEL_X);
}

void UPlayerMovementComponent::increaseSpeed()
{
	adjustSpeedBy(SPEED_CHANGE);
}

void UPlayerMovementComponent::decreaseSpeed()
{
	adjustSpeedBy(-SPEED_CHANGE);
}


void UPlayerMovementComponent::startTeleportMovement()
{
	m_savedMotionVals = m_motionVals;
	m_savedProjectileVelocity = m_projectileMovementComponent->Velocity;

	m_motionVals.maxAbsVelocityX = 99999;
	m_motionVals.maxAbsVelocityY = 0.f;
	m_motionVals.curAccelXWithoutFriction = 0.f;
	m_motionVals.absFrictionAccel = 0.f;

	auto gameInstance = Cast<UKeylimeGameInstance>(GetWorld()->GetGameInstance());
	float teleportVelocity = gameInstance->teleportDistance / gameInstance->teleportTimeInSecs;
	m_projectileMovementComponent->Velocity = FVector(teleportVelocity, 0.f, 0.f);
}

void UPlayerMovementComponent::endTeleportMovement()
{
	m_motionVals = m_savedMotionVals;
	m_projectileMovementComponent->Velocity = m_savedProjectileVelocity;
}

void UPlayerMovementComponent::stop()
{
	m_projectileMovementComponent->Velocity.X = 0.f;
	m_projectileMovementComponent->Velocity.Y = 0.f;
	m_projectileMovementComponent->Deactivate();
	m_active = false;
}

void UPlayerMovementComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
}

void UPlayerMovementComponent::tickX()
{
	float finalVelocityX = m_projectileMovementComponent->Velocity.X + (getNetAccelX() * UGameplayStatics::GetWorldDeltaSeconds(this));
	setVelocityX(finalVelocityX);
}

void UPlayerMovementComponent::tickY()
{
	float initialVelocityY = FMath::Clamp(m_projectileMovementComponent->Velocity.Y, -m_motionVals.maxAbsVelocityY, m_motionVals.maxAbsVelocityY);
	if (FMath::Abs(initialVelocityY) > m_motionVals.maxAbsVelocityY - 0.0001f) return;

	float absFinalVelocityY = calculateFinalVelocity(FMath::Abs(initialVelocityY), ACCEL_Y);

	m_projectileMovementComponent->Velocity.Y = (initialVelocityY < 0.f) ? -absFinalVelocityY : absFinalVelocityY;
}

void UPlayerMovementComponent::setVelocityX(float velocityX)
{
	velocityX = FMath::Clamp(velocityX, -m_motionVals.maxAbsVelocityX, m_motionVals.maxAbsVelocityX);

	float formerVelocityX = m_projectileMovementComponent->Velocity.X;
	m_projectileMovementComponent->Velocity.X = velocityX;

	if (haveDifferentSigns(formerVelocityX, velocityX) && FMath::Abs(m_motionVals.curAccelXWithoutFriction) < 0.0001)
	{
		m_projectileMovementComponent->Velocity.X = 0.f;
	}
}

float UPlayerMovementComponent::calculateFinalVelocity(float initialVelocity, float accel) const
{
	return initialVelocity + (UGameplayStatics::GetWorldDeltaSeconds(this) * accel);
}

float UPlayerMovementComponent::getNetAccelX() const
{
	if (FMath::Abs(m_projectileMovementComponent->Velocity.X) < 0.001f)
	{
		return m_motionVals.curAccelXWithoutFriction;
	}
	if (m_projectileMovementComponent->Velocity.X > 0.f)
	{
		return m_motionVals.curAccelXWithoutFriction - m_motionVals.absFrictionAccel;
	}

	return m_motionVals.curAccelXWithoutFriction + m_motionVals.absFrictionAccel;
}

void UPlayerMovementComponent::addAccelX(float changeInAccelX)
{
	m_motionVals.curAccelXWithoutFriction += changeInAccelX;
}

void UPlayerMovementComponent::adjustSpeedBy(float speedChange)
{
	m_motionVals.maxAbsVelocityY += speedChange;
	m_motionVals.maxAbsVelocityX += speedChange;

	float finalVelocityY = addValueButKeepSign(m_projectileMovementComponent->Velocity.Y, speedChange);
	float finalVelocityX = addValueButKeepSign(m_projectileMovementComponent->Velocity.X, speedChange);
	m_projectileMovementComponent->Velocity = FVector(finalVelocityX, finalVelocityY, 0.f);
}

float UPlayerMovementComponent::addValueButKeepSign(float originalValue, float valueToAdd)
{
	if (originalValue > 0.f && originalValue + valueToAdd > 0.f)
	{
		return originalValue + valueToAdd;
	}
	else if (originalValue < 0.f && originalValue - valueToAdd < 0.f)
	{
		return originalValue - valueToAdd;
	}
	return 0.f;
}

bool UPlayerMovementComponent::haveDifferentSigns(float a, float b)
{
	return (a < 0.f && b > 0.f) || (a > 0.f && b < 0.f);
}
