#pragma once
#include "BaseEndpoint.h"

namespace endpoints{
    namespace ExpenseManager{
        class IExpenseManagerEndpoint : public BaseEndpoint{};
    }
}
DEFINE_MODULE_UID(endpoints::ExpenseManager::IExpenseManagerEndpoint, "2174221216")