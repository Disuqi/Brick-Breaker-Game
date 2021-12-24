// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Paddle.h"
#include "Ball.h"

APaddle_Controller::APaddle_Controller()
{
}

void APaddle_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveHorizontal", this, &APaddle_Controller::MoveHorizontal);
	InputComponent->BindAction("Launch",IE_Pressed, this, &APaddle_Controller::Launch);



}

void APaddle_Controller::BeginPlay()
{
	MyPaddle = Cast<APaddle>(GetPawn());
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	
	FViewTargetTransitionParams Params;

	SetViewTarget(CameraActors[0], Params);

	SpawnNewBall();


}

void APaddle_Controller::MoveHorizontal(float AxisValue)
{

	if (MyPaddle != nullptr) {
		MyPaddle->MoveHorizontal(AxisValue);
	}
}

void APaddle_Controller::Launch()
{
	MyBall->Launch();
}

void APaddle_Controller::SpawnNewBall()
{
	if (!MyBall)
		MyBall = nullptr;

	if (BallObj) {
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, SpawnLocation, SpawnRotation, SpawnInfo);
	}
}
