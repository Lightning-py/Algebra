#pragma once

#include "parsing.hpp"
#include <iostream>

auto libs::parse(const line_type &cmd, char sep) -> lines_type
{
    // std::cout << "now processing command: " << cmd << std::endl; 
    lines_type res(0);
    int64_t prev = -1;


    for (int64_t i = 0; i < cmd.size(); ++i)
    {
        if (cmd[i] == sep)
        {
            res.push_back(cmd.substr(prev + 1, i - prev - 1));
            prev = i;
        }
    }

    if (prev < cmd.size())
    {
        res.push_back(cmd.substr(prev + 1, cmd.size() - prev - 2));
    }


    return res;
}
