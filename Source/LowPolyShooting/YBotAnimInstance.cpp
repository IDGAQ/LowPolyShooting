// Fill out your copyright notice in the Description page of Project Settings.


#include "YBotAnimInstance.h"
#include "YBotCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UYBotAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	YBotCharacter = Cast<AYBotCharacter>(TryGetPawnOwner());
}

void UYBotAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (YBotCharacter == nullptr)
	{
		YBotCharacter = Cast<AYBotCharacter>(TryGetPawnOwner());
	}
	if (YBotCharacter == nullptr) return;

	FVector Velocity = YBotCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = YBotCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = YBotCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = YBotCharacter->IsWeaponEquipped();
	bIsCrouched = YBotCharacter->bIsCrouched;
	bAiming = YBotCharacter->IsAiming();

	// Offset Yaw for Strafing
	FRotator AimRotation = YBotCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(YBotCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = YBotCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 3.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);
}

