#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceBar.generated.h"

UINTERFACE(MinimalAPI)
class UResourceBar : public UInterface
{
	GENERATED_BODY()
};

class GAS_PJB_API IResourceBar
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ResourceBar")
	void UpdateCurrent(float Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ResourceBar")
	void UpdateMax(float Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ResourceBar")
	void UpdateAll (float Current, float Max);
};
