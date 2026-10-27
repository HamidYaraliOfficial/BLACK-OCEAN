// BLACK OCEAN - Primary Module Header
#pragma once
#include "Modules/ModuleManager.h"

class FBlackOceanModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
