#pragma once

#include <fstream> // std::ifstream
#include <map>     // std::map

#include "parsing.hpp"
#include "variables.hpp"

namespace arch
{
  class Interpreter
  {
  public:
    using path_type = libs::line_type;

    Interpreter(const path_type &logPath);
    ~Interpreter()
    {
        
    } // 2023.12.12

    auto readCommand() -> void;
    auto readLogFile() -> void; // 2023.12.12

  private:
    using file_stream_type_ = std::ifstream;
    using key_type_ = libs::line_type;
    using elements_type_ = libs::lines_type;
    using commands_type_ =
        std::map<key_type_,
                 void (Interpreter::*)(const elements_type_ &)>;
    using command_type_ = libs::line_type;

    const path_type logPath_;
    file_stream_type_ fileStrm_;
    const commands_type_ commands_;
    daba::Database<key_type_, float> database_;

    auto set(const elements_type_ &commandElements) -> void;
    auto dot(const elements_type_ &commandElements) -> void;
    auto out(const elements_type_ &commandElements) -> void;
    // cross and others... // 2023.12.12
    // CMakeLists // 2023.12.12
  };
}