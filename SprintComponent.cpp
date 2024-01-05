// ©2023 JDSherbert. All Rights Reserved.

#include "Project/Public/Components/SprintComponent.h"

#include <Runtime/Engine/Classes/Components/InputComponent.h>
#include <Runtime/Engine/Classes/GameFramework/Character.h>

#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"

/* --------------------------------- Namespace ----------------------------------- */

namespace SprintComponentDefs
{
	constexpr float DefaultSprintSpeed = 1000.0f;
	const FRotator DefaultSprintRotationSpeed = FRotator(0.0f, 50.0f, 0.0f);
}

/* ---------------------------- Method Definitions ------------------------------- */

USprintComponent::USprintComponent(const FObjectInitializer& ObjectInitializer)
	: SprintInputAction(nullptr)
	, DefaultWalkSpeed(0.0f)
	, DefaultRotationRate(FRotator(0.0f, 0.0f, 0.0f))
	, bSprinting(false)
	, SprintKeyHoldTime(0.0f)
	, SprintSpeed(SprintComponentDefs::DefaultSprintSpeed)
	, SprintRotationRate(SprintComponentDefs::DefaultSprintRotationSpeed)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::Init()
{
	if (AActor* Owner = GetOwner())
	{
		/** 
  		* This should happen automatically - 
  		* AActor will handle the initialization of its own subcomponents!
		*/
		// RegisterComponent();

		if (ACharacter* Character = CastChecked<ACharacter>(Owner))
		{
			if (UEnhancedInputComponent* TempInput = Character->EnhancedInputComponent)
			{
				TempInput->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &USprintComponent::Sprint, true); //! Not working
				TempInput->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &USprintComponent::Sprint, false);
			}
		}
		
		if (UCharacterMovementComponent* TempMovementComponent = CastChecked<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
		{
			MovementComponent = TempMovementComponent;
			DefaultWalkSpeed = MovementComponent->MaxWalkSpeed;
			DefaultRotationRate = MovementComponent->RotationRate;
		}
	}
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::Sprint(const bool bActive /*= false*/)
{
	Server_Sprint(bActive);
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::Server_Sprint_Implementation(const bool bActive /* = false*/)
{
	SetSprinting(bActive);
	if (IsSprinting()) SprintKeyHoldTime += FApp::GetDeltaTime();
	else if (SprintKeyHoldTime != 0.0f) SprintKeyHoldTime = 0.0f;

	if (UCharacterMovementComponent* CharacterMovementComponent = GetMovementComponent())
	{
		CharacterMovementComponent->MaxWalkSpeed = (IsSprinting()) ? SprintSpeed : DefaultWalkSpeed;
		CharacterMovementComponent->RotationRate = (IsSprinting()) ? SprintRotationRate : DefaultRotationRate;
	}
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::OnRep_bSprinting()
{
	(IsSprinting()) ? Event_OnSprintStart() : Event_OnSprintStop();
}

/* ------------------------------------------------------------------------------- */
