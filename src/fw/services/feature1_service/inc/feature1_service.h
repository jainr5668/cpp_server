#pragma once

#include "feature1_service_types.h"
#include "IFeature1Service.h"
#include "logger.h"
#include "Utils.h"
#include "Feature1ServiceInjections.h"
#include <unordered_map>
#include <vector>


class Feature1Service : public IFeature1Service
{
public:
    Feature1Service(Feature1ServiceInjections* feature1ServiceInjections__);
    ~Feature1Service();
    Person* processRequest1(Person*);
    PersonWithId addPerson(Person);
    Person* getPerson(std::string);
    PersonList getPersons(std::unordered_map<std::string, std::string>);
private:
    void connect();
    Feature1ServiceInjections* injections_ = nullptr;
    Logger logger;
    std::string get_uuid();
    std::unordered_map<std::string, Person> personMap;
    std::string getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue);
};