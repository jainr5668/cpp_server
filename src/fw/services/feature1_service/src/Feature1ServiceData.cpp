#include "Feature1ServiceData.h"

Feature1ServiceData::Feature1ServiceData()
{
    data_ = new Data("Feature1ServiceData");
}
Feature1ServiceData::~Feature1ServiceData()
{
    delete data_;
}