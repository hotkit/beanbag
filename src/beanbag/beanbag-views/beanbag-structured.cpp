/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <beanbag/structured.hpp>


namespace {
    const beanbag::structured_view c_view("beanbag.structured");
}


beanbag::structured_view::structured_view(const fostlib::string &name)
: raw_view(name) {
}


fostlib::jcursor beanbag::structured_view::position(
        const fostlib::string &pathname, fostlib::jsondb::local &db) const {
    fostlib::jcursor location = raw_view::position(pathname, db);
    if ( db.has_key(location / "") )
        location /= "";
    else if ( db.has_key(location/ 0) )
        location /= 0;
    return location;
}

