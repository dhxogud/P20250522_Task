// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_Rocket.SM_Rocket'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	Body->SetupAttachment(Box);
	Body->AddLocalRotation(FRotator(-90.0f, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	MoveSpeed = 2000.0f;

	Movement->InitialSpeed = MoveSpeed;
	Movement->MaxSpeed = MoveSpeed;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor,
		100.0f,
		nullptr,
		this,
		UDamageType::StaticClass()
	);

	//상속된 블루프린트에 무슨 함수 있을꺼야. 그걸 기획자가 만들면 난 그걸 알아서 호출께
	//CallCPPToExecuteBP(100);
	// 
	CallCPPToDefaultExecuteBP(100);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	Destroy();
}

void AMyActor::CallCPPToDefaultExecuteBP_Implementation(float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("이건 Cpp에서 호출한거임"));
}

