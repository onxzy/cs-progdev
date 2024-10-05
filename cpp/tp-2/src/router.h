#ifndef ROUTER_H
#define ROUTER_H

#include <memory>
#include <vector>

#include "route.h"
#include "response.h"
#include "request.h"

namespace http::router {

  using namespace http;

  class Router {
    private:
      std::vector<std::unique_ptr<router::Route>> routes;

    public:
      void addRoute(std::unique_ptr<Route>&& route);
      const int nbRoutes() const;
      const response::Response& serveRequest(const request::Request& req) const;
  };
}

#endif
