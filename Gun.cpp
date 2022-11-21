// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult OutHitResult;
	FVector ShotDirection;
	bool hasHit = GunTrace(OutHitResult, ShotDirection);

	if (hasHit) {
		//DrawDebugPoint(GetWorld(), OutHitResult.ImpactPoint, 20, FColor::Red, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHitResult.ImpactPoint, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHitResult.ImpactPoint);
		AActor* DamagedActor = OutHitResult.GetActor();
		if (DamagedActor) {
			FPointDamageEvent DamageEvent(Damage, OutHitResult, ShotDirection, nullptr);
			AController* OwnerController = AGun::GetOwnerController();
			DamagedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& OutHitResult, FVector& ShotDirection)
{
	AController* OwnerController = AGun::GetOwnerController();

	if (OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	FVector End = Location + Rotation.Vector() * MaxRange;

	//DrawDebugPoint(GetWorld(), Location, 20, FColor::Red, true);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Location, End,  ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

