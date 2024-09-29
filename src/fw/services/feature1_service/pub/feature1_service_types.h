#pragma once

#include <string>
#include <boost/optional.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include "customDataType.h"
enum PersonType
{
    STUDENT = 0,
    TEACHER
};

class PersonTypeString
{
public:
    /**
     * @brief Class to contain all the common constants for scanJob
     *
     */
    static constexpr const char *STUDENT = "student";
    static constexpr const char *TEACHER = "teacher";
};

class Person
{
public:
    // Required fields
    CustomDataType<std::string> name;
    CustomDataType<int> age;
    CustomDataType<PersonType> type;

    // Optional fields
    boost::optional<std::string> address;
    boost::optional<int64_t> phone;

    // Default constructor
    Person() = default;

    // Constructor that accepts a pointer to another Person object and copies its data
    Person(const Person *other)
    {
        if (other)
        {
            name = other->name;
            age = other->age;
            type = other->type;
            address = other->address;
            phone = other->phone;
        }
    }

    // Define a from_json function to convert JSON to Person
    friend void from_json(const nlohmann::json &j, Person &p)
    {
        j.at("name").get_to(p.name.value);
        j.at("age").get_to(p.age.value);
        p.type.value = personTypeStringToInt(j.at("type"));

        if (j.contains("address"))
        {
            p.address = j.at("address").get<std::string>();
        }
        if (j.contains("phone"))
        {
            p.phone = static_cast<int64_t>(j.at("phone"));
        }
    }

    friend void to_json(nlohmann::json &j, const Person &p)
    {
        j = nlohmann::json{{"name", p.name.value}, {"age", p.age.value}, {"type", personTypeIntToString(p.type.value)}};
        if (p.address)
        {
            j["address"] = *p.address;
        }
        if (p.phone)
        {
            j["phone"] = *p.phone;
        }
    }

    static PersonType personTypeStringToInt(std::string personType)
    {
        if (personType == PersonTypeString::TEACHER)
        {
            return TEACHER;
        }
        else
        {
            return STUDENT;
        }
    }

    static std::string personTypeIntToString(PersonType personType)
    {
        if (personType == PersonType::TEACHER)
        {
            return PersonTypeString::TEACHER;
        }
        else
        {
            return PersonTypeString::STUDENT;
        }
    }
};

class PersonWithId
{
public:
    CustomDataType<std::string> id;
    CustomDataType<Person> person;
    PersonWithId()
    {
        this->id.value = "";
        person.value = Person();
    }
    friend void to_json(nlohmann::json &j, const PersonWithId &p)
    {
        j = nlohmann::json{{"id", p.id.value}, {"person", p.person.value}};
        
    }
};

class PersonList
{
public:
    CustomDataType<std::vector<std::string>> memberIds;
    boost::optional<std::vector<PersonWithId>> members;
    friend void to_json(nlohmann::json &j, const PersonList &p)
    {
        j = nlohmann::json{
            {"memberIds", p.memberIds.value}
        };
        if (p.members)
        {
            j["members"] = *p.members;
        }
    }
};