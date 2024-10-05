#ifndef ROUTE_H
#define ROUTE_H

#include "request.h"
#include "response.h"

namespace http::router {
  class Route {
    protected:
      const std::string& getRoute(const http::request::Request& req) const;
    public:
      virtual const bool matches(const http::request::Request& req) const = 0;
      virtual const http::response::Response& operator()(const http::request::Request& req) = 0;
  };
}

#endif

