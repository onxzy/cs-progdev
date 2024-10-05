#include <string>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "request.h"
#include "exception.h"

namespace http::request {
  const Verb& Request::getVerb() const {
    return this->verb;
  }
  const std::string& Request::getUrl() const {
    return this->url;
  }
  const std::string& Request::getBody() const {
    return this->body;
  }

  Request::operator bool() const {
    return this->parsed;
  }

  std::ostream& operator<<(std::ostream& os, const Verb& verb) {
    switch (verb) {
      case GET: return os << "GET";
      case POST: return os << "POST";
      case PUT: return os << "PUT";
      case DELETE: return os << "DELETE";
      case HEAD: return os << "HEAD";
      case OPTION: return os << "OPTION";
      default: return os << "-";
    }
  }

  std::ostream& operator<<(std::ostream& os, const Request& req) {
    os << "[" << req.verb << "] " << req.url << std::endl;
  
    for (auto it: req.headers) {
      os << it.first << ": " << it.second << std::endl;
    }

    os << "---" << std::endl;
    os << req.body << std::endl;
    os << "---" << std::endl;

    return os;
  }

  std::istream& operator>>(std::istream& is, Request& req) {
    std::string line;
    enum Step {
      INIT = 0,
      HEADERS = 1,
      BODY = 2,
      DONE = 3,
    };

    int step = 0;
    while (step < Step::DONE) {
      if (!std::getline(is, line, '\n')) return is;
      boost::trim(line);
      
      if (line.size() == 0) {
        if (step == Step::HEADERS) {
          switch (req.verb) {
            case POST:
            case PUT:
              step +=1;
              break;
            default:
              step = DONE;
          }
        } else {
          step += 1;
        }
      }

      switch (step) {
        case INIT: {
          int delimiter = line.find(' ');
          std::string verb = line.substr(0, delimiter);
          line = line.substr(delimiter + 1); 
          boost::to_upper(verb);

          // VERB
          if (verb == "GET") req.verb = GET;
          else if (verb == "POST") req.verb = POST;
          else if (verb == "PUT") req.verb = PUT;
          else if (verb == "DELETE") req.verb = DELETE;
          else if (verb == "HEAD") req.verb = HEAD;
          else if (verb == "OPTION") req.verb = OPTION;
          else throw http::exception::BadRequest();

          // ROUTE
          delimiter = line.find(' ');
          req.url = line.substr(0, delimiter); 
          boost::trim(req.url);

          step += 1;
          break;
        }
          
        case HEADERS: {
          int delimiter = line.find(':');
          std::string header = line.substr(0, delimiter);
          std::string value = line.substr(delimiter + 2);
          boost::trim(header); boost::to_lower(header);
          boost::trim(value); boost::to_lower(value);
          if (header.size() > 0) req.headers.insert(std::pair{header, value});
          break;
        }

        case BODY: {
          req.body += std::move(line);
          break;
        }
        
        case DONE:                                        
          req.parsed = true;
        default:
          return is;
      }
    }

    return is;
  }
}

