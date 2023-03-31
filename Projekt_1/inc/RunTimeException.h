#pragma once
#include <iostream>
#include <string>

class RunTimeException {
private:
  std::string errMessage;

public:
  RunTimeException(const std::string &err) : errMessage(err) {}
  std::string getMessage() const { return errMessage; }
};
