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
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
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

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(muzzleSound, mesh, TEXT("MuzzleFlashSocket"));

	FVector shotDirection;
	FHitResult result;
	bool bSuccess = GunTrace(result, shotDirection);

	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impactParticles, result.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), impactSound, result.Location);
		
		AActor* actor = result.GetActor();

		if(actor != nullptr)
		{
			FPointDamageEvent DamageEvent(damagePerShot, result, shotDirection, nullptr);
			actor->TakeDamage(damagePerShot, DamageEvent, GetOwnerController(), this);
		}
	}
}

bool AGun::GunTrace(FHitResult& hit, FVector& shotDirection)
{
	AController* ownerController = GetOwnerController();
	if(ownerController == nullptr) return false;

	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	ownerController->GetPlayerViewPoint(playerViewPointLocation, playerViewPointRotation);
	
	FVector endPoint = playerViewPointLocation + (playerViewPointRotation.Vector() * maxRange);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	shotDirection = -playerViewPointRotation.Vector();

	return GetWorld()->LineTraceSingleByChannel(hit, playerViewPointLocation, endPoint, ECollisionChannel::ECC_GameTraceChannel1, params);
}

AController* AGun::GetOwnerController() const
{
	APawn* owner = Cast<APawn>(GetOwner());
	if(owner == nullptr) return nullptr;

	return owner->GetController();
}