#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "meme.h"

namespace http::router::route::meme {
  using namespace http;

  FileNotFound::FileNotFound(const std::string& path) 
   : path(path) {}

  const char * FileNotFound::what() const throw () {
    return ("FileNotFound : " + this->path).c_str();
  }

  const bool Meme::matches(const request::Request& req) const {
    return req.getVerb() == request::Verb::GET && this->getRoute(req).compare("/meme") == 0;
  }

  const response::Response& Meme::operator()(const request::Request& req) {
    response::Response* res = new response::Response(200, "OK");

    std::ifstream file(this->path, std::ifstream::binary);
    if (!file) throw FileNotFound(this->path);

    std::vector<char> file_data;

    // Prevents skipping these whitespace characters, treating them as part of the input.
    file >> std::noskipws;

    std::copy(
      std::istream_iterator<char>(file),
      std::istream_iterator<char>(),
      std::back_inserter(file_data)
    );

    // std::cout << file_data.size() << std::endl;

    res->setBody(std::move(file_data));
    res->setHeader("Content-Type", "image/jpeg");
    return *res;
  }
}
