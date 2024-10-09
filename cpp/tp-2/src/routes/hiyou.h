#ifndef HIYOU_H
#define HIYOU_H

#include <string>
#include <map>
#include "../route.h"
#include "../request.h"

namespace http::router::route::hiyou{

    class Hiyou : public router::Route{        
        public:
            virtual const bool matches(const http::request::Request& req) const override;
            virtual const http::response::Response& operator()(const http::request::Request& req) override;
    
    };

}


#endif