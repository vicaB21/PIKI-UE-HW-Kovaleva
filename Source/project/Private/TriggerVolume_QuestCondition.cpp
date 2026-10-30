#include "TriggerVolume_QuestCondition.h"

#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
    AQuest* Quest = Cast<AQuest>(GetOuter());
    if (!Quest)
    {
        UE_LOG(LogQuest, Warning, TEXT("TriggerVolume condition %s: outer is not a quest"), *GetNameSafe(this));
        return;
    }

    if (TriggerPhase == EQuestTriggerPhase::OnEnter)
    {
        Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::StartOverlap);
    }
    else
    {
        Quest->OnActorEndOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::EndOverlap);
    }

    UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition started: quest %s, phase %s, tag %s"),
        *Quest->GetName(), *UEnum::GetValueAsString(TriggerPhase), *OtherTag.ToString());
}

void UTriggerVolume_QuestCondition::StopCondition()
{
    AQuest* Quest = Cast<AQuest>(GetOuter());
    if (!Quest)
    {
        return;
    }

    Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::StartOverlap);
    Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolume_QuestCondition::EndOverlap);

    UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition stopped: quest %s"), *Quest->GetName());
}

void UTriggerVolume_QuestCondition::StartOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    HandleOverlap(OtherActor, TEXT("begin overlap"));
}

void UTriggerVolume_QuestCondition::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    HandleOverlap(OtherActor, TEXT("end overlap"));
}

void UTriggerVolume_QuestCondition::HandleOverlap(AActor* OtherActor, const TCHAR* EventName)
{
    if (!OtherActor)
    {
        return;
    }

    const bool bHasTag = OtherActor->ActorHasTag(OtherTag);
    UE_LOG(LogQuest, Log, TEXT("TriggerVolume condition: %s with actor %s, %s"),
        EventName, *OtherActor->GetName(), bHasTag ? TEXT("has tag") : TEXT("no tag"));

    if (bHasTag)
    {
        Complete();
    }
}
