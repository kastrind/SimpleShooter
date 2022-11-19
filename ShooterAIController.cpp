#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}

}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	 if (LineOfSightTo(PlayerPawn)) {
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}else {
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}

	// Replaced by Behavior Tree
	// if (LineOfSightTo(PlayerPawn)) {
	// 	SetFocus(PlayerPawn);
	// 	MoveToActor(PlayerPawn, AcceptanceRadius);	
	// }else {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
	}

}
