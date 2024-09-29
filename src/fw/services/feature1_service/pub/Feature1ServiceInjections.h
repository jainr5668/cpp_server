#pragma once
#include "IFeature1ServiceData.h"
#include "Utils.h"

class Feature1ServiceInjections
{
public:
    IFeature1ServiceData *feature1ServiceData_{nullptr};
    Utils* utils_{nullptr};
};