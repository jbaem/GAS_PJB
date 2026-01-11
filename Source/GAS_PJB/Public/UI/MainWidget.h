#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainWidget.generated.h"

UCLASS()
class GAS_PJB_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	class UMainBarWidget* GetMainBarWidget() const { return MainBarWidget; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMainBarWidget> MainBarWidget = nullptr;
};
