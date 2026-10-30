#include "QuestSystemComponent.h"

#include "EngineUtils.h"
#include "Quest.h"
#include "QuestCondition.h"

UQuestSystemComponent::UQuestSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UQuestSystemComponent::BeginPlay()
{
    Super::BeginPlay();

    for (const TSubclassOf<AQuest>& QuestClass : Quests)
    {
        AQuest* Quest = GetWorld()->SpawnActor<AQuest>(QuestClass);
        if (Quest)
        {
            UE_LOG(LogQuest, Log, TEXT("Quest system: spawned quest %s"), *GetNameSafe(Quest));
        }
        else
        {
            UE_LOG(LogQuest, Warning, TEXT("Quest system: failed to spawn quest from class %s"),
                *GetNameSafe(QuestClass));
        }
    }
}

void UQuestSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestSystemComponent::GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests)
{
    for (AQuest* Quest : ActiveQuests)
    {
        if (Quest->GetQuestStatus() == EQuestStatus::Started)
        {
            OutQuests.Add(Quest);
        }
    }
}

void UQuestSystemComponent::RegisterQuest(AQuest* NewQuest)
{
    ActiveQuests.AddUnique(NewQuest);
    UE_LOG(LogQuest, Log, TEXT("Quest system: registered quest %s, active quests: %d"),
        *GetNameSafe(NewQuest), ActiveQuests.Num());
}
