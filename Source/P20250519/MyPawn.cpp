// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	Body->SetupAttachment(Box);


	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Right->SetStaticMesh(SM_Propeller.Object);
		Left->SetStaticMesh(SM_Propeller.Object);
	}
	Right->SetupAttachment(Body);
	Left->SetupAttachment(Body);

	Right->AddRelativeLocation(FVector(36.5f, 21.0f, 0.0f));
	Left->AddRelativeLocation(FVector(36.5f, -21.0f, 0.0f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Body);
	Arrow->AddRelativeLocation(FVector(40.0f, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Body);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDrawDebugLagMarkers = true;

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	BodyMoveSpeed = 1000.0f;
	BodyRotateSpeed = 180.0f;
	PropellerRotateSpeed = 7200.0f;
	Boost = 0.0f;

	Movement->MaxSpeed = BodyMoveSpeed;

	Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), Boost);

	Right->AddLocalRotation(FRotator(0, 0, PropellerRotateSpeed * DeltaTime));
	Left->AddLocalRotation(FRotator(0, 0, PropellerRotateSpeed * DeltaTime));


}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);

	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &AMyPawn::DoBoost);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &AMyPawn::UnBoost);

	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
}

void AMyPawn::Fire()
{
	//문법 : CDO 포인터를 가르침
	//의미 : 클래스 이름을 저장하고 싶다. 
	//RocketTemplete = AMyActor::StaticClass();
	GetWorld()->SpawnActor<AMyActor>(RocketTemplete, Arrow->K2_GetComponentToWorld());
}

void AMyPawn::DoBoost()
{
	Boost = 1.0f;
}

void AMyPawn::UnBoost()
{
	Boost = 0.5f;
}

void AMyPawn::Roll(float AxisValue)
{
	AddActorLocalRotation(FRotator(0, 0, 
		AxisValue * BodyRotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void AMyPawn::Pitch(float AxisValue)
{
	AddActorLocalRotation(FRotator(AxisValue * BodyRotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 
		0, 0));
}

