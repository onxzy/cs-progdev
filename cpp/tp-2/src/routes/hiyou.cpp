#include "hiyou.h"
#include "../exception.h"
#include <map>

namespace http::router::route::hiyou{

    const bool Hiyou::matches(const http::request::Request& req) const {
        std::string url = req.getUrl();
        return req.getVerb() == request::Verb::GET && (url.substr(0, url.find('?')).compare("/hiyou")==0);
    }

    const http::response::Response& Hiyou::operator()(const http::request::Request& req){
        

        std::map<std::string,std::string> params = this->getParams(req);
        

        if (params.size()>1) throw http::exception::BadRequest("Too many parameters");
        std::string name;
        for (auto const& it : params){
            if (!it.first.compare("name")){
                name=it.second;
            }
            else{
                throw http::exception::BadRequest("Bad parameter");
            }
        }
        
        http::response::Response* res = new http::response::Response(200,"OK");
        res->setBody("Hi "+name+" !");
        return *res;
    }
}