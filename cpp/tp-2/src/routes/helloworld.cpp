#include "helloworld.h"

namespace http::router::route::helloWorld {
  using namespace http;

  const bool HelloWorld::matches(const request::Request& req) const {
    return this->getRoute(req).compare("/") == 0;
  }

  const response::Response& HelloWorld::operator()(const request::Request& req) {
    response::Response* res = new response::Response(200, "OK");
    res->setBody("Hello world !\n");
    return *res;
  }
}
