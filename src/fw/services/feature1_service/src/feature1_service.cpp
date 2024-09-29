#include "feature1_service.h"
#include <random>

Feature1Service::Feature1Service(Feature1ServiceInjections* feature1ServiceInjections__)
    : injections_(feature1ServiceInjections__)
{
    logger.info("Feature1Service::Feature1Service Constructor Entry");
    if (injections_ == nullptr)
    {
        logger.error("Feature1Service::Feature1Service Constructor: injections_ is null");
    }
    connect();
    logger.info("Feature1Service::Feature1Service Constructor Exit");
}

void Feature1Service::connect()
{
    logger.info("Feature1Service::connect Entry");
    bool connected = true;
    if (injections_->feature1ServiceData_ == nullptr)
    {
        connected = false;
        logger.error("Feature1Service::connect: injections_->feature1ServiceData_ is null");
    }
    if (injections_->utils_ == nullptr)
    {
        connected = false;
        logger.error("Feature1Service::connect: injections_->utils_ is null");
    }
    if(!connected)
    {
        throw std::runtime_error("Feature1Service::connect: Not all dependencies are connected");
    }
    logger.info("Feature1Service::connect Exit");
}

Feature1Service::~Feature1Service()
{
    logger.info("Feature1Service::~Feature1Service Destructor Entry");
    logger.info("Feature1Service::~Feature1Service Destructor Exit");
}

Person *Feature1Service::processRequest1(Person *person_)
{
    logger.info("Feature1Service::processRequest1 Entry");
    Person *person = nullptr;
    if (person_)
    {
        person = new Person(person_);
    }
    logger.info("Feature1Service::processRequest1 Exit");
    return person;
}
PersonWithId Feature1Service::addPerson(Person person_)
{
    logger.info("Feature1Service::addPerson Entry");
    PersonWithId personWithId;
    personWithId.id.value = get_uuid();
    personWithId.person.value = person_;
    personMap[personWithId.id.value] = personWithId.person.value;
    logger.info("Feature1Service::addPerson Exit");
    return personWithId;
}
Person* Feature1Service::getPerson(std::string id_)
{
    logger.info("Feature1Service::getPerson Entry");
    Person *person = nullptr;
    auto p = personMap.find(id_);
    if (p != personMap.end())
    {
        person = &(p->second);
    }
    logger.info("Feature1Service::getPerson Exit");
    return person;
}

PersonList Feature1Service::getPersons(std::unordered_map<std::string, std::string> path_params)
{
    logger.info("Feature1Service::getPersons Entry");
    auto includeMembers = injections_->utils_->getValueFromMap(path_params, "includeMembers", "false") == "true";
    PersonList personList;
    std::vector<PersonWithId> personListWithId_;
    for (auto &p : personMap)
    {
        PersonWithId personWithId;
        personWithId.id.value = p.first;
        personWithId.person.value = p.second;
        personListWithId_.push_back(personWithId);
        personList.memberIds.value.push_back(personWithId.id.value);
    }
    if (includeMembers)
    {
        personList.members = personListWithId_;
    }
    std::unordered_map<std::string, Person> personMap;
    logger.info("Feature1Service::getPersons Exit");
    return personList;
}

std::string Feature1Service::getValueFromMap(std::unordered_map<std::string, std::string> map, std::string key, std::string defaultValue)
{
    auto value = map.find(key);
    if (value != map.end())
    {
        return value->second;
    }
    return defaultValue;
}

std::string Feature1Service::get_uuid()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    std::string res;
    for (int i = 0; i < 16; i++)
    {
        if (dash[i])
            res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}
