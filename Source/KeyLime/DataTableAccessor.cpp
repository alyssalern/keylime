#include "DataTableAccessor.h"

ADataTableAccessor::ADataTableAccessor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADataTableAccessor::BeginPlay()
{
	Super::BeginPlay();

}

void ADataTableAccessor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
