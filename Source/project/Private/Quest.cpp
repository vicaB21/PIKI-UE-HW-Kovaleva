#include "Quest.h"

#include "QuestSettings.h"
#include "QuestCondition.h"
#include "QuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"

int32 bDebugInstantFinish = 0;
FAutoConsoleVariableRef CVarDebugInstantFinish(TEXT("quest.InstantFinish"),
    bDebugInstantFinish, TEXT("Debug Instantly Finish Quests"),
    ECVF_Cheat);

AQuest::AQuest()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AQuest::BeginPlay()
{
    Super::BeginPlay();

    AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
    UQuestSystemComponent* QuestComponent = GameMode ? GameMode->GetComponentByClass<UQuestSystemComponent>() : nullptr;
    if (QuestComponent)
    {
        QuestComponent->RegisterQuest(this);
    }
    else
    {
        UE_LOG(LogQuest, Warning, TEXT("Quest %s: quest system component not found on game mode"), *GetNameSafe(this));
    }

    if (!QuestSettings)
    {
        UE_LOG(LogQuest, Error, TEXT("Quest %s: QuestSettings is not set"), *GetNameSafe(this));
        return;
    }

    UE_LOG(LogQuest, Log, TEXT("Quest %s: begin play, start conditions: %d"),
        *GetNameSafe(this), QuestSettings->StartConditionsInst.Num());

    for (const UQuestCondition* ConditionTemplate : QuestSettings->StartConditionsInst)
    {
        if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
        {
            return;
        }
        UQuestCondition* QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
        QuestCondition->StartCondition();
        QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
        StartConditions.Add(QuestCondition);
    }
}

void AQuest::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AQuest::UpdateStartStatus()
{
    if (QuestStatus != EQuestStatus::WaitingForStart)
    {
        return;
    }

    for (UQuestCondition* Condition : StartConditions)
    {
        if (!ensure(Condition))
        {
            return;
        }
        if (!Condition->IsCompleted())
        {
            UE_LOG(LogQuest, Log, TEXT("Quest %s: start condition %s is not completed yet"),
                *GetNameSafe(this), *GetNameSafe(Condition));
            return;
        }
    }

    QuestStatus = EQuestStatus::Started;
    UE_LOG(LogQuest, Log, TEXT("Quest %s: status changed to %s"),
        *GetNameSafe(this), *UEnum::GetValueAsString(QuestStatus));

    if (bDebugInstantFinish)
    {
        QuestStatus = EQuestStatus::Completed;
        UE_LOG(LogQuest, Log, TEXT("Quest %s: finished instantly by quest.InstantFinish"), *GetNameSafe(this));
        return;
    }

    UE_LOG(LogQuest, Log, TEXT("Quest %s: starting end conditions: %d"),
        *GetNameSafe(this), QuestSettings->EndConditionsInst.Num());

    for (const UQuestCondition* ConditionTemplate : QuestSettings->EndConditionsInst)
    {
        if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
        {
            return;
        }
        UQuestCondition* QuestCondition = DuplicateObject<UQuestCondition>(ConditionTemplate, this);
        QuestCondition->StartCondition();
        QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
        EndConditions.Add(QuestCondition);
    }
}

void AQuest::UpdateEndStatus()
{
    if (QuestStatus != EQuestStatus::Started)
    {
        return;
    }

    for (UQuestCondition* Condition : EndConditions)
    {
        if (!ensure(Condition))
        {
            return;
        }
        if (!Condition->IsCompleted())
        {
            UE_LOG(LogQuest, Log, TEXT("Quest %s: end condition %s is not completed yet"),
                *GetNameSafe(this), *GetNameSafe(Condition));
            return;
        }
    }

    QuestStatus = EQuestStatus::Completed;
    UE_LOG(LogQuest, Log, TEXT("Quest %s: status changed to %s"),
        *GetNameSafe(this), *UEnum::GetValueAsString(QuestStatus));
}
