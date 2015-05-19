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

  InvalidDurationValue::InvalidDurationValue(const char* msg) :
      exception(),
      m_message(msg)
  {
  }

  const char* InvalidDurationValue::what() const throw()
  {
    return m_message;
  }

  InvalidDelayValue::InvalidDelayValue(const char* msg) :
      exception(),
      m_message(msg)
  {
  }

  const char* InvalidDelayValue::what() const throw()
  {
    return m_message;
  }
}


