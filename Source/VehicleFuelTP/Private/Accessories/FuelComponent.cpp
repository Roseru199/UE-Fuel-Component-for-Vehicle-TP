#include "Accessories/FuelComponent.h"

void UFuelComponent::CalculateRate(float Throttle)
{
	if (this->Fuel > 0)
	{
		this->Rate = ThrottleCurve->GetFloatValue(Throttle);
	}
	else
	{
		this->Rate = 0;
	}
}

void UFuelComponent::CalculateFuel(float DeltaTime, float Speed)
{
	float ConsumableFuel = this->Rate * DeltaTime * (abs(Speed) / 3600);

	if (this->Fuel <= ConsumableFuel)
	{
		this->Fuel = 0;
		
		this->OnNoFuel.Broadcast();
	}
	else
	{
		this->Fuel -= ConsumableFuel;
		
	}

	this->OnChangedFuelAmount.Broadcast();
}

UFuelComponent::UFuelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UFuelComponent::BeginPlay()
{
	Super::BeginPlay();

	this->MaxFuel = this->Fuel;
}

void UFuelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

