#include <stdexcept> // std::invalid_argument
#include <string>    // std::getline

#include "interpreter.hpp"
#include "parsing.hpp"

arch::Interpreter::Interpreter(
    const path_type &logPath) : logPath_(logPath), fileStrm_(logPath_), commands_{
                                                                            {"SET", &Interpreter::set},
                                                                            {"DOT", &Interpreter::dot},
                                                                            {"OUT", &Interpreter::out}}
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
  const auto parsedCmd = libs::parse(cmd);
  const auto key = parsedCmd.front();
  const auto elems = elements_type_(++parsedCmd.begin(), parsedCmd.end());
  (this->*this->commands_.at(key))(elems);
}

auto arch::Interpreter::readLogFile() -> void
{
}

auto arch::Interpreter::set(const elements_type_ &cmdElems) -> void
{
  const auto name = cmdElems.front();
  const auto vals = elements_type_(++cmdElems.begin(), cmdElems.end());
  this->database_.set(name, vals);
}

auto arch::Interpreter::dot(const elements_type_ &commandElements) -> void
{
}

auto arch::Interpreter::out(const elements_type_ &commandElements) -> void
{
}