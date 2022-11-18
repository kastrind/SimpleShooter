#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LineOfSightTo(PlayerPawn)) {
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, AcceptanceRadius);	
	}else {
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}

	// if (PlayerPawn) {

	// 	FVector Location;
	// 	FRotator Rotation;
	
	// 	GetPlayerViewPoint(Location, Rotation);

	// 	float Distance = FVector::Dist(Location, PlayerPawn->GetActorLocation());

	// 	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);

	// 	if (Distance <= FocusDistance) {
	// 		SetFocus(PlayerPawn);
	// 	}else {
	// 		ClearFocus(EAIFocusPriority::Gameplay);
	// 	}

	// }
}
