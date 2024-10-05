#ifndef ROUTE_HELLOWORLD_H
#define ROUTE_HELLOWORLD_H

#include "../route.h"

namespace http::router::route::helloWorld {
  class HelloWorld : public Route {
    public:
      virtual const bool matches(const http::request::Request& req) const override;
      virtual const http::response::Response& operator()(const http::request::Request& req) override;
  };
}

#endif
