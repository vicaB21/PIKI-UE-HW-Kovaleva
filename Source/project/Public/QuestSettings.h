#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestSettings.generated.h"

class UQuestCondition;

UCLASS()
class PRACTICE_API UQuestSettings : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Name;

    UPROPERTY(Instanced, EditAnywhere)
    TArray<TObjectPtr<UQuestCondition>> StartConditionsInst;

    UPROPERTY()
    TArray<TSubclassOf<UQuestCondition>> StartConditions_DEPRECATED;

    UPROPERTY(Instanced, EditAnywhere)
    TArray<TObjectPtr<UQuestCondition>> EndConditionsInst;

    UPROPERTY()
    TArray<TSubclassOf<UQuestCondition>> EndConditions_DEPRECATED;

    virtual void PostLoad() override;
};
