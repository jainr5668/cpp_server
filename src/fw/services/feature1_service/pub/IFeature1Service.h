#pragma once

#include "feature1_service_types.h"


class IFeature1Service
{
public:
    IFeature1Service() = default;
    ~IFeature1Service() = default;
    virtual Person* processRequest1(Person*) = 0;
    
};