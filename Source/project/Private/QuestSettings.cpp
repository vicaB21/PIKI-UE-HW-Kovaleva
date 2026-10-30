#include "QuestSettings.h"

#include "QuestCondition.h"

void UQuestSettings::PostLoad()
{
    Super::PostLoad();

    if (!StartConditions_DEPRECATED.IsEmpty())
    {
        for (const TSubclassOf<UQuestCondition>& ConditionTemplate : StartConditions_DEPRECATED)
        {
            if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
            {
                return;
            }
            UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
            StartConditionsInst.Add(QuestCondition);
        }
        UE_LOG(LogQuest, Log, TEXT("Settings %s: migrated %d start conditions"),
            *GetNameSafe(this), StartConditions_DEPRECATED.Num());
        StartConditions_DEPRECATED.Empty();
    }

    if (!EndConditions_DEPRECATED.IsEmpty())
    {
        for (const TSubclassOf<UQuestCondition>& ConditionTemplate : EndConditions_DEPRECATED)
        {
            if (!ensureMsgf(ConditionTemplate, TEXT("Bad setup for quest %s"), *GetNameSafe(this)))
            {
                return;
            }
            UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
            EndConditionsInst.Add(QuestCondition);
        }
        UE_LOG(LogQuest, Log, TEXT("Settings %s: migrated %d end conditions"),
            *GetNameSafe(this), EndConditions_DEPRECATED.Num());
        EndConditions_DEPRECATED.Empty();
    }
}
