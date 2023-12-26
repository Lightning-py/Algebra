#pragma once
#include <regex>
#include <map>
#include <typeinfo>

#include <iostream>
#include "parsing.hpp"
#include "variables.hpp"

namespace daba
{
    enum class type_ {None, Int, Float, String, VectInt, VectFloat, VectString};


    struct Value
    {
        type_ type = type_::None;
        int value_int;
        float value_float;
        std::string value_string;

        std::vector<int> value_vector_int;
        std::vector<float> value_vector_float;
    };




    class Database
    {
        public:
        Database()
        { }
        ~Database()
        { }


        bool is_int(std::string value)
        {
            return std::regex_match(value, std::regex(R"(\d+)"));
        }


        bool is_float(std::string value)
        {
            return std::regex_match(value, std::regex(R"(\d+\.\d+)"));
        }


        type_ check_type(std::vector<std::string> values)
        {
            if (values.size() == 1)
            {
                if (is_int(values[0]))
                    return type_::Int;
                else if (is_float(values[0]))
                    return type_::Float;
                return type_::String;
            }

            type_ types = type_::VectInt;
            for (auto value: values)
            {
                if (is_float(value))
                    types = type_::VectFloat;
                else if (!is_int(value))
                {
                    // строка в векторе - ошибка
                

                }
            }

            return types;
        }


        void set(std::string name, std::vector<std::string> values)
        {
            type_ this_type = check_type(values);

            Value v;
            v.type = this_type;

            if (this_type == type_::Int)
            {
                v.value_int = std::stoi(values[0]);
            }
            else if (this_type == type_::Float)
            {
                v.value_float = std::stof(values[0]);
            }
            else if (this_type == type_::String)
            {
                v.value_string = values[0];
            }
            else if (this_type == type_::VectInt)
            {
                std::vector<int> values_parsed;
                for (std::string value: values)
                {
                    values_parsed.push_back(std::stoi(value));
                }
                v.value_vector_int = values_parsed;
            }
            else if (this_type == type_::VectFloat)
            {
                std::vector<float> values_parsed;
                for (std::string value: values)
                {
                    values_parsed.push_back(std::stof(value));
                }
                v.value_vector_float = values_parsed;
            }
            
            db.insert(std::make_pair(name, v));
        }

        bool set(std::string name, Value v)
        {
            type_ this_type = v.type;


            if (this_type == type_::Int)
            {
                v.value_int = v.value_int;
            }
            else if (this_type == type_::Float)
            {
                v.value_float = v.value_float;
            }
            else if (this_type == type_::String)
            {
                v.value_string = v.value_string;
            }
            else if (this_type == type_::VectInt)
            {
                v.value_vector_int = v.value_vector_int;
            }
            else if (this_type == type_::VectFloat)
            {
                v.value_vector_float = v.value_vector_float;
            }
            
            db.insert(std::make_pair(name, v));
            return true;
        }

        Value get(std::string name)
        {
            return db[name];
        }

        private:
            std::map<std::string, Value> db;

    };


}



// упорядочить структуру // 2023.12.12
// создать другие типы шаблона: path_type, vector_type // 2023.12.12
// set/get, чтобы получать значения по имени // 2023.12.12