#include "UnitPlayer.h"
#include "EngineMinimal.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Kismet/KismetMathLibrary.h>

#include "PlayerModelComponent.h"
#include "RPGProject/Effect/EffectManager.h"
#include "RPGProject/Gamemode/Gamemode_Ingame.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Input/DAInputAction.h"
#include "RPGProject/Interfaces/Interactable.h"
#include "RPGProject/UMG/WD_DialoguePanel.h"
#include "RPGProject/UMG/WD_IngameHUD.h"
#include "RPGProject/UMG/WD_Inventory.h"
#include "RPGProject/UMG/WD_QuestPanel.h"
#include "RPGProject/UMG/WD_StatusPanel.h"

AUnitPlayer* AUnitPlayer::CurrentPlayer = nullptr;

FVector AUnitPlayer::GetLocalMoveDir()
{
	return FVector();
}

FPlayerData* AUnitPlayer::GetData()
{
	return _playerModel->GetData();
}

const float AUnitPlayer::GetSprintSpeed()
{
	return _playerModel->GetData()->SprintSpeed;
}

const float AUnitPlayer::GetWalkSpeed()
{
	return _playerModel->GetData()->MoveSpeed;
}

void AUnitPlayer::Attack()
{
	
}

void AUnitPlayer::Damage(int32 damage)
{
	EffectManager::GetInstance()->CreateEffect(EEFECT_TYPE::HIT_PUNCH_0,GetLevel(),GetActorLocation());

	displayDamage(damage, UPlayerModelComponent::damageColor);
	_playerModel->Damage(damage);
}

void AUnitPlayer::AddItem(const int32 id)
{
	_playerModel->AddItem(id);
}

void AUnitPlayer::AddItem(Item* item)
{
	_playerModel->AddItem(item);
}

void AUnitPlayer::SetWeaponOverlap(bool boolean)
{
	if(boolean)
	{
		_weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
	}
	else
	{
		_weapon->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void AUnitPlayer::SetInputMode(bool isGamemode)
{
	APlayerController* pController = Cast<APlayerController>(GetController());

	if(nullptr != pController && nullptr != _subsystem)
	{
		if (isGamemode)
		{
			if(!_subsystem->HasMappingContext(_playerInputContext.LoadSynchronous()))
				_subsystem->AddMappingContext(_playerInputContext.LoadSynchronous(),0);

			pController->bShowMouseCursor = false;

			/*
			pController->SetInputMode(FInputModeGameOnly());
			*/
		}
		else
		{
			if (_subsystem->HasMappingContext(_playerInputContext.LoadSynchronous()))
				_subsystem->RemoveMappingContext(_playerInputContext.LoadSynchronous());

			/*
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(UWD_IngameMain::CurrentWidget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			pController->SetInputMode(InputModeData);
			*/

			pController->bShowMouseCursor = true;
		}
	}

}

void AUnitPlayer::StartDialogue(AActor* otherActor, int32 id)
{
	if(_currentInteractable)
	{
		_currentInteractable->OnExitOverlap();
		_currentInteractable = nullptr;
	}

	UWD_IngameMain* currentMain = UWD_IngameMain::CurrentWidget;
	if(currentMain)
		currentMain->SetWidgetIndex(0);

	//카메라를 전환한다.
	APlayerController* playerController = GetLocalViewingPlayerController();

	playerController->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, 0.25f, FLinearColor::Black, false, true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this, playerController,otherActor,id, currentMain]()
	{
		//플레이어를 대상으로 이동시킨다.
		SetActorLocation(otherActor->GetActorLocation() + (otherActor->GetActorForwardVector() * 200.f));
		SetActorRotation(otherActor->GetActorRotation() + FRotator(0, 180, 0));

		// CameraA 비활성화, CameraB 활성화
		_camera->Deactivate();
		_dialogueCamera->Activate();


		UWD_IngameMain* ingameMain = UWD_IngameMain::CurrentWidget;
		if (nullptr == ingameMain)
		{
			return;
		}

		UWD_DialoguePanel* dialoguePanel = ingameMain->GetDialoguePanel();
		dialoguePanel->EnQueueDialogue(id);

		SetInputMode(false);

		if (currentMain)
			currentMain->SetWidgetIndex(2);


		// 카메라 페이드 인 시작
		GetLocalViewingPlayerController()->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 0.25f, FLinearColor::Black, false, true);
	}, 0.25f, false);

}

