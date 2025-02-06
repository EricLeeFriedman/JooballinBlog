// License Copyright (c) 2025 Eric Friedman

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
    //~ Begin IModuleInterface Interface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    //~ End IModuleInterface Interface

private:
    static TTypeContainer<> TypeContainer;
};

template <class T>
TSharedRef<T> GetService()
{
    return FJooballinServicesModule::GetTypeContainer().GetInstance<T>();
}
