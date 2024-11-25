#ifndef BASESERVICE_H
#define BASESERVICE_H
#include <string>
#include <map>
#include <regex>

using ModuleUid = std::string;

template <typename T>
inline ModuleUid getModuleUid();

static std::map<std::string, ModuleUid> moduleUidMap;

#ifndef UNIQUE_ID
#define UNIQUE_ID_IMPL(line, counter) _unique_id_##line##_##counter
#define UNIQUE_ID(line, counter) UNIQUE_ID_IMPL(line, counter)
#define UNIQUE_VAR UNIQUE_ID(__LINE__, __COUNTER__)
#endif


#define DEFINE_MODULE_UID(cf, uid) \
    template <>                    \
    inline ModuleUid getModuleUid<::cf>() { return uid; } \
    SET_MODULE_UID(#cf, uid)

#define SET_MODULE_UID(str, uid) \
namespace { \
        const auto UNIQUE_VAR = moduleUidMap[str] = uid; \
    }

#define GET_MODULE_UID_STR(str) (moduleUidMap.find(str) != moduleUidMap.end() ? moduleUidMap[str] : "")

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

#endif // BASESERVICE_H