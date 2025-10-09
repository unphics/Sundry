#include "Other/Stanford/MyCharacter.h"

#include "Other/3DMath/Vector.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Other/Stanford/InteractionComponent.h"
#include "Other/Stanford/MagicProjectile.h"
#include "Other/Stanford/MyAttributeComponent.h"

AMyCharacter::AMyCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	
	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	this->SpringArmComp->SetupAttachment(this->RootComponent);
	this->SpringArmComp->bUsePawnControlRotation = true;
	
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	this->CameraComp->SetupAttachment(this->SpringArmComp);

	this->bUseControllerRotationYaw = false;

	this->GetCharacterMovement()->bOrientRotationToMovement = true;

	this->InteractionComp = CreateDefaultSubobject<UInteractionComponent>("InteractionComp");

	this->AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");
}

void AMyCharacter::BeginPlay() {
	Super::BeginPlay();
	
}

void AMyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// 显示前向的箭头;后面可用作新手指引
	// const float DrawScale = 100.0f;
	// const float Thickness = 5.0f;
	// FVector LineStart = GetActorLocation();
	// LineStart += GetActorRightVector() * 100.f;
	// FVector ActorDir_LineEnd = LineStart + (GetActorForwardVector() * 100.f);
	// DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDir_LineEnd, DrawScale, FColor::Yellow, false, 0.f, 0, Thickness);
	// FVector ControllerDir_LineEnd = LineStart + (GetControlRotation().Vector() * 100.f);
	// DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDir_LineEnd, DrawScale, FColor::Green, false, 0.f, 0, Thickness);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward); // 此处必须是成员方法而且类型同第二个参数，无法使用lambda
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LoopUp", this, &AMyCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMyCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Keyboard_F", IE_Pressed, this, &AMyCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("SpaceBar",IE_Pressed, this, &AMyCharacter::Jump);
}

void AMyCharacter::MoveForward(float Value) {
	// 将仅采纳mesh的前向改为采纳
	// AddMovementInput(GetActorForwardVector(), Value, false);
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value, false);
}
void AMyCharacter::MoveRight(float Value) {
	// AddMovementInput(GetActorRightVector(), Value, false); // 修改了其他后这个现在是不对的
	
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y),Value); // 同GetRightVector
}

void AMyCharacter::PrimaryAttack() {
	PlayAnimMontage(this->AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMyCharacter::PirmaryAttack_TimeElapsed, 0.2f);
}

void AMyCharacter::PirmaryAttack_TimeElapsed() {
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(),HandLocation);
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;
	GetWorld()->SpawnActor<AActor>(this->ProjectileClass, SpawnTransform, SpawnParam);
}

void AMyCharacter::Jump() {
	Super::Jump();
}

void AMyCharacter::PrimaryInteract() {
	if (InteractionComp) {
		InteractionComp->PrimaryInteract();
	}
}

