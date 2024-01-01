// ©2023 JDSherbert. All Rights Reserved.

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>

#include <Runtime/Engine/Classes/Components/ActorComponent.h>
#include <Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

#include "SprintComponent.generated.h"

/* ---------------------------- Forward Declarations ----------------------------- */

class UCharacterMovementComponent;
class UInputAction;

/* ------------------------------ Class Definition ------------------------------- */

/**
* Sprint Component Class. Performs behaviors related to sprinting.
* Receives input from EnhancedInputSystem Plugin and assigns locomotion values based on definitions in this class.
* Make sure to assign a UInputAction to define the bindings for this behavior!
*	@since 17/01/2023
*	@author JDSherbert
*/
UCLASS(ClassGroup = "Sherbert", Blueprintable, meta = (BlueprintSpawnableComponent))
class SHERBERT_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USprintComponent(const FObjectInitializer& ObjectInitializer);

	/** Sprint Input Action - Assign bindings here. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sherbert|Component|Sprint|Input")
	UInputAction* InputAction_Sprint;

	/** Default Walk Speed - Transient - Assigned by OwningActor's Locomotion Data. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Sherbert|Component|Sprint|Locomotion")
	float DefaultWalkSpeed;

	/** Default Rotation Rate - Transient - Assigned by OwningActor's Locomotion Data. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Sherbert|Component|Sprint|Locomotion")
	FRotator DefaultRotationRate;

	/** True while sprinting. */
	UPROPERTY(VisibleInstanceOnly, Category = "Sherbert|Component|Sprint|Locomotion", ReplicatedUsing=OnRep_bSprinting)
	bool bSprinting;

	/** Sprint Key Held Time - Transient - Duration the bound InputAction was held for. */
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Sherbert|Component|Sprint|Locomotion")
	float SprintKeyHoldTime;

	/** Sprinting Speed. */
	UPROPERTY(EditDefaultsOnly, Category = "Sherbert|Component|Sprint|Locomotion")
	float SprintSpeed;

	/** Sprinting Rotation Speed */
	UPROPERTY(EditDefaultsOnly, Category = "Sherbert|Component|Sprint|Locomotion")
	FRotator SprintRotationRate;

protected:

	/** Owning Actor's Character Movement Component Reference. */
	UCharacterMovementComponent* MovementComponent;

protected:

	virtual void BeginPlay() override;

public: 

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{ 
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(UBlueGhost_SprintComponent, bSprinting);
	}

protected:

	/**
	* Initializer method.
	*	@return void
	*	@since 17/01/2023
	*	@author JDSherbert
	*/
	void Init();

public:	

	/**
	* Sets Sprint Mode. Assigns values based on truth. Calls OnSprintStart and OnSprintStop events.
	*	@param bActive : Set this actor to either Sprint or not sprint.
	*	@return void
	*	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintCallable, Category = "Sherbert|Component|Sprint")
	void Sprint(const bool bActive = false); //! Not being called by the enhanced input system

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Sherbert|Component|Sprint")
	void Server_Sprint(const bool bActive = false);
	void Server_Sprint_Implementation(const bool bActive = false);
	FORCEINLINE bool Server_Sprint_Validate(const bool bActive = false) { return true; }

	/**
	* Gets Sprint Mode Truth.
	*	@return bool bSprinting
	*	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE bool Get_IsSprinting() const { return bSprinting; }

	/**
	* Sets Sprint Mode Truth.
	*	@return bool bSprinting
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintCallable, Category = "Sherbert|Component|Sprint")
	FORCEINLINE bool Set_IsSprinting(const bool bActive = false) { bSprinting = bActive; return bSprinting; }

	/**
	* Gets Sprint Speed used by the component as defined.
	*	@return float SprintSpeed
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE float Get_SprintSpeed() const { return SprintSpeed; }

	/**
	* Sets a new Sprint Speed for the component to use when sprinting.
	*	@return float SprintSpeed
	* 	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintCallable, Category = "Sherbert|Component|Sprint")
	FORCEINLINE float Set_SprintSpeed(const float NewSprintSpeed) { SprintSpeed = NewSprintSpeed; return SprintSpeed; }

	/**
	* Gets Rotation Rate used by the component as defined.
	*	@return FRotator SprintRotationRate
	* 	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE FRotator Get_RotationRate() const { return SprintRotationRate; }

	/**
	* Sets a new Rotation Speed for the component to use when sprinting.
	*	@return FRotator SprintRotationRate
	* 	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintCallable, Category = "Sherbert|Component|Sprint")
	FORCEINLINE FRotator Set_RotationRate(const FRotator NewSprintRotationRate) { SprintRotationRate = NewSprintRotationRate; return SprintRotationRate; }

	/**
	* Gets Sprint Key Hold Time.
	*	@return float SprintKeyHoldTime
	* 	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE float Get_KeyHoldTime() const { return SprintKeyHoldTime; }

	/**
	* Gets Movement Component reference used by the component as acquired on construction.
	*	@return UCharacterMovementComponent* MovementComponent
	*	@since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE UCharacterMovementComponent* Get_MovementComponent() const { return MovementComponent; }

	/**
	* Gets Sprint Key Input Action.
	*	@return UInputAction* InputAction_Sprint
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintPure, Category = "Sherbert|Component|Sprint")
	FORCEINLINE UInputAction* Get_InputAction() const { return InputAction_Sprint; }

	/**
	* Sets a new Sprint Key Input Action.
	*	@return UInputAction* InputAction_Sprint
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintCallable, Category = "Sherbert|Component|Sprint")
	FORCEINLINE UInputAction* Set_InputAction(UInputAction* NewInputAction) { InputAction_Sprint = NewInputAction; return InputAction_Sprint; }

	/* ----------------------------- RepNotify ----------------------------- */

	/**
	* Replicated. Sets new Sprint values.
	*	@return void
	* @since 13/02/2023
	*	@author JDSherbert
	*/
	UFUNCTION()
	void OnRep_bSprinting();

	/* ------------------------------ Events ------------------------------- */

	/**
	* Event: Triggers when Sprint Key Input Action is received.
	*	@return void
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Sherbert|Component|Sprint")
	void Event_OnSprintStart();

	/**
	* Event: Triggers when Sprint Key Input Action is released.
	*	@return void
	* @since 17/01/2023
	*	@author JDSherbert
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Sherbert|Component|Sprint")
	void Event_OnSprintStop();

};

/* ------------------------------------------------------------------------------- */