void AUnitPlayer::OnEndDialogue()
{
	UWD_IngameMain* currentMain = UWD_IngameMain::CurrentWidget;
	if (currentMain)
		currentMain->SetWidgetIndex(0);

	//카메라를 전환한다.
	APlayerController* playerController = GetLocalViewingPlayerController();

	playerController->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, 0.25f, FLinearColor::Black,false,true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this, playerController, currentMain]()
	{
		_dialogueCamera->Deactivate();
		_camera->Activate();

		if (currentMain)
			currentMain->SetWidgetIndex(1);

		SetInputMode(true);

		// 카메라 페이드 인 시작
		GetLocalViewingPlayerController()->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 0.25f, FLinearColor::Black, false, true);
	}, 0.25f, false);

}

void AUnitPlayer::ChangeFOV(float targetFov, float duration)
{

}

void AUnitPlayer::_onMovement(const FInputActionValue& inputValue)
{
	const FVector2D MovementVector = inputValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();

	FRotator RightVectorParam(0, ControlRot.Yaw, ControlRot.Roll);
	FRotator ForwardVectorParam(0, ControlRot.Yaw, 0);

	FVector RightVector = UKismetMathLibrary::GetRightVector(RightVectorParam);
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ForwardVectorParam);


	AddMovementInput(RightVector, MovementVector.X);
	AddMovementInput(ForwardVector, MovementVector.Y);
}

void AUnitPlayer::_onRotate(const FInputActionValue& inputValue)
{
	const FVector RotationVector = inputValue.Get<FVector>();

	AddControllerPitchInput(-RotationVector.Y);
	AddControllerYawInput(RotationVector.X);
}

void AUnitPlayer::_onJump(const FInputActionValue& inputValue)
{
	Super::Jump();
	//GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity + FVector::UpVector * 100.f;
}

void AUnitPlayer::_onSprint(const FInputActionValue& inputValue)
{
	bool isSprinting = inputValue.Get<bool>();
	if(isSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = _playerModel->GetData()->SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = _playerModel->GetData()->MoveSpeed;
	}
		
}

void AUnitPlayer::_onAttack(const FInputActionValue& inputValue)
{
	if (IsAttacking)
	{
		IsNextCombo = true;
	}
	else
	{
		IsAttacking = true;
		if(_attackMontage)
			GetMesh()->GetAnimInstance()->Montage_Play(_attackMontage,1.15f);
	}
}

void AUnitPlayer::_onInventory(const FInputActionValue& inputValue)
{
	// 게임모드로 부터 메인 HUD 가져오기
	UWD_IngameHUD* ingameHUD = UWD_IngameHUD::CurrentWidget;

	if (ingameHUD)
		ingameHUD->GetInventory()->TogglePanel();
		
}

void AUnitPlayer::_onEquip(const FInputActionValue& inputValue)
{
	// 게임모드로 부터 메인 HUD 가져오기
	UWD_IngameHUD* ingameHUD = UWD_IngameHUD::CurrentWidget;

	if (ingameHUD)
		ingameHUD->GetStatus()->TogglePanel();
}

void AUnitPlayer::_onQuest(const FInputActionValue& inputValue)
{
	// 게임모드로 부터 메인 HUD 가져오기
	UWD_IngameHUD* ingameHUD = UWD_IngameHUD::CurrentWidget;
	if (ingameHUD)
		ingameHUD->GetQuestPanel()->TogglePanel();
}

