// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
class AMyActor;


UCLASS()
class P20250519_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Right;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Left;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	TSubclassOf<AMyActor> RocketTemplete;

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	float BodyMoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	float BodyRotateSpeed;

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	float PropellerRotateSpeed;

	UPROPERTY(EditAnywhere, Category = "Datas", BlueprintReadWrite)
	float Boost;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void DoBoost();

	UFUNCTION()
	void UnBoost();

	UFUNCTION()
	void Roll(float AxisValue);

	UFUNCTION()
	void Pitch(float AxisValue);
};
