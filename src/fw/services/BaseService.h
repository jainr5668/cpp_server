#pragma once
#include <string>

using ModuleUid = uint32_t;

template <typename T>
inline ModuleUid getModuleUid();

#define DEFINE_MODULE_UID(cf, uid) \
    template <>                    \
    inline ModuleUid getModuleUid<::cf>() { return uid; }

#define GET_MODULE_UID(cf) getModuleUid<cf>()

class BaseService
{
public:
    virtual void initialize() = 0;
    virtual void *getInterface(ModuleUid uid) = 0;
    virtual void setInterface(ModuleUid uid, void *interface) = 0;
    virtual void connect() = 0;
    virtual void *getInstance() = 0;
    virtual void shutdown() = 0;
    virtual ModuleUid getInterfaceUID() = 0;
    virtual ~BaseService() = default;
};
