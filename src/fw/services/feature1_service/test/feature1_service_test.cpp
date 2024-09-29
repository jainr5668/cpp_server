#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "feature1_service.h"
#include "Feature1ServiceData.h"

class Feature1ServiceTest : public ::testing::Test
{
public:
    Feature1Service *feature1Service;
    Person *p1;

    void SetUp() override
    {
        Feature1ServiceInjections* feature1ServiceInjections = new Feature1ServiceInjections();
        feature1ServiceInjections->feature1ServiceData_ = new Feature1ServiceData();
        feature1ServiceInjections->utils_ = new Utils();
        feature1Service = new Feature1Service(feature1ServiceInjections);
        p1 = new Person();
        p1->name.value = "John";
        p1->age.value = 25;
        p1->type.value = PersonType::STUDENT;
    }

    void TearDown() override
    {
        delete feature1Service;
        delete p1;
    }
};

TEST_F(Feature1ServiceTest, WhenNullpointerIsPassedToProcessRequest1ThenReturnNullptr)
{
    auto person_ = feature1Service->processRequest1(nullptr);
    EXPECT_EQ(person_, nullptr);
}

TEST_F(Feature1ServiceTest, WhenPersonIsPassedToProcessRequest1ThenReturnPerson)
{
    auto person_ = feature1Service->processRequest1(p1);
    ASSERT_NE(person_, nullptr);
    EXPECT_EQ(person_->name.value, "John");
    EXPECT_EQ(person_->age.value, 25);
    EXPECT_EQ(person_->type.value, PersonType::STUDENT);
    
}

TEST_F(Feature1ServiceTest, WhenPersonIsPassedToAddPersonThenReturnPersonWithId)
{
    auto personWithId = feature1Service->addPerson(*p1);
    EXPECT_TRUE(personWithId.id.has_value());
    EXPECT_EQ(personWithId.person.value.name.value, "John");
    EXPECT_EQ(personWithId.person.value.age.value, 25);
    EXPECT_EQ(personWithId.person.value.type.value, PersonType::STUDENT);
}

TEST_F(Feature1ServiceTest, WhenPersonIsPassedToAddPersonThenGetPersonReturnsPerson)
{
    auto personWithId = feature1Service->addPerson(p1);
    auto person = feature1Service->getPerson(personWithId.id.value);
    EXPECT_NE(person, nullptr);
    EXPECT_EQ(person->name.value, "John");
    EXPECT_EQ(person->age.value, 25);
    EXPECT_EQ(person->type.value, PersonType::STUDENT);
}

TEST_F(Feature1ServiceTest, WhenPersonIsPassedToAddPersonThenOnlyMembersIdsIsPopulatedIfIncludeMembersIsFalse)
{

    feature1Service->addPerson(p1);
    std::unordered_map<std::string, std::string> path_params;
    path_params["includeMembers"] = "false";
    auto personList = feature1Service->getPersons(path_params);
    EXPECT_EQ(personList.memberIds.value.size(), 1);
    EXPECT_FALSE(personList.members.has_value());
}

TEST_F(Feature1ServiceTest, WhenPersonIsPassedToAddPersonThenMembersIdsIsAlsoPopulatedIfIncludeMembersIsTrue)
{

    feature1Service->addPerson(p1);
    std::unordered_map<std::string, std::string> path_params;
    path_params["includeMembers"] = "true";
    auto personList = feature1Service->getPersons(path_params);
    EXPECT_EQ(personList.memberIds.value.size(), 1);
    EXPECT_TRUE(personList.members.has_value());
    EXPECT_EQ(personList.members.get().size(), 1);
}
