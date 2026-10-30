#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystemComponent.generated.h"

class AQuest;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PRACTICE_API UQuestSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestSystemComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests);

    void RegisterQuest(AQuest* NewQuest);

protected:
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<AQuest>> Quests;

    UPROPERTY()
    TArray<AQuest*> ActiveQuests;
};
