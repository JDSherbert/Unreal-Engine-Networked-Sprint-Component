// ©2023 JDSherbert. All Rights Reserved.

#include "Project/Public/Components/SprintComponent.h"

#include <Runtime/Engine/Classes/Components/InputComponent.h>
#include <Runtime/Engine/Classes/GameFramework/Character.h>

#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"

/* --------------------------------- Namespace ----------------------------------- */

namespace SprintComponentDefs
{
	const TCHAR* ClassPath_InputAction_Sprint = TEXT("/Game/Project/Blueprints/Input/Actions/InputAction_Sprint.uasset");
	constexpr float Default_SprintSpeed = 1000.0f;
	const FRotator Default_SprintRotationSpeed = FRotator(0.0f, 50.0f, 0.0f);
}

/* ---------------------------- Method Definition -------------------------------- */

USprintComponent::USprintComponent(const FObjectInitializer& ObjectInitializer)
	: InputAction_Sprint(nullptr)
	, DefaultWalkSpeed(0.0f)
	, DefaultRotationRate(FRotator(0.0f, 0.0f, 0.0f))
	, bSprinting(false)
	, SprintKeyHoldTime(0.0f)
	, SprintSpeed(SprintComponentDefs::Default_SprintSpeed)
	, SprintRotationRate(SprintComponentDefs::Default_SprintRotationSpeed)
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
		RegisterComponent();

		if (ACharacter* Character = CastChecked<ACharacter>(Owner))
		{
			if (UEnhancedInputComponent* TempInput = Character->EnhancedInputComponent)
			{
				TempInput->BindAction(InputAction_Sprint, ETriggerEvent::Triggered, this, &USprintComponent::Sprint, true); //! Not working
				TempInput->BindAction(InputAction_Sprint, ETriggerEvent::Completed, this, &USprintComponent::Sprint, false);
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
	Set_IsSprinting(bActive);
	if (Get_IsSprinting()) SprintKeyHoldTime += FApp::GetDeltaTime();
	else if (SprintKeyHoldTime != 0.0f) SprintKeyHoldTime = 0.0f;

	if (Get_MovementComponent())
	{
		Get_MovementComponent()->MaxWalkSpeed = (Get_IsSprinting()) ? SprintSpeed : DefaultWalkSpeed;
		Get_MovementComponent()->RotationRate = (Get_IsSprinting()) ? SprintRotationRate : DefaultRotationRate;
	}
}

/* ------------------------------------------------------------------------------- */

void USprintComponent::OnRep_bSprinting()
{
	(Get_IsSprinting()) ? Event_OnSprintStart() : Event_OnSprintStop();
}

/* ------------------------------------------------------------------------------- */
