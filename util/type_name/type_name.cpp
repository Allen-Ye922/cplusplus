
#include <string>
#include <typeindex>
#include <iostream>
#ifdef __GNUC__
#include <cxxabi.h>
#endif


template<typename T>
std::string _type_name()
{
    std::string type_name;
    std::type_index type = std::type_index(typeid(T));
    const char* type_nm = type.name();
    #ifdef __GNUC__
    int status;
    char* realname = abi::__cxa_demangle( type_nm, 0, 0, &status );
    if(realname)
    {
        type_name = realname;
        free(realname);
    }
    else
    #endif
    type_name = type_nm;
    return type_name;
}

//template<typename T>
//struct TypeName { std::string operator()() { return _type_name<T>();}};
template<typename T>
std::string typeName()
{
    if constexpr (std::is_same_v<std::string, T>)
        return "string";
    else if constexpr (std::is_same_v<const char*, T>)
             return "string";
    else
        return _type_name<T>();

}

int main()
{
    std::string str= "slakjfdsl";
    auto name = typeName<typeof(str)>();
    std::cout<<"int name is: "<<name<<std::endl;

    return 0;
}
