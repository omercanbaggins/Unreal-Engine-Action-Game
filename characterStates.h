#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterStates :uint8 {
	EUnequipped,
	EEquippedWithMelee,
	EEquippedWithRifle,
	EEquippedWithHandGun
};