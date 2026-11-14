#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KurdishLifeProgressionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FKLMoneyChanged, int32, NewBalance, int32, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKLTaskUpdated, const FString&, TaskName);

UCLASS(ClassGroup=(KurdishLife), meta=(BlueprintSpawnableComponent))
class KURDISHLIFE_API UKurdishLifeProgressionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UKurdishLifeProgressionComponent();

    UPROPERTY(BlueprintAssignable, Category="Kurdish Life|Economy")
    FKLMoneyChanged OnMoneyChanged;

    UPROPERTY(BlueprintAssignable, Category="Kurdish Life|Tasks")
    FKLTaskUpdated OnTaskUpdated;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Kurdish Life|Economy")
    int32 Money = 500;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Kurdish Life|Jobs")
    FString ActiveJob;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Kurdish Life|Missions")
    FString ActiveMission;

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Economy")
    bool SpendMoney(int32 Amount);

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Economy")
    void AddMoney(int32 Amount);

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Jobs")
    bool StartJob(const FString& JobName);

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Jobs")
    bool FinishJob(int32 Payment);

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Missions")
    bool AcceptMission(const FString& MissionName);

    UFUNCTION(BlueprintCallable, Category="Kurdish Life|Missions")
    bool CompleteMission(int32 Reward);
};
