#pragma once

// Includes
// -------------------------------------

// Engine
#include "Misc/TypeContainer.h"

/**
 * 
 */
class FJooballinServicesModule final : public IModuleInterface
{
public:
    static JOOBALLINSERVICES_API TTypeContainer<>& GetTypeContainer();

protected:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    static TTypeContainer<> TypeContainer;
};
