#include <iostream>  // std::{cout, endl}
#include <stdexcept> // std::{invalid_argument, out_of_range}

#include "parsing.hpp"
#include "interpreter.hpp"
#include "variables.hpp"

int main()
{
    try
    {
        arch::Interpreter inpr("./log.txt");
        
        inpr.readLogFile();

        // inpr.readCommand();
        // inpr.readCommand();
        // inpr.readCommand();
        // inpr.readCommand();
        // inpr.readCommand();
        // inpr.readCommand();
        
    }
    catch (const std::invalid_argument &exc)
    {
        std::cout << exc.what() << std::endl;
    }
    catch (const std::out_of_range &exc)
    {
        std::cout << exc.what() << std::endl;
    }

    // system("pause");
    return 0;
}
