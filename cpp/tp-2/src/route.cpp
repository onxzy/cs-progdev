#include <string>

#include "route.h"
#include "request.h"
#include "exception.h"

namespace http::router {

  const std::string Route::getRoute(const http::request::Request& req) const {
    const std::string route = req.getUrl().substr(0, req.getUrl().find('?'));
    return route;
  }

  const std::map<std::string,std::string> Route::getParams(const http::request::Request& req) const{

        std::string url = req.getUrl();
        size_t param_separator = url.find('?');
        if (param_separator==std::string::npos) throw http::exception::BadRequest("No parameter");
        if (param_separator==url.size()-1) throw http::exception::BadRequest("No parameter");

        std::string url_params = url.substr(url.find('?')+1,std::string::npos);
        std::map<std::string, std::string> params;

        while(url_params.size()){
            if (url_params.find('=')==std::string::npos) throw http::exception::BadRequest("Bad expression");
            size_t delimiter = url_params.find('=');

            std::string param_name = url_params.substr(0,delimiter);
            std::string param_value = url_params.substr(delimiter+1, url_params.find('&')-delimiter-1);

            params[param_name]=param_value;
            if (url_params.find('&')==url_params.size() -1) throw http::exception::BadRequest("Bad expression");
            if (url_params.find('&')==std::string::npos){
                url_params="";
            } else{
                url_params = url_params.substr(url_params.find('&')+1,std::string::npos);
            }
        }

        return params;
    }


}
