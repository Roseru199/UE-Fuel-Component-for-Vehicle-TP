#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FuelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoFuel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetFuel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedFuelAmount);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLEFUELTP_API UFuelComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/*Max fuel of fuel tank*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fuel")
		float MaxFuel;

	/*Amount of fuel at this moment*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
		float Fuel = 1.0f;

	/*Rate of car L/km*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
		float Rate;

	/*Throttle curve. Rate depend on this curve. Can get rate by throttle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
		UCurveFloat* ThrottleCurve;

	/*Calculate rate*/
	UFUNCTION(BlueprintCallable)
		void CalculateRate(float Throttle);

	/*Calculate fuel. Must be used in Tick event or if you have a DeltaTime*/
	UFUNCTION(BlueprintCallable)
		void CalculateFuel(float DeltaTime, float Speed);

	/*If no fuel this delegate will be execute*/
	UPROPERTY(BlueprintAssignable)
		FOnNoFuel OnNoFuel;

	/*If fuel has reseted this delegate will be execute*/
	UPROPERTY(BlueprintAssignable)
		FOnResetFuel OnResetFuel;

	/*Execute every change of fuel amount*/
	UPROPERTY(BlueprintAssignable)
		FOnChangedFuelAmount OnChangedFuelAmount;

	UFuelComponent();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};