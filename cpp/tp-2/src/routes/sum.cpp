#include "sum.h"
#include "../exception.h"
#include <stdio.h>

namespace http::router::route::sum{

    const bool Sum::matches(const http::request::Request& req) const {
        std::string url = req.getUrl();
        return req.getVerb() == request::Verb::GET && (url.substr(0, url.find('?')).compare("/sum")==0);
    }

    const http::response::Response& Sum::operator()(const http::request::Request& req){

        std::map<std::string,std::string> params = this->getParams(req);

        if (params.size()>2) throw http::exception::BadRequest("Too many parameters");
        if (params.size()<2) throw http::exception::BadRequest("Two parameters needed");
        std::string x,y;
        int sum;

        for (auto const& it : params){
            if (!it.first.compare("x")){
                x= it.second;
            } else if (!it.first.compare("y")){
                y= it.second;
            }
            else{
                throw http::exception::BadRequest("Bad parameter");
            }
        }

        int x0,y0;
        try{
            x0 = stoi(x);
            y0 = stoi(y);

        } catch(const std::invalid_argument& e){
            throw http::exception::BadRequest("Not an integer");
        } catch(const std::out_of_range& e){
            throw http::exception::BadRequest("Out ouf range");
        } 

        http::response::Response* res = new http::response::Response(200,"OK");
        char buffer[255];
        snprintf(buffer,255,"%d + %d = %d",x0,y0, x0+y0 );
        res->setBody(buffer);
        return *res;
    }
}