#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatSystem/Actors/Items/ItemBase.h"
#include "StatSystem/Interfaces/ItemPickUpInterface.h"
#include "StatSystem/Structs/ExWAttribute.h"
#include "StatSystem/Structs/ExWAttributeTypeEffectOnStatType.h"
#include "StatSystem/Structs/ExWStat.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributesAndStatsChanged);


UCLASS()
class ABaseCharacter : public ACharacter, public IItemPickUpInterface
{
	GENERATED_BODY()


public: //Setup
	ABaseCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public: //Interfaces

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PickUpItem(AActor* Item);
	virtual void PickUpItem_Implementation(AActor* Item) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DropItem(AActor* Item);
	virtual void DropItem_Implementation(AActor* Item) override;


protected: //Input

	void OnResetVR();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public: //Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public: //Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	TArray<FExWAttribute> Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	TArray<FExWStat> Stats;


public: //Functions

	void ApplyItemDataAttributesToStats(AItemBase* ItemBase);

	void SubtractItemDataAttributesToStats(AItemBase* ItemBase);

public: //Utils

	void CreateDefaultAttributes();
	void CreateDefaultStats();

	TArray<FExWAttributeTypeEffectOnStatType> GetAttributeEffectorList();

public: //Events

	UPROPERTY(BlueprintAssignable)
	FOnAttributesAndStatsChanged OnAttributesAndStatsChanged;
};
