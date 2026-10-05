// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "TriggerVolume_QuestCondition.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EQuestTriggerPhase : uint8
{
    OnEnter UMETA(DisplayName = "On Enter"),
    OnExit  UMETA(DisplayName = "On Exit")
};

UCLASS()
class PROJECT_API UTriggerVolume_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()
public:
    virtual void StartCondition() override;
    virtual void StopCondition() override;

    UFUNCTION()
    void StartOverlap(AActor* OverlappedActor, AActor* OtherActor);
    
    UFUNCTION()
    void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);
    
    UPROPERTY(EditAnywhere)
    FName OtherTag;
    
    UPROPERTY(EditAnywhere, Category = "Quest")
    EQuestTriggerPhase TriggerPhase = EQuestTriggerPhase::OnEnter;
};
