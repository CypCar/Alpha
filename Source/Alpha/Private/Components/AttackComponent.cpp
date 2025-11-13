#include "Components/AttackComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"

UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttackComponent::OnAttackInput()
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		CurrentComboIndex = 0;
		bQueuedNextAttack = false;
		PlayAttackMontage();
	}
	else
	{
		// przyjmujemy kolejny atak TYLKO gdy okno combo jest otwarte
		if (bComboWindowOpen)
		{
			QueueNextAttack();
		}
	}
}


void UAttackComponent::QueueNextAttack()
{
	if (CurrentComboIndex + 1 < MaxCombo)
	{
		// mark to queue - actual increment when montage completes / notify
		bQueuedNextAttack = true;

		// refresh/reset combo timer so player has window to press next
		GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UAttackComponent::ResetCombo, ComboInputWindow, false);
	}
}

void UAttackComponent::StopCombo()
{
	// Immediately cancel
	bIsAttacking = false;
	bQueuedNextAttack = false;
	CurrentComboIndex = 0;
	AlreadyHitActors.Reset();
	GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);

	// also try to stop animation
	if (ACharacter* OwnerChar = Cast<ACharacter>(GetOwner()))
	{
		if (UAnimInstance* Anim = OwnerChar->GetMesh()->GetAnimInstance())
		{
			if (AttackMontage)
			{
				Anim->Montage_Stop(0.2f, AttackMontage);
			}
		}
	}
}

void UAttackComponent::ResetCombo()
{
	// Called when combo window expired
	bIsAttacking = false;
	bQueuedNextAttack = false;
	CurrentComboIndex = 0;
	AlreadyHitActors.Reset();
	GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
}

void UAttackComponent::PlayAttackMontage() const
{
	const ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!OwnerChar || !AttackMontage) return;

	UAnimInstance* AnimInst = OwnerChar->GetMesh()->GetAnimInstance();
	if (!AnimInst) return;

	// Determine section name, assumes montage sections named Attack_1 Attack_2 Attack_3
	FName SectionName = FName(*FString::Printf(TEXT("Attack_%d"), CurrentComboIndex + 1));
	AnimInst->Montage_Play(AttackMontage, 1.0f);
	if (AnimInst->Montage_IsActive(AttackMontage))
	{
		AnimInst->Montage_JumpToSection(SectionName, AttackMontage);
	}

	// Play swing sound
	if (SwingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SwingSound, OwnerChar->GetActorLocation());
	}

	// Note: We expect an AnimNotify in the montage (named e.g., "Hit") to call AnimNotify_Hit()
	// Alternatively we can run a delayed trace here if you prefer a fixed delay:
	// GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UAttackComponent::DoSwordTrace);
}

void UAttackComponent::MontageNotify_PerformTrace()
{
	// jeśli chcesz, żeby notify z montażu robił trace:
	DoSwordTrace();
}

void UAttackComponent::PerformSwordTrace()
{
	// Public wrapper if you want to call trace manually
	DoSwordTrace();
}

void UAttackComponent::DoSwordTrace()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;

	ACharacter* OwnerChar = Cast<ACharacter>(OwnerActor);
	if (!OwnerChar) return;

	USkeletalMeshComponent* Mesh = OwnerChar->GetMesh();
	if (!Mesh) return;

	const FVector Start = Mesh->GetSocketLocation(TraceStartSocket);
	const FVector End = Mesh->GetSocketLocation(TraceEndSocket);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerActor);
	Params.bTraceComplex = true;

	// We will do a sweep (sphere) to better detect hits along blade
	FHitResult Hit;
	const bool bHit = GetWorld()->SweepSingleByChannel(
		Hit,
		Start,
		End,
		FQuat::Identity,
		ECC_Pawn, // adjust channel as needed
		FCollisionShape::MakeSphere(TraceRadius),
		Params
	);

/*#if ENABLE_DRAW_DEBUG
	const float DebugLifeTime = 0.25f; // lub 0.5f jak wolisz

	DrawDebugSphere(GetWorld(), Start, TraceRadius, 8, FColor::Blue, false, DebugLifeTime);
	DrawDebugSphere(GetWorld(), End, TraceRadius, 8, FColor::Green, false, DebugLifeTime);
	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, DebugLifeTime, 0, 1.0f);
#endif*/

	if (bHit && Hit.GetActor())
	{
		AActor* HitActor = Hit.GetActor();

		// prevent hitting same actor multiple times in same combo swing
		if (AlreadyHitActors.Contains(HitActor))
		{
			return;
		}
		AlreadyHitActors.Add(HitActor);

		// Apply damage
		UGameplayStatics::ApplyPointDamage(HitActor, AttackDamage, (End - Start).GetSafeNormal(), Hit, OwnerChar->GetController(), OwnerActor, DamageTypeClass);

		// Play hit FX
		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}

		// Notify blueprint / listeners
		OnAttackHit.Broadcast(HitActor);
	}
}

void UAttackComponent::HandleNotify_ComboWindowOpen()
{
	bComboWindowOpen = true;
}

void UAttackComponent::HandleNotify_ComboWindowClose()
{
	bComboWindowOpen = false;
	bQueuedNextAttack = false; // jak zamknięte, nie trzymamy kolejki
}

void UAttackComponent::HandleNotify_Hit()
{
	// Jeśli NIE używamy ciągłego trace'a, zrób pojedynczy w momencie Hit
	if (!bUseContinuousTrace)
	{
		DoSwordTrace();
	}

	// Dalej logika combosa:
	if (bQueuedNextAttack)
	{
		bQueuedNextAttack = false;
		CurrentComboIndex = FMath::Clamp(CurrentComboIndex + 1, 0, MaxCombo - 1);
		PlayAttackMontage();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UAttackComponent::ResetCombo, ComboInputWindow, false);
	}
}

void UAttackComponent::HandleNotify_SwordTraceStart()
{
	if (!bUseContinuousTrace) return;

	// Czyścimy listę trafionych aktorów dla nowego zamachu
	AlreadyHitActors.Reset();

	// Odpalamy timer, który w kółko woła DoSwordTrace
	if (!GetWorld()->GetTimerManager().IsTimerActive(SwordTraceTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(
			SwordTraceTimerHandle,
			this,
			&UAttackComponent::SwordTraceTick,
			TraceTickInterval,
			true
		);
	}
}

void UAttackComponent::HandleNotify_SwordTraceEnd()
{
	if (!bUseContinuousTrace) return;

	GetWorld()->GetTimerManager().ClearTimer(SwordTraceTimerHandle);
}

void UAttackComponent::SwordTraceTick()
{
	DoSwordTrace();
}
