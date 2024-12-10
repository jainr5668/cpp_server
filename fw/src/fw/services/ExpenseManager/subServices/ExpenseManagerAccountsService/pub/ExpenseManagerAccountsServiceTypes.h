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

            /**
             * @brief This class is used to store the data of the accounts that are posted
             */
            class ExpenseManagerAccountsPostData
            {
            public:
                CustomDataType<std::string> accountName;
                CustomDataType<std::string> description;
                CustomDataType<AccountType> accountType;
                CustomDataType<std::string> currencyCode;
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
                    accountType.value = stringToAccountType(data[2]);
                    currencyCode.value = data[3];
                    balance.value = atof(data[4].c_str());
                    userId.value = data[5];
                };

                std::string accountTypeToString() const
                {
                    switch (accountType.value)
                    {
                    case AccountType::Savings:
                        return "savings";
                    case AccountType::Checking:
                        return "checking";
                    case AccountType::CreditCard:
                        return "creditCard";
                    case AccountType::Cash:
                        return "cash";
                    case AccountType::Investment:
                        return "investment";
                    case AccountType::Loan:
                        return "loan";
                    case AccountType::Other:
                        return "other";
                    default:
                        return "other";
                    }
                }

                AccountType stringToAccountType(std::string accountType) const
                {
                    if (accountType == "savings")
                    {
                        return AccountType::Savings;
                    }
                    else if (accountType == "checking")
                    {
                        return AccountType::Checking;
                    }
                    else if (accountType == "creditCard")
                    {
                        return AccountType::CreditCard;
                    }
                    else if (accountType == "cash")
                    {
                        return AccountType::Cash;
                    }
                    else if (accountType == "investment")
                    {
                        return AccountType::Investment;
                    }
                    else if (accountType == "loan")
                    {
                        return AccountType::Loan;
                    }
                    else
                    {
                        return AccountType::Other;
                    }
                }
                friend void to_json(nlohmann::json &j, const ExpenseManagerAccountsPostData &p)
                {
                    j = nlohmann::json{
                        {"name", p.accountName.value},
                        {"description", p.description.value},
                        {"accountType", p.accountTypeToString()},
                        {"currencyCode", p.currencyCode.value},
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
                    p.accountType.value = p.stringToAccountType(j.at("accountType").get<std::string>());;
                    j.at("currencyCode").get_to(p.currencyCode.value);
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