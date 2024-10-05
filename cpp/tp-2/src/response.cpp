#include <vector>

#include "response.h"

namespace http::response {
  Response::Response(int status)
    : status(status), statusText(std::to_string(status)) {}

  Response::Response(int status, const std::string& statusText) 
    : status(status), statusText(statusText) {}

  const int Response::getStatus() const {
    return this->status;
  }

  void Response::setHeader(const std::string& key, const std::string& value) {
    // TODO: Headers blacklist
    this->headers.insert(std::pair(key, value));
  }
  void Response::deleteHeader(const std::string& key) {
    // TODO: Headers blacklist
    this->headers.erase(key);
  }
  void Response::setBody(std::vector<char>&& body) {
    this->body = std::move(body);
  }
  void Response::setBody(const std::string& body) {
    this->body = std::vector<char>(body.begin(), body.end());
  }

  std::ostream& operator<<(std::ostream& os, const Response& res) {
    os
      << "HTTP/1.0 " << res.status << " " << res.statusText << std::endl
      << "Connection: close" << std::endl
      << "Server: Thomas" << std::endl
      << "Content-Length: " << res.body.size() << std::endl;

    for (auto it: res.headers) {
      os << it.first << ": " << it.second << std::endl;
    }

    os << std::endl;
    for (auto it: res.body) os << it;
    os << std::endl;

    return os;
  }
}

