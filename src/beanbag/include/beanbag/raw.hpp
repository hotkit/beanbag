/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once
#ifndef BEANBAG_RAW_HPP
#define BEANBAG_RAW_HPP


#include <fost/urlhandler>


namespace beanbag {


    class raw_view : public fostlib::urlhandler::view {
    public:
        /// Construct a raw view giving it the provided name
        raw_view(const fostlib::string &name);

        /// The standard view implementation operator
        std::pair<boost::shared_ptr<fostlib::mime>, int> operator () (
            const fostlib::json &options, const fostlib::string &pathname,
            fostlib::http::server::request &req,
            const fostlib::host &
        ) const;

    };


}


#endif // BEANBAG_RAW_HPP
