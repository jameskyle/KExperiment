#include "ComponentExceptions.h"

namespace kex
{
  InvalidComponentType::InvalidComponentType(const char* msg) :
      exception(),
      m_message(msg)
  {
  }

  const char* InvalidComponentType::what() const throw()
  {
    return m_message;
  }
}


