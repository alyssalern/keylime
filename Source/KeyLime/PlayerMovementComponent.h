#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"

class UProjectileMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEYLIME_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();
	virtual ~UPlayerMovementComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void setProjectileMovementComponent(UProjectileMovementComponent* projectileMovementComponent);
	void addInputAccelLeft();
	void addInputAccelRight();

	void increaseSpeed();
	void decreaseSpeed();

	void startTeleportMovement();
	void endTeleportMovement();

	void stop();

protected:

	struct MotionVals
	{
		float maxAbsVelocityX = 650.f;
		float maxAbsVelocityY = 500.f;
		float curAccelXWithoutFriction = 0.f;
		float absFrictionAccel = 400.f;
	};

	virtual void BeginPlay() override;
	void tickX();
	void tickY();
	void setVelocityX(float velocityX);
	float calculateFinalVelocity(float initialVelocity, float accel) const;
	float getNetAccelX() const;
	void addAccelX(float changeInAccelX);
	void adjustSpeedBy(float speedChange);

	static float addValueButKeepSign(float originalValue, float valueToAdd);
	static bool haveDifferentSigns(float a, float b);

	MotionVals m_motionVals;
	MotionVals m_savedMotionVals;
	UProjectileMovementComponent* m_projectileMovementComponent = nullptr;
	FVector m_savedProjectileVelocity;

	bool m_active{ true };
	static const float ACCEL_Y;
	static const float SPEED_CHANGE;
	static const float INPUT_ACCEL_X;
};