void AUnitPlayer::_onInteract(const FInputActionValue& inputValue)
{
	if (_currentInteractable)
	{
		_currentInteractable->OnInteract();
	}
}

void AUnitPlayer::_onNext(const FInputActionValue& inputValue)
{

	UWD_IngameMain* ingameMain = UWD_IngameMain::CurrentWidget;
	if (nullptr == ingameMain)
		return;

	UWD_DialoguePanel* dialoguePanel = ingameMain->GetDialoguePanel();
	dialoguePanel->DequeueDialogue();

}

void AUnitPlayer::_onSelection(const FInputActionValue& inputValue)
{
	
}

void AUnitPlayer::_onTest(const FInputActionValue& inputValue)
{
	SetInputMode(true);
}

void AUnitPlayer::_onHit(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, FVector _normalImpulse, const FHitResult& _hitInfo)
{
}

void AUnitPlayer::_onBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo)
{
}

void AUnitPlayer::_onEndOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index)
{
}

void AUnitPlayer::_onWeaponBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo)
{
	AUnit* unit = Cast<AUnit>(_otherActor);

	if(IsValid(unit))
	{
		unit->Damage(GetModel()->GetDamage());
		EffectManager::GetInstance()->CreateEffect(EEFECT_TYPE::HIT_PUNCH_0, GetLevel(), _otherActor->GetActorLocation());
	}


}

void AUnitPlayer::_onInteractableBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor,
	UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo)
{
	auto interactable = Cast<IInteractable>(_otherActor);
	if(interactable)
	{
		if (_currentInteractable == nullptr)
		{
			_currentInteractable = interactable;
			_currentInteractable->OnEnterOverlap();
		}		
	}


}

void AUnitPlayer::_onInteractableEndOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor,
	UPrimitiveComponent* _otherPrimitiveComp, int32 _index)
{
	auto interactable = Cast<IInteractable>(_otherActor);
	if (interactable)
	{
		if (_currentInteractable == interactable)
		{
			_currentInteractable->OnEnterOverlap();
			_currentInteractable = nullptr;
		}

		interactable->OnExitOverlap();
	}



}


AUnitPlayer::AUnitPlayer() : IsAttacking(false)
{
	//Tick 활성화
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트 생성
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_playerModel = CreateDefaultSubobject<UPlayerModelComponent>(TEXT("Player Model"));
	_weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	_interactionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Volume"));

	_dialogueCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Dialogue Camera"));
	_dialogueCamera->Deactivate();

	_interactionVolume->SetCollisionProfileName(TEXT("PlayerInteraction"));

	_interactionVolume->SetupAttachment(GetCapsuleComponent());
	_dialogueCamera->SetupAttachment(GetCapsuleComponent());
	_springArm->SetupAttachment(RootComponent);
	_camera->SetupAttachment(_springArm);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> _skeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Game/Models/Thief/SK_Thief.SK_Thief'"));

	if (_skeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(_skeletalMeshAsset.Object);
		_weapon->SetupAttachment(GetMesh(), TEXT("Socket_WeaponR"));
	}
	
	
}

void AUnitPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CurrentPlayer != nullptr)
		CurrentPlayer = nullptr;

	CurrentPlayer = this;
}

