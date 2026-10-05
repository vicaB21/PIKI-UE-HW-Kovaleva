#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "TestQuestCondition.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECT_API UTestQuestCondition : public UQuestCondition
{
    GENERATED_BODY()
public:
    virtual void StartCondition() override {}
    virtual void StopCondition() override {}
};
