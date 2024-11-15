#pragma once
#include "IFeature1ServiceData.h"
#include "Data.h"

class Feature1ServiceData : public IFeature1ServiceData
{
private:
    Data* data_;
public:

    Feature1ServiceData();
    ~Feature1ServiceData();
};