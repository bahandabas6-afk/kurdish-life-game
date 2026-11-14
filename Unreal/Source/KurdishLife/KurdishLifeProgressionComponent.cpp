#include "KurdishLifeProgressionComponent.h"

UKurdishLifeProgressionComponent::UKurdishLifeProgressionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UKurdishLifeProgressionComponent::SpendMoney(int32 Amount)
{
    if (Amount <= 0 || Money < Amount) return false;
    Money -= Amount;
    OnMoneyChanged.Broadcast(Money, -Amount);
    return true;
}

void UKurdishLifeProgressionComponent::AddMoney(int32 Amount)
{
    if (Amount <= 0) return;
    Money += Amount;
    OnMoneyChanged.Broadcast(Money, Amount);
}

bool UKurdishLifeProgressionComponent::StartJob(const FString& JobName)
{
    if (JobName.IsEmpty() || !ActiveJob.IsEmpty()) return false;
    ActiveJob = JobName;
    OnTaskUpdated.Broadcast(ActiveJob);
    return true;
}

bool UKurdishLifeProgressionComponent::FinishJob(int32 Payment)
{
    if (ActiveJob.IsEmpty() || Payment < 0) return false;
    const FString Finished = ActiveJob;
    ActiveJob.Empty();
    if (Payment > 0) AddMoney(Payment);
    OnTaskUpdated.Broadcast(FString::Printf(TEXT("Job complete: %s"), *Finished));
    return true;
}

bool UKurdishLifeProgressionComponent::AcceptMission(const FString& MissionName)
{
    if (MissionName.IsEmpty() || !ActiveMission.IsEmpty()) return false;
    ActiveMission = MissionName;
    OnTaskUpdated.Broadcast(ActiveMission);
    return true;
}

bool UKurdishLifeProgressionComponent::CompleteMission(int32 Reward)
{
    if (ActiveMission.IsEmpty() || Reward < 0) return false;
    const FString Finished = ActiveMission;
    ActiveMission.Empty();
    if (Reward > 0) AddMoney(Reward);
    OnTaskUpdated.Broadcast(FString::Printf(TEXT("Mission complete: %s"), *Finished));
    return true;
}
