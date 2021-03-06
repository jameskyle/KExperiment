#ifndef COMPONENTEXCEPTIONS_H
#define COMPONENTEXCEPTIONS_H

#include <exception>

namespace kex
{
  class InvalidComponentType : public std::exception
  {
  public:
      explicit InvalidComponentType(const char* msg);

      const char* what() const throw();

      ~InvalidComponentType() throw() {}
  private:
      const char* m_message;
  };

  class InvalidDurationValue : public std::exception
  {
  public:
    explicit InvalidDurationValue(const char* msg);

    const char* what() const throw();

    ~InvalidDurationValue() throw() {}

  private:
    const char* m_message;


  };

  class InvalidDelayValue : public std::exception
  {
  public:
    explicit InvalidDelayValue(const char* msg);

    const char* what() const throw();

    ~InvalidDelayValue() throw() {}

  private:
    const char* m_message;
  };
}

#endif // COMPONENTEXCEPTIONS_H