void AUnitPlayer::BeginPlay()
{
	Super::BeginPlay();



	//모델 데이터 초기화
	_playerModel->Init(GetMesh()->GetWorld());
	GetCharacterMovement()->MaxWalkSpeed = _playerModel->GetData()->MoveSpeed;

	//충돌 델리게이트 콜백 추가
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AUnitPlayer::_onHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUnitPlayer::_onBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AUnitPlayer::_onEndOverlap);

	_interactionVolume->OnComponentBeginOverlap.AddDynamic(this,&AUnitPlayer::_onInteractableBeginOverlap);
	_interactionVolume->OnComponentEndOverlap.AddDynamic(this, &AUnitPlayer::_onInteractableEndOverlap);

	_weapon->OnComponentBeginOverlap.AddDynamic(this, &AUnitPlayer::_onWeaponBeginOverlap);
	SetWeaponOverlap(false);


	//플레이어컨트롤러 연결
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		ULocalPlayer* pLocalPlayer = PlayerController->GetLocalPlayer();

		if (pLocalPlayer)
		{
			_subsystem = pLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

			_subsystem->AddMappingContext(_playerInputContext.LoadSynchronous(), 0);

			_subsystem->AddMappingContext(_UIInputContext.LoadSynchronous(), 0);

		}
	}

	GetModel()->AcceptQuest(1);
}

void AUnitPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (!_inputActionDataAsset.IsNull())
		{
			UDAInputAction* _dataAsset = _inputActionDataAsset.LoadSynchronous();

			for (int32 i = 0; i < _dataAsset->PlayerInputDatas.Num(); i++)
			{
				switch (_dataAsset->PlayerInputDatas[i].Type)
				{
					//플레이어 입력 연동
					case EINPUT_TYPE_PLAYER::MOVE:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onMovement);
						break;
					case EINPUT_TYPE_PLAYER::ROTATE:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onRotate);
						break;
					case EINPUT_TYPE_PLAYER::JUMP:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onJump);
						break;
					case EINPUT_TYPE_PLAYER::SPRINT:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onSprint);
						break;
					case EINPUT_TYPE_PLAYER::ATTACK:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onAttack);
						break;
					case EINPUT_TYPE_PLAYER::QUICKSLOT0:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onQuickSlot0);
						break;
					case EINPUT_TYPE_PLAYER::QUICKSLOT1:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onQuickSlot1);
						break;
					case EINPUT_TYPE_PLAYER::QUICKSLOT2:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onQuickSlot2);
						break;
					case EINPUT_TYPE_PLAYER::INTERACT:
						enhancedInputComponent->BindAction(_dataAsset->PlayerInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onInteract);
						break;

					case EINPUT_TYPE_PLAYER::QUICKSLOT3:
					case EINPUT_TYPE_PLAYER::QUICKSLOT4:
					case EINPUT_TYPE_PLAYER::QUICKSLOT5:
					case EINPUT_TYPE_PLAYER::QUICKSLOT6:
					

					break;

				}
			}

			for (int32 i = 0; i < _dataAsset->UIInputDatas.Num(); i++)
			{
				switch (_dataAsset->UIInputDatas[i].Type)
				{
					case EINPUT_TYPE_UI::INVENTORY:
						enhancedInputComponent->BindAction(_dataAsset->UIInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onInventory);
						break;
					case EINPUT_TYPE_UI::STATUS:
						enhancedInputComponent->BindAction(_dataAsset->UIInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onEquip);
						break;
					case EINPUT_TYPE_UI::QUEST:
						enhancedInputComponent->BindAction(_dataAsset->UIInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onQuest);
						break;
					case EINPUT_TYPE_UI::NEXT:
						enhancedInputComponent->BindAction(_dataAsset->UIInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onNext);
						break;
					case EINPUT_TYPE_UI::MENU:
						enhancedInputComponent->BindAction(_dataAsset->UIInputDatas[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &AUnitPlayer::_onTest);
						break;
				}
			}
		}


	}
}

void AUnitPlayer::_onQuickSlot0(const FInputActionValue& inputValue)
{
	GetModel()->UseQuickSlotItem(0);
}

void AUnitPlayer::_onQuickSlot1(const FInputActionValue& inputValue)
{
	GetModel()->UseQuickSlotItem(1);
}

void AUnitPlayer::_onQuickSlot2(const FInputActionValue& inputValue)
{
	GetModel()->UseQuickSlotItem(2);
}

void AUnitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tick = DeltaTime;

}
