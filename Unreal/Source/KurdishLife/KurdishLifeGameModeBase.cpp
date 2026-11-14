#include "KurdishLifeGameModeBase.h"
#include "KurdishLifeCharacter.h"

AKurdishLifeGameModeBase::AKurdishLifeGameModeBase()
{
    DefaultPawnClass = AKurdishLifeCharacter::StaticClass();
}
