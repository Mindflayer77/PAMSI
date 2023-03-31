#pragma once
#include "RunTimeException.h"

class QueueEmpty : public RunTimeException {
public:
  QueueEmpty(const std::string &err) : RunTimeException(err) {}
};