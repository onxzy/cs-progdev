#include <string>

#include "route.h"
#include "request.h"

namespace http::router {

  const std::string& Route::getRoute(const http::request::Request& req) const {
    const std::string& route = req.getUrl().substr(0, req.getUrl().find('?'));
    return route;
  }

}
