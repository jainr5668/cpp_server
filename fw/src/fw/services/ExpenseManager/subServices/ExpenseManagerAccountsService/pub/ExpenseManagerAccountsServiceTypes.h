#ifndef EXPENSEMANAGERACCOUNTSSERVICETYPES_H
#define EXPENSEMANAGERACCOUNTSSERVICETYPES_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <chrono>
#include "customDataType.h"
#include "boost/optional.hpp"

namespace services
{
    namespace ExpenseManagerService
    {
        namespace ExpenseManagerAccountsServiceTypes
        {
            /**
             * @brief This class is used to store the data of the accounts that are posted
             */
            class ExpenseManagerAccountsPostData
            {
            public:
                CustomDataType<std::string> name;
                CustomDataType<std::string> description;
                CustomDataType<std::string> type;
                CustomDataType<std::string> currency;
                CustomDataType<std::string> balance;
                CustomDataType<std::string> userId;

                ExpenseManagerAccountsPostData() = default;

                ExpenseManagerAccountsPostData(std::string name, std::string description, std::string type, std::string currency, std::string balance, std::string userId)
                {
                    this->name.value = name;
                    this->description.value = description;
                    this->type.value = type;
                    this->currency.value = currency;
                    this->balance.value = balance;
                    this->userId.value = userId;
                }

                ~ExpenseManagerAccountsPostData() = default;

                ExpenseManagerAccountsPostData(const ExpenseManagerAccountsPostData &other)
                {
                    name.value = other.name.value;
                    description.value = other.description.value;
                    type.value = other.type.value;
                    currency.value = other.currency.value;
                    balance.value = other.balance.value;
                    userId.value = other.userId.value;
                };

                ExpenseManagerAccountsPostData(std::vector<std::string> data)
                {
                    name.value = data[0];
                    description.value = data[1];
                    type.value = data[2];
                    currency.value = data[3];
                    balance.value = data[4];
                    userId.value = data[5];
                };

                friend void to_json(nlohmann::json &j, const ExpenseManagerAccountsPostData &p)
                {
                    j = nlohmann::json{
                        {"name", p.name.value},
                        {"description", p.description.value},
                        {"type", p.type.value},
                        {"currency", p.currency.value},
                        {"balance", p.balance.value},
                        {"userId", p.userId.value}};
                }
            };

            /**
             * @brief This class is used to store the data of the accounts in the database
             */
            class ExpenseManagerAccountsDbData
            {
            public:
                CustomDataType<std::string> name;
                CustomDataType<std::string> description;
                CustomDataType<std::string> type;
                CustomDataType<std::string> currency;
                CustomDataType<std::string> balance;
                CustomDataType<std::string> userId;
                CustomDataType<std::string> id;

                ExpenseManagerAccountsDbData() = default;

                ExpenseManagerAccountsDbData(std::string name, std::string description, std::string type, std::string currency, std::string balance, std::string userId, std::string id)
                {
                    this->name.value = name;
                    this->description.value = description;
                    this->type.value = type;
                    this->currency.value = currency;
                    this->balance.value = balance;
                    this->userId.value = userId;
                    this->id.value = id;
                }
            };
        } // namespace ExpenseManagerAccountsService
    } // namespace ExpenseManagerAccountsService
}
#endif // EXPENSEMANAGERACCOUNTSSERVICETYPES_H