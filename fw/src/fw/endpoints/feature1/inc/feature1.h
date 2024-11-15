#ifndef HANDLER1_H
#define HANDLER1_H
#include <string>
#include "logger.h"
#include "Ifeature1.h"
#include "IServer.h"
#include "server.h"
#include "feature1_service.h"
#include "Feature1ServiceData.h"

class Feature1 : public IFeature1
{
public:
    Feature1();
    ~Feature1() = default;

private:
    Logger logger;
    Feature1Service *featire1Service_;
    Feature1ServiceInjections* feature1ServiceInjections;
};
#endif // HANDLER1_H