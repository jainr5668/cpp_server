#ifndef CUSTOMDATATYPE_H
#define CUSTOMDATATYPE_H
#include <type_traits>
template <typename T>
class CustomDataType
{
public:
    T value;
    T get_value_or(T default_value)
    {
        if (value)
            return value;
        else
            return default_value;
    }
    bool has_value()
    {
        if constexpr (std::is_pointer<T>::value)
        {
            return value != nullptr;
        }
        else
        {
            return value != T{};
        }
    }
};
#endif // CUSTOMDATATYPE_H
