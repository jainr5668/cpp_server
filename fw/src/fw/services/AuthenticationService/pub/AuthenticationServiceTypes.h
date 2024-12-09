#ifndef AUTHENTICATIONSERVICETYPES_H
#define AUTHENTICATIONSERVICETYPES_H
#include "customDataType.h"
#include <string>
#include <nlohmann/json.hpp>
#include <boost/optional.hpp>
#include <iostream>

namespace services
{
    namespace AuthenticationService
    {
        namespace AuthenticationServiceTypes
        {
            class LoginData
            {
            public:
                CustomDataType<std::string> username;
                CustomDataType<std::string> password;

                LoginData(std::string username, std::string password)
                {
                    this->username.value = username;
                    this->password.value = password;
                }

                LoginData()
                {
                    this->username.value = "";
                    this->password.value = "";
                }

                LoginData(LoginData *loginData)
                {
                    this->username.value = loginData->username.value;
                    this->password.value = loginData->password.value;
                }

                friend void from_json(const nlohmann::json &j, LoginData &data)
                {
                    j.at("username").get_to(data.username.value);
                    j.at("password").get_to(data.password.value);
                }

                friend void to_json(nlohmann::json &j, const LoginData &data)
                {
                    j = nlohmann::json{{"username", data.username.value}, {"password", data.password.value}};
                }
            };
            class LoginResponse
            {
            public:
                CustomDataType<std::string> access_token;
                CustomDataType<std::string> token_type;

                LoginResponse(std::string token, std::string token_type)
                {
                    this->access_token.value = token;
                    this->token_type.value = token_type;
                }

                LoginResponse()
                {
                    this->access_token.value = "";
                    this->token_type.value = "";
                }

                LoginResponse(LoginResponse *loginResponse)
                {
                    this->access_token.value = loginResponse->access_token.value;
                    this->token_type.value = loginResponse->token_type.value;
                }

                friend void from_json(const nlohmann::json &j, LoginResponse &data)
                {
                    j.at("access_token").get_to(data.access_token.value);
                    j.at("token_type").get_to(data.token_type.value);
                }

                friend void to_json(nlohmann::json &j, const LoginResponse &data)
                {
                    j = nlohmann::json{{"access_token", data.access_token.value}, {"token_type", data.token_type.value}};
                }
            };
            class UserDataModel
            {

            public:
                CustomDataType<std::string> id;
                CustomDataType<std::string> username;
                CustomDataType<std::string> password;

                UserDataModel(std::string id, std::string username, std::string password)
                {
                    this->id.value = id;
                    this->username.value = username;
                    this->password.value = password;
                }

                UserDataModel()
                {
                    this->id.value = "";
                    this->username.value = "";
                    this->password.value = "";
                }

                UserDataModel(UserDataModel *userDataModel)
                {
                    this->id.value = userDataModel->id.value;
                    this->username.value = userDataModel->username.value;
                    this->password.value = userDataModel->password.value;
                }

                UserDataModel(std::vector<std::string> userData)
                {
                    this->id.value = userData[0];
                    this->username.value = userData[1];
                    this->password.value = userData[2];
                }

                friend void from_json(const nlohmann::json &j, UserDataModel &data)
                {
                    j.at("id").get_to(data.id.value);
                    j.at("username").get_to(data.username.value);
                    j.at("password").get_to(data.password.value);
                }

                friend void to_json(nlohmann::json &j, const UserDataModel &data)
                {
                    j = nlohmann::json{{"id", data.id.value}, {"username", data.username.value}, {"password", data.password.value}};
                }
            };
            class SingupData
            {
            public:
                CustomDataType<std::string> username;
                CustomDataType<std::string> password;
                CustomDataType<uint64_t> mobile1;
                boost::optional<uint64_t> mobile2;

                SingupData(std::string username, std::string password, uint64_t mobile1, boost::optional<uint64_t> mobile2)
                {
                    this->username.value = username;
                    this->password.value = password;
                    this->mobile1.value = mobile1;
                    this->mobile2 = mobile2;
                }

                SingupData()
                {
                    this->username.value = "";
                    this->password.value = "";
                    this->mobile1.value = 0;
                    this->mobile2 = 0;
                }

                SingupData(SingupData *singupData)
                {
                    this->username.value = singupData->username.value;
                    this->password.value = singupData->password.value;
                    this->mobile1.value = singupData->mobile1.value;
                    this->mobile2 = singupData->mobile2.value();
                }

                friend void from_json(const nlohmann::json &j, SingupData &data)
                {
                    if (j.contains("username") && j.at("username").is_string())
                    {
                        j.at("username").get_to(data.username.value);
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid or missing 'username'");
                    }

                    if (j.contains("password") && j.at("password").is_string())
                    {
                        j.at("password").get_to(data.password.value);
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid or missing 'password'");
                    }

                    if (j.contains("mobile1") && j.at("mobile1").is_number_unsigned())
                    {
                        j.at("mobile1").get_to(data.mobile1.value);
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid or missing 'mobile1'");
                    }

                    if (j.contains("mobile2"))
                    {
                        if (j.at("mobile2").is_number_unsigned())
                        {
                            data.mobile2 = j.at("mobile2").get<uint64_t>();
                        }
                        else
                        {
                            throw std::invalid_argument("Invalid 'mobile2'");
                        }
                    }
                }

                friend void to_json(nlohmann::json &j, const SingupData &data)
                {
                    j = nlohmann::json{{"username", data.username.value}, {"password", data.password.value}, {"mobile1", data.mobile1.value}};
                    if (data.mobile2.has_value())
                    {
                        j["mobile2"] = data.mobile2.value();
                    }
                }
            };
            class SignupResponse
            {
            };
        } // namespace services::AuthenticationService::AuthenticationServiceTypes
    } // namespace services::AuthenticationService
} // namespace services
#endif // AUTHENTICATIONSERVICETYPES_H
