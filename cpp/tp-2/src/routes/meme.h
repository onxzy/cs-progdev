#ifndef ROUTE_MEME_H
#define ROUTE_MEME_H

#include <string>

#include "../route.h"

namespace http::router::route::meme {
  class FileNotFound : public std::exception {
    private:
      const std::string path;
    public:
      FileNotFound(const std::string& path);
      const char * what() const throw ();
  };

  class Meme : public Route {
    private:
      const std::string path = "meme.jpeg";

    public:
      virtual const bool matches(const http::request::Request& req) const override;
      virtual const http::response::Response& operator()(const http::request::Request& req) override;
  };
}

#endif
