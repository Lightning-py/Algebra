#pragma once

#include <stdexcept> // std::invalid_argument
#include <string>    // std::getline

#include <iostream>
#include "interpreter.hpp"
#include "parsing.hpp"

arch::Interpreter::Interpreter(
    const path_type &logPath) : logPath_(logPath), fileStrm_(logPath_), commands_{
                                                                            {"SET", &Interpreter::set},
                                                                            {"DOT", &Interpreter::dot},
                                                                            {"OUT", &Interpreter::out},
                                                                            {"set", &Interpreter::set},
                                                                            {"PLUS", &Interpreter::plus},
                                                                            {"FOUT", &Interpreter::fout}

                                                                            }
{
  if (!this->fileStrm_.is_open())
  {
    throw std::invalid_argument("wrong log path");
  }
}

auto arch::Interpreter::readCommand() -> void
{
    command_type_ cmd;

    std::getline(this->fileStrm_, cmd);
    

    auto parsedCmd = libs::parse(cmd); // парсинг полученной с ввода строки


    auto key = parsedCmd.front(); // получение названия команды
    auto elems = elements_type_(++parsedCmd.begin(), parsedCmd.end()); // получение аргументов
    
    try
    {
        (this->*this->commands_.at(key))(elems); // вызов команды, соответствующей функции
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

auto arch::Interpreter::readLogFile() -> void
{
    command_type_ cmd;

    while (std::getline(this->fileStrm_, cmd))
    {
        auto parsedCmd = libs::parse(cmd); // парсинг полученной с ввода строки


        auto key = parsedCmd.front(); // получение названия команды
        auto elems = elements_type_(++parsedCmd.begin(), parsedCmd.end()); // получение аргументов
        
        try
        {
            (this->*this->commands_.at(key))(elems); // вызов команды, соответствующей функции
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

auto arch::Interpreter::set(const elements_type_ &cmdElems) -> void
{
    // std::cout << "doing a command set" << std::endl;
    const auto name = cmdElems.front();
    const auto vals = elements_type_(++cmdElems.begin(), cmdElems.end());
    this->database_.set(name, vals);
}

auto arch::Interpreter::dot(const elements_type_ &commandElements) -> void
{
    // std::cout << "doing a command DOT" << std::endl;

    std::string name1, name2, name3;
    daba::Value v1, v2;

    name1 = commandElements[0];
    name2 = commandElements[1];
    name3 = commandElements[2];

    v1 = database_.get(name1);
    v2 = database_.get(name2);
    
    if ( !(v1.type == daba::type_::VectInt || v1.type == daba::type_::VectInt) || !(v2.type == daba::type_::VectInt || v2.type == daba::type_::VectInt))
    {
        std::cout << "invalid or nonexisted arguments" << std::endl;
        return;
    }

    if (v1.type == daba::type_::VectInt)
    {
        std::vector<int> v1_v = v1.value_vector_int;

        if (v2.type == daba::type_::VectInt)
        {
            if (v1.value_vector_int.size() != v2.value_vector_int.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            int result = 0;
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result += v1.value_vector_int[i] * v2.value_vector_int[i];
            }
            std::vector<std::string> res;
            res.push_back(std::to_string(result));

            database_.set(name3, res);
        }
        else if (v2.type == daba::type_::VectFloat)
        {
            if (v1.value_vector_int.size() != v2.value_vector_float.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            float result = 0;
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result += v1.value_vector_int[i] * v2.value_vector_float[i];
            }
            std::vector<std::string> res;
            res.push_back(std::to_string(result));

            database_.set(name3, res);
        }
    }
    else if  (v1.type == daba::type_::VectFloat)
    {
        if (v2.type == daba::type_::VectInt)
        {
            if (v1.value_vector_float.size() != v2.value_vector_int.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            float result = 0;
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result += v1.value_vector_float[i] * v2.value_vector_int[i];
            }
            std::vector<std::string> res;
            res.push_back(std::to_string(result));

            database_.set(name3, res);
        }
        else if (v2.type == daba::type_::VectFloat)
        {
            if (v1.value_vector_float.size() != v2.value_vector_float.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            float result = 0;
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result += v1.value_vector_float[i] * v2.value_vector_float[i];
            }
            std::vector<std::string> res;
            res.push_back(std::to_string(result));

            database_.set(name3, res);
        }
    }
}

auto arch::Interpreter::out(const elements_type_ &commandElements) -> void
{
    // std::cout << "doing a command OUT" << std::endl;


    std::string name = commandElements[0];


    daba::Value result = database_.get(name);
    // std::cout << (int)result.type << std::endl;

    switch (result.type)
    {
    case daba::type_::Int:
        std::cout << "Variable name: " << name << " value: " << result.value_int << std::endl;
        break;
    case daba::type_::Float:
        std::cout << "Variable name: " << name << " value: " << result.value_float << std::endl;
        break;
    
    case daba::type_::String:
        std::cout << "Variable name: " << name << " value: " << result.value_string << std::endl;
        break;

    case daba::type_::VectInt:
        std::cout << "Variable name: " << name << " values: ";
        for (auto value: result.value_vector_int)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        break;
    
    case daba::type_::VectFloat:
        std::cout << "Variable name: " << name << " values: ";
        for (auto value: result.value_vector_float)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        break;

    default:
        break;
    }
}

auto arch::Interpreter::plus(const elements_type_ &commandElements) -> void
{
    std::string name1, name2, result;

    name1 = commandElements[0];
    name2 = commandElements[1];
    result = commandElements[2];

    daba::Value v1, v2, result_v;
    v1 = database_.get(name1);
    v2 = database_.get(name2);

    if (v1.type == daba::type_::Int)
    {
        if (v2.type == daba::type_::Int)
        {
            result_v.type = daba::type_::Int;

            result_v.value_int = v1.value_int + v2.value_float;

            database_.set(result, result_v);
            return;
        }
        else if (v2.type == daba::type_::Float)
        {
            result_v.type = daba::type_::Float;

            result_v.value_float = v1.value_int + v2.value_float;

            database_.set(result, result_v);
            return;
        } 
    }
    else if (v1.type == daba::type_::Float)
    {
        if (v2.type == daba::type_::Int)
        {
            result_v.type = daba::type_::Float;

            result_v.value_float = v1.value_int + v2.value_float;

            database_.set(result, result_v);
            return;
        }
        else if (v2.type == daba::type_::Float)
        {
            result_v.type = daba::type_::Float;

            result_v.value_float = v1.value_int + v2.value_float;

            database_.set(result, result_v);
            return;
        }
    }

    if (v1.type == daba::type_::VectInt)
    {
        std::vector<int> v1_v = v1.value_vector_int;

        if (v2.type == daba::type_::VectInt)
        {
            if (v1.value_vector_int.size() != v2.value_vector_int.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            
            std::vector<int> result_(v1.value_vector_int.size());
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result_[i] = v1.value_vector_int[i] + v2.value_vector_int[i];
            }

            result_v.type = daba::type_::VectInt;
            result_v.value_vector_int = result_;

            database_.set(result, result_v);
            return;
        }
        else if (v2.type == daba::type_::VectFloat)
        {
            if (v1.value_vector_int.size() != v2.value_vector_float.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            
            std::vector<float> result_(v1.value_vector_int.size());
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result_[i] = v1.value_vector_int[i] + v2.value_vector_int[i];
            }

            result_v.type = daba::type_::VectFloat;
            result_v.value_vector_float = result_;

            database_.set(result, result_v);
            return;
        }
    }
    else if  (v1.type == daba::type_::VectFloat)
    {
        if (v2.type == daba::type_::VectInt)
        {
            if (v1.value_vector_float.size() != v2.value_vector_int.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            
            std::vector<float> result_(v1.value_vector_int.size());
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result_[i] = v1.value_vector_int[i] + v2.value_vector_int[i];
            }

            result_v.type = daba::type_::VectFloat;
            result_v.value_vector_float = result_;

            database_.set(result, result_v);
            return;
        }
        else if (v2.type == daba::type_::VectFloat)
        {
            if (v1.value_vector_float.size() != v2.value_vector_float.size())
            {
                std::cout << "размер векторов не совпадает" << std::endl;
                return;
            }
            
            std::vector<float> result_(v1.value_vector_int.size());
            for (int i = 0; i < v1.value_vector_int.size(); ++i)
            {
                result_[i] = v1.value_vector_int[i] + v2.value_vector_int[i];
            }

            result_v.type = daba::type_::VectFloat;
            result_v.value_vector_float = result_;

            database_.set(result, result_v);
            return;
        }
    }    
}

auto arch::Interpreter::fout(const elements_type_ &commandElements) -> void
{
    std::string filename, filename_, elementname;

    filename_ = commandElements[0];
    daba::Value v = database_.get(filename_);

    filename = v.value_string;

    elementname = commandElements[1];

    std::ofstream out;
    try
    {
        out.open(filename);
    }
    catch(const std::exception& e)
    {
        std::cout << "неверное имя файла" << std::endl;
        return;
    }
    

    if (out.is_open())
    {
        daba::Value result = database_.get(elementname);
    // std::cout << (int)result.type << std::endl;

        switch (result.type)
        {
        case daba::type_::Int:
            out << "Variable name: " << elementname << " value: " << result.value_int << std::endl;
            break;
        case daba::type_::Float:
            out << "Variable name: " << elementname << " value: " << result.value_float << std::endl;
            break;
        
        case daba::type_::String:
            out << "Variable name: " << elementname << " value: " << result.value_string << std::endl;
            break;

        case daba::type_::VectInt:
            out << "Variable name: " << elementname << " values: ";
            for (auto value: result.value_vector_int)
            {
                out << value << " ";
            }
            out << std::endl;
            break;
        
        case daba::type_::VectFloat:
            out << "Variable name: " << elementname << " values: ";
            for (auto value: result.value_vector_float)
            {
                out << value << " ";
            }
            out << std::endl;
            break;

        default:
            break;
        }
    }
    else
    {
        std::cout << "при записи файла что-то пошло не так" << std::endl;
    }
    out.close(); 
}