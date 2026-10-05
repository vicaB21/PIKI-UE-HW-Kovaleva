// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"
#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
    AQuest* Quest = Cast<AQuest>(GetOuter());
    if (!Quest) return;

    if (TriggerPhase == EQuestTriggerPhase::OnEnter)
    {
        Quest->OnActorBeginOverlap.AddDynamic(
            this, &UTriggerVolume_QuestCondition::StartOverlap);
    }
    else
    {
        Quest->OnActorEndOverlap.AddDynamic(
            this, &UTriggerVolume_QuestCondition::EndOverlap);
    }
}

void UTriggerVolume_QuestCondition::StopCondition()
{
    AQuest* Quest = Cast<AQuest>(GetOuter());
    if (!Quest) return;

    Quest->OnActorBeginOverlap.RemoveDynamic(
        this, &UTriggerVolume_QuestCondition::StartOverlap);
    Quest->OnActorEndOverlap.RemoveDynamic(
        this, &UTriggerVolume_QuestCondition::EndOverlap);
}

void UTriggerVolume_QuestCondition::StartOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor->ActorHasTag(OtherTag))
    {
        Complete();
    }
}

void UTriggerVolume_QuestCondition::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor->ActorHasTag(OtherTag))
    {
        Complete();
    }
}
