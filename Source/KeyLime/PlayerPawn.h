#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UStaticMeshComponent;
class UShapeComponent;
class UPlayerMovementComponent;
class UProjectileMovementComponent;

UCLASS()
class KEYLIME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	enum PlayerEffect
	{
		Undefined,
		Slow,
		Fast,
		Small,
		Large,
		Teleporting
	};

	APlayerPawn();
	virtual ~APlayerPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void onInputMoveLeft();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void onInputMoveRight();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void onInputStopMovingLeft();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void onInputStopMovingRight();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void onLevelEnd();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void onTimerExpired();

	void applyEffect(const PlayerEffect& effect);
	void removeEffect(const PlayerEffect& effect);

	template <class T>
	T* findComponentByType(const FString& name)
	{
		TArray<T*> components;
		GetComponents<T>(components);

		if (components.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("APlayerPawn::findComponentByType<%s> - Failed to find component"), *name);
			return nullptr;
		}
		if (components.Num() > 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("APlayerPawn::findColisionComponent<%s> - Found more than one component"), *name);
		}
		return components.Pop();
	}

	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	FVector getMeshComponentLocation() const;

	bool finishedTeleporting();

protected:

	enum InputDirection
	{
		None,
		Left,
		Right
	};

	virtual void BeginPlay() override;
	UStaticMeshComponent* findMeshComponent();
	UStaticMeshComponent* findTeleportIndicatorMeshComponent();
	UShapeComponent* findCollisionComponent();
	UProjectileMovementComponent* findProjectileMovementComponent();
	UPlayerMovementComponent* findPlayerMovementComponent();
	
	bool m_levelComplete{ false };
	void removeAllEffects();
	bool effectIsActive(PlayerEffect effect);
	void adjustMeshSize(float growBy);

	UStaticMeshComponent* m_meshComponent{ nullptr };
	UStaticMeshComponent* m_teleportIndicatorMeshComponent{ nullptr };
	UShapeComponent* m_collisionComponent{ nullptr };
	UPlayerMovementComponent* m_playerMovementComponent{ nullptr };
	TSet<PlayerEffect> m_activeEffects;
	InputDirection m_inputDirection{ None };

	float m_teleportGoal{ 0.f };

	static constexpr float SHRINK_FACTOR{ 0.75f };
	static constexpr float GROW_FACTOR{ 1.5f };
};
