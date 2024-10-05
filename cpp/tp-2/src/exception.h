#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace http::exception {
  class BadRequest : public std::exception {
    private:
      const std::string message;

    public:
      BadRequest(const std::string& message = "");
      const char * what() const throw ();
  };

  class NotFound : public std::exception {
    private:
      const std::string message;

    public:
      NotFound(const std::string& message = "");
      const char * what() const throw ();
  };
}

#endif