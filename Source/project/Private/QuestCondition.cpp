#include "QuestCondition.h"

DEFINE_LOG_CATEGORY(LogQuest)

void UQuestCondition::Complete()
{
    bCompleted = true;
    UE_LOG(LogQuest, Log, TEXT("Condition %s completed"), *GetNameSafe(this));
    OnQuestConditionCompleted.Broadcast();
}
