#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Structs/ExWItemData.h"
#include "../../Utils/Enum/EnumUtils.h"
#include "../../Utils/Rarety/RarityUtils.h"
#include "StatSystem/Consts/DataTablesConst.h"
#include "StatSystem/Interfaces/ItemPickUpInterface.h"
#include "GameFramework/Character.h"
#include "ItemBase.generated.h"

UCLASS()
class STATSYSTEM_API AItemBase : public AActor
{
	GENERATED_BODY()

public: //Setup

	AItemBase();

	UFUNCTION()
	void SetupInitialAttributes();

protected: //Events
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public: //Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ExposeOnSpawn="true"), Replicated)
	FExWItemData ItemData;

public: //Functions

	UFUNCTION(BlueprintCallable)
	void PickUp(ACharacter* PlayerCharacter);

	UFUNCTION(Server, Reliable)
	void PickUpServer(ACharacter* PlayerCharacter);

	UFUNCTION(NetMulticast, Reliable)
	void PickUpNetMulticast(ACharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	void Drop(ACharacter* PlayerCharacter);

	UFUNCTION(Server, Reliable)
	void DropServer(ACharacter* PlayerCharacter);

	UFUNCTION(NetMulticast, Reliable)
	void DropNetMulticast(ACharacter* PlayerCharacter);
};
