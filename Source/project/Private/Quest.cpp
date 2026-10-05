// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest.h"

#include "QuestSettings.h"
#include "QuestCondition.h"
#include "QuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"

AQuest::AQuest()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AQuest::BeginPlay()
{
    Super::BeginPlay();
    if (UQuestSystemComponent* QuestComponent = GetWorld()->GetAuthGameMode()->GetComponentByClass<UQuestSystemComponent>())
    {
        QuestComponent->RegisterQuest(this);
    }
    for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->StartConditions)
    {
        if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
        {
            return;
        }
        UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
        QuestCondition->StartCondition();
        QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
        StartConditions.Add(QuestCondition);
    }
}

void AQuest::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AQuest::SetQuestStatus(EQuestStatus NewStatus)
{
    if (QuestStatus == NewStatus)
    {
        return;
    }
    QuestStatus = NewStatus;
    OnQuestStatusChanged.Broadcast(this, NewStatus);
}

void AQuest::UpdateStartStatus()
{
    for (UQuestCondition* Condition : StartConditions)
    {
        if (!ensure(Condition))
        {
            return;
        }
        if (!Condition->IsCompleted())
        {
            return;
        }
    }

    SetQuestStatus(EQuestStatus::Started);

    for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->EndConditions)
    {
        if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
        {
            return;
        }
        UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
        QuestCondition->StartCondition();
        QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
        EndConditions.Add(QuestCondition);
    }
}

void AQuest::UpdateEndStatus()
{
    for (UQuestCondition* Condition : EndConditions)
    {
        if (!ensure(Condition))
        {
            return;
        }
        if (!Condition->IsCompleted())
        {
            return;
        }
    }

    SetQuestStatus(EQuestStatus::Completed);
}
