#include <exception>
#include <string>

#include "exception.h"

namespace http::exception {
  BadRequest::BadRequest(const std::string& message)
    : exception(), message(message) {}

  const char * BadRequest::what() const throw () {
    return this->message.c_str();
  }

  NotFound::NotFound(const std::string& message)
    : exception(), message(message) {}

  const char * NotFound::what() const throw () {
    return this->message.c_str();
  }
}
