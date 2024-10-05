#include <memory>

#include "router.h"
#include "exception.h"

namespace http::router {
  using namespace http;

  void Router::addRoute(std::unique_ptr<Route>&& route) {
    this->routes.push_back(std::move(route));
  }

  const int Router::nbRoutes() const {
    return this->routes.size();
  }

  const response::Response& Router::serveRequest(const request::Request& req) const {
    for (auto const& route: this->routes)
      if (route->matches(req)) return (*route)(req);
    throw exception::NotFound(req.getUrl());
  }
}
