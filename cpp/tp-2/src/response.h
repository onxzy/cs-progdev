#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace http::response {
  class Response {
    private:
      const int status;
      const std::string statusText;
      std::map<std::string, std::string> headers;
      std::vector<char> body;

    public:
      Response() = delete;
      Response(int status);
      Response(int status, const std::string& statusText);

      const int getStatus() const;

      void setHeader(const std::string& key, const std::string& value);
      void deleteHeader(const std::string& key);
      void setBody(std::vector<char>&& body);
      void setBody(const std::string& body);

      friend std::ostream& operator<<(std::ostream& os, const Response& res);
  };
}

#endif
