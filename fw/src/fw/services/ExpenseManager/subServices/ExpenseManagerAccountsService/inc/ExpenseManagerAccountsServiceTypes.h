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

            enum class AccountType
            {
                Other = 1,
                Savings,
                Checking,
                CreditCard,
                Cash,
                Investment,
                Loan
            };
            static std::unordered_map<AccountType, std::string> accountTypeToString{
                {AccountType::Savings, "savings"},
                {AccountType::Checking, "checking"},
                {AccountType::CreditCard, "creditCard"},
                {AccountType::Cash, "cash"},
                {AccountType::Investment, "investment"},
                {AccountType::Loan, "loan"},
                {AccountType::Other, "other"}};
            
            static std::unordered_map<std::string, AccountType> stringToAccountType{
                {"savings", AccountType::Savings},
                {"checking", AccountType::Checking},
                {"creditCard", AccountType::CreditCard},
                {"cash", AccountType::Cash},
                {"investment", AccountType::Investment},
                {"loan", AccountType::Loan},
                {"other", AccountType::Other}};

            enum class CurrencyCode
            {
                USD = 1,
                EUR,
                GBP,
                INR,
                AUD,
                CAD,
                SGD,
                JPY,
                CNY,
                HKD
            };

            static std::unordered_map<CurrencyCode, std::string> currencyCodeToString{
                {CurrencyCode::USD, "USD"},
                {CurrencyCode::EUR, "EUR"},
                {CurrencyCode::GBP, "GBP"},
                {CurrencyCode::INR, "INR"},
                {CurrencyCode::AUD, "AUD"},
                {CurrencyCode::CAD, "CAD"},
                {CurrencyCode::SGD, "SGD"},
                {CurrencyCode::JPY, "JPY"},
                {CurrencyCode::CNY, "CNY"},
                {CurrencyCode::HKD, "HKD"}};

            static std::unordered_map<std::string, CurrencyCode> stringToCurrencyCode{
                {"USD", CurrencyCode::USD},
                {"EUR", CurrencyCode::EUR},
                {"GBP", CurrencyCode::GBP},
                {"INR", CurrencyCode::INR},
                {"AUD", CurrencyCode::AUD},
                {"CAD", CurrencyCode::CAD},
                {"SGD", CurrencyCode::SGD},
                {"JPY", CurrencyCode::JPY},
                {"CNY", CurrencyCode::CNY},
                {"HKD", CurrencyCode::HKD}};

            /**
             * @brief This class is used to store the data of the accounts that are posted
             */
            class ExpenseManagerAccountsPostData
            {
            public:
                CustomDataType<std::string> accountName;
                CustomDataType<std::string> description;
                CustomDataType<AccountType> accountType;
                CustomDataType<CurrencyCode> currencyCode;
                CustomDataType<double> balance;
                CustomDataType<std::string> userId;

                ExpenseManagerAccountsPostData() = default;

                ~ExpenseManagerAccountsPostData() = default;

                ExpenseManagerAccountsPostData(const ExpenseManagerAccountsPostData &other)
                {
                    accountName.value = other.accountName.value;
                    description.value = other.description.value;
                    accountType.value = other.accountType.value;
                    currencyCode.value = other.currencyCode.value;
                    balance.value = other.balance.value;
                    userId.value = other.userId.value;
                };

                ExpenseManagerAccountsPostData(std::vector<std::string> data)
                {
                    accountName.value = data[0];
                    description.value = data[1];
                    accountType.value = stringToAccountType[data[2]];
                    currencyCode.value = stringToCurrencyCode[data[3]];
                    balance.value = atof(data[4].c_str());
                    userId.value = data[5];
                };

                friend void to_json(nlohmann::json &j, const ExpenseManagerAccountsPostData &p)
                {
                    j = nlohmann::json{
                        {"name", p.accountName.value},
                        {"description", p.description.value},
                        {"accountType", accountTypeToString[p.accountType.value]},
                        {"currencyCode", currencyCodeToString[p.currencyCode.value]},
                        {"balance", p.balance.value}
                    };
                    if(p.userId.value != "")
                    {
                        j["userId"] = p.userId.value;
                    }
                }

                friend void from_json(const nlohmann::json &j, ExpenseManagerAccountsPostData &p)
                {
                    j.at("accountName").get_to(p.accountName.value);
                    j.at("description").get_to(p.description.value);
                    if (stringToAccountType.find(j.at("accountType").get<std::string>()) != stringToAccountType.end())
                    {
                        p.accountType.value = stringToAccountType.at(j.at("accountType").get<std::string>());
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid Account Type");
                    }
                    if (stringToCurrencyCode.find(j.at("currencyCode").get<std::string>()) != stringToCurrencyCode.end())
                    {
                        p.currencyCode.value = stringToCurrencyCode.at(j.at("currencyCode").get<std::string>());
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid Currency Code");
                    }
                    j.at("balance").get_to(p.balance.value);
                    if (j.contains("userId"))
                    {
                        j.at("userId").get_to(p.userId.value);
                    }
                }
            };

            /**
             * @brief This class is used to store the data of the accounts in the database
             */
            class ExpenseManagerAccountsDbData
            {
            public:
                CustomDataType<std::string> accountName;
                CustomDataType<std::string> description;
                CustomDataType<std::string> accountType;
                CustomDataType<std::string> currencyCode;
                CustomDataType<std::string> balance;
                boost::optional<std::string> userId;
                CustomDataType<std::string> id;
                CustomDataType<std::string> updatedAt;
                CustomDataType<std::string> createdAt;
                CustomDataType<std::string> isActive;

                ExpenseManagerAccountsDbData() = default;

                friend void to_json(nlohmann::json &j, const ExpenseManagerAccountsDbData &p)
                {
                    j = nlohmann::json{
                        {"id", p.id.value},
                        {"accountName", p.accountName.value},
                        {"description", p.description.value},
                        {"accountType", p.accountType.value},
                        {"currencyCode", p.currencyCode.value},
                        {"balance", p.balance.value},
                        {"updatedAt", p.updatedAt.value},
                        {"createdAt", p.createdAt.value},
                        {"isActive", p.isActive.value}
                    };
                    if(p.userId.has_value())
                    {
                        j["userId"] = p.userId.value();
                    }
                }
            };
        } // namespace ExpenseManagerAccountsService
    } // namespace ExpenseManagerAccountsService
}
#endif // EXPENSEMANAGERACCOUNTSSERVICETYPES_H