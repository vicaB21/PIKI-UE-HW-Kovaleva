#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "TestQuestCondition.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class PRACTICE_API UTestQuestCondition : public UQuestCondition
{
    GENERATED_BODY()
public:
    virtual void StartCondition() override {}
    virtual void StopCondition() override {}
};
