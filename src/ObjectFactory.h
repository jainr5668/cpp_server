#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <dlfcn.h>
#include <iostream>

// Base class for all objects
class Base {
public:
    virtual ~Base() = default;
};

// Factory function type
using CreateFunction = void* (*)();
using DestroyFunction = void (*)(void*);

// Factory class
class ObjectFactory {
public:
    std::unique_ptr<Base> createObject(const std::string& libraryName) {
        void* handle = dlopen(libraryName.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << std::endl;
            return nullptr;
        }

        dlerror(); // Reset errors

        CreateFunction create = (CreateFunction) dlsym(handle, "create");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol create: " << dlsym_error << std::endl;
            dlclose(handle);
            return nullptr;
        }

        void* instance = create();
        return std::unique_ptr<Base>(static_cast<Base*>(instance));
    }

    void destroyObject(void* instance, const std::string& libraryName) {
        void* handle = dlopen(libraryName.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << std::endl;
            return;
        }

        dlerror(); // Reset errors

        DestroyFunction destroy = (DestroyFunction) dlsym(handle, "destroy");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol destroy: " << dlsym_error << std::endl;
            dlclose(handle);
            return;
        }

        destroy(instance);
        dlclose(handle);
    }
};

#endif // OBJECTFACTORY_H