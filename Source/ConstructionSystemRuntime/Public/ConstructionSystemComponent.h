//$ Copyright 2015-19, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstructionSystemComponent.generated.h"

class UPrefabricatorAssetInterface;
class APrefabActor;
class UConstructionSystemCursor;
class UConstructionSystemTool;
class UMaterialInterface;
class UConstructionSystemUIAsset;

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class CONSTRUCTIONSYSTEMRUNTIME_API UConstructionSystemComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UConstructionSystemComponent();

	UFUNCTION(BlueprintCallable, Category = "ConstructionSystem")
	void ToggleConstructionSystem();

	//~ Begin UActorComponent Interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
	virtual void BeginPlay() override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~ End UActorComponent Interface

private:
	APlayerController* GetPlayerController();
	void TransitionCameraTo(AActor* InViewTarget, float InBlendTime, float InBlendExp);
	void HandleUpdate();
	void BindInput();

	void ToggleBuildUI();
	void EnableConstructionSystem();
	void DisableConstructionSystem();
	void CreateTool(TSubclassOf<UConstructionSystemTool> InToolClass);

	UFUNCTION()
	void CreateTool_Build();

	UFUNCTION()
	void CreateTool_Remove();

	void CreateBuildMenu();
	void ShowBuildMenu();
	void HideBuildMenu();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorInvalidMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AActor* ConstructionCameraActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ConstructionCameraTransitionTime = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ConstructionCameraTransitionExp = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BuildMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UConstructionSystemUIAsset* BuildMenuData;

	UPROPERTY(Transient)
	UUserWidget* BuildMenuUIInstance;

	UPROPERTY(Transient, Replicated, BlueprintReadOnly, Category = "ConstructionSystem")
	UConstructionSystemTool* ActiveTool;

private:
	bool bConstructionSystemEnabled = false;
	bool bInputBound = false;
};