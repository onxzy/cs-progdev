#ifndef SUM_H
#define SUM_H

#include <string>
#include <map>
#include "../route.h"
#include "../request.h"

namespace http::router::route::sum{

    class Sum : public Route{        
        public:
            virtual const bool matches(const http::request::Request& req) const override;
            virtual const http::response::Response& operator()(const http::request::Request& req) override;
    
    };

}


#endif