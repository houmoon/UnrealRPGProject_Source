#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "RPGProject/DataBase/UnitDB.h"

#include "RPGProject/Unit/Unit.h"
#include "UnitPlayer.generated.h"

class IInteractable;
class UBoxComponent;
class UDAInputAction;
class Item;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class RPGPROJECT_API AUnitPlayer : public AUnit
{
	GENERATED_BODY()

	public:
	static AUnitPlayer* CurrentPlayer;

	public: //Getters
	virtual FVector			GetLocalMoveDir() override;
	FPlayerData*		GetData();
	const float				GetSprintSpeed();
	const float				GetWalkSpeed();

	public: //Messeages
	virtual void			Attack() override;
	virtual void			Damage(int32 damage) override;
	void					AddItem(const int32 id);
	void					AddItem(Item* item);
	void					SetWeaponOverlap(bool boolean);
	void					SetInputMode(bool isGamemode);
	void					StartDialogue(AActor* otherActor, int32 id);
	void					OnEndDialogue();
	void					ChangeFOV(float targetFOV, float duration);

	class UPlayerModelComponent* GetModel() { return _playerModel; }


	private: //Attributes & Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent*		_camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent*	_springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class UPlayerModelComponent* _playerModel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* _interactionVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* _weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _dialogueCamera;

	UPROPERTY(EditAnywhere, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> _playerInputContext;

	UPROPERTY(EditAnywhere, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> _UIInputContext;

	UPROPERTY(EditAnywhere, Category = "Unit Player", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _attackMontage;

	UPROPERTY(EditAnywhere, Category = "Input Component (Player)", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UDAInputAction> _inputActionDataAsset;

	UEnhancedInputLocalPlayerSubsystem* _subsystem;

	IInteractable* _currentInteractable = nullptr;

	FTimerHandle _fovTransitionHandle;
	float tick;

	private: //Methods
	UFUNCTION()
	void					_onMovement(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onRotate(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onJump(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onSprint(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onAttack(const FInputActionValue& inputValue);

	//UI Callback

	UFUNCTION()
	void					_onInventory(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onEquip(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onQuest(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onInteract(const FInputActionValue& inputValue);

	//Dialogue Callback
	UFUNCTION()
	void					_onNext(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onSelection(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onTest(const FInputActionValue& inputValue);

	UFUNCTION()
	void					_onHit(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, FVector _normalImpulse, const FHitResult& _hitInfo);
	UFUNCTION()
	void					_onBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo);
	UFUNCTION()
	void					_onEndOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index);

	UFUNCTION()
	void					_onWeaponBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo);

	UFUNCTION()
	void					_onInteractableBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo);
	UFUNCTION()
	void					_onInteractableEndOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index);



	public:
	UPROPERTY(VisibleAnywhere)
	bool					IsAttacking;
	UPROPERTY(VisibleAnywhere)
	bool					IsNextCombo;

	protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	public:
	AUnitPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Quickslot Inputs
	UFUNCTION()
	void					_onQuickSlot0(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onQuickSlot1(const FInputActionValue& inputValue);
	UFUNCTION()
	void					_onQuickSlot2(const FInputActionValue& inputValue);

};
