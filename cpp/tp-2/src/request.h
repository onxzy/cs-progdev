#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>

namespace http::request {
  enum Verb {
    GET = 1,
    POST = 2,
    PUT = 3,
    DELETE = 4,
    HEAD = 5,
    OPTION = 6
  };

  std::ostream& operator<<(std::ostream& os, const Verb& verb);

  class Request {
    private:
      bool parsed = false;
      Verb verb;
      std::string url;
      std::map<std::string, std::string> headers;
      std::string body;

    public:
      const Verb& getVerb() const;
      const std::string& getUrl() const;
      const std::string& getBody() const;

      friend std::ostream& operator<<(std::ostream& os, const Request& req);
      friend std::istream& operator>>(std::istream& is, Request& req);
      operator bool() const;
  };

}


#endif
