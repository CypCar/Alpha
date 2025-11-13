#include "Components/AttackComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
UAttackComponent::UAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

//==========================================================================
// BEGIN PLAY
//==========================================================================
void UAttackComponent::BeginPlay()
{
    Super::BeginPlay();
}

//==========================================================================
// ATTACK INPUT HANDLING
//==========================================================================
void UAttackComponent::OnAttackInput()
{
    if (!bIsAttacking)
    {
        bIsAttacking = true;
        CurrentComboIndex = 0;
        bQueuedNextAttack = false;
        PlayAttackMontage();
    }
    else if (bComboWindowOpen)
    {
        QueueNextAttack();
    }
}

void UAttackComponent::QueueNextAttack()
{
    if (CurrentComboIndex + 1 < MaxCombo)
    {
        bQueuedNextAttack = true;
        GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
        GetWorld()->GetTimerManager().SetTimer(ComboResetTimerHandle, this, &UAttackComponent::ResetCombo, ComboInputWindow, false);
    }
}

//==========================================================================
// COMBO SYSTEM
//==========================================================================
void UAttackComponent::StopCombo()
{
    bIsAttacking = false;
    bQueuedNextAttack = false;
    CurrentComboIndex = 0;
    AlreadyHitActors.Reset();
    GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);

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
    bIsAttacking = false;
    bQueuedNextAttack = false;
    CurrentComboIndex = 0;
    AlreadyHitActors.Reset();
    GetWorld()->GetTimerManager().ClearTimer(ComboResetTimerHandle);
}

//==========================================================================
// ANIMATION SYSTEM
//==========================================================================
void UAttackComponent::PlayAttackMontage() const
{
    const ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar || !AttackMontage) return;

    UAnimInstance* AnimInst = OwnerChar->GetMesh()->GetAnimInstance();
    if (!AnimInst) return;

    FName SectionName = FName(*FString::Printf(TEXT("Attack_%d"), CurrentComboIndex + 1));
    AnimInst->Montage_Play(AttackMontage, 1.0f);
    
    if (AnimInst->Montage_IsActive(AttackMontage))
    {
        AnimInst->Montage_JumpToSection(SectionName, AttackMontage);
    }

    if (SwingSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SwingSound, OwnerChar->GetActorLocation());
    }
}

//==========================================================================
// TRACE SYSTEM
//==========================================================================
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

    FHitResult Hit;
    const bool bHit = GetWorld()->SweepSingleByChannel(
        Hit,
        Start,
        End,
        FQuat::Identity,
        ECC_Pawn,
        FCollisionShape::MakeSphere(TraceRadius),
        Params
    );

    if (bHit && Hit.GetActor())
    {
        AActor* HitActor = Hit.GetActor();

        if (AlreadyHitActors.Contains(HitActor))
        {
            return;
        }
        AlreadyHitActors.Add(HitActor);

        UGameplayStatics::ApplyPointDamage(HitActor, AttackDamage, (End - Start).GetSafeNormal(), Hit, OwnerChar->GetController(), OwnerActor, DamageTypeClass);

        if (HitParticle)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
        }

        OnAttackHit.Broadcast(HitActor);
    }
}

void UAttackComponent::PerformSwordTrace()
{
    DoSwordTrace();
}

void UAttackComponent::SwordTraceTick()
{
    DoSwordTrace();
}

//==========================================================================
// ANIMATION NOTIFY HANDLERS
//==========================================================================
void UAttackComponent::HandleNotify_Hit()
{
    if (!bUseContinuousTrace)
    {
        DoSwordTrace();
    }

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

void UAttackComponent::HandleNotify_ComboWindowOpen()
{
    bComboWindowOpen = true;
}

void UAttackComponent::HandleNotify_ComboWindowClose()
{
    bComboWindowOpen = false;
    bQueuedNextAttack = false;
}

void UAttackComponent::HandleNotify_SwordTraceStart()
{
    if (!bUseContinuousTrace) return;

    AlreadyHitActors.Reset();

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

void UAttackComponent::MontageNotify_PerformTrace()
{
    DoSwordTrace();
}