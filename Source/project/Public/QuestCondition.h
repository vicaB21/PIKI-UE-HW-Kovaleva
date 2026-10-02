// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestCondition.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UQuestCondition : public UObject
{
	GENERATED_BODY()
public:
  virtual void StartCondition() PURE_VIRTUAL(StartCondition, );
  virtual void StopCondition() PURE_VIRTUAL(StopCondition, );
protected:
  UPROPERTY(BlueprintReadOnly)
  bool bCompleted = false;
};
