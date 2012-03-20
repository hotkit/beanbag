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


fostlib::jcursor beanbag::structured_view::relocated(
        fostlib::jsondb::local &db, fostlib::jcursor location) const {
    if ( db.has_key(location/ 0) )
        location /= 0;
    else
        location /= "";
    return location;
}


std::pair<fostlib::json, int> beanbag::structured_view::get(
    const fostlib::json &, const fostlib::string &,
    fostlib::http::server::request &, const fostlib::host &,
    fostlib::jsondb::local &db, const fostlib::jcursor &position
) const {
    fostlib::jcursor location = relocated(db, position);

    if ( db.has_key(location) )
        return std::make_pair(db[location], 200);
    else
        return std::make_pair(fostlib::json(), 404);
}

int beanbag::structured_view::put(
    const fostlib::json &options, const fostlib::string &pathname,
    fostlib::http::server::request &req, const fostlib::host &host,
    fostlib::jsondb::local &db, const fostlib::jcursor &position
) const {
    return raw_view::put(options, pathname, req, host, db,
        relocated(db, position));
}

int beanbag::structured_view::del(
    const fostlib::json &options, const fostlib::string &pathname,
    fostlib::http::server::request &req, const fostlib::host &host,
    fostlib::jsondb::local &db, const fostlib::jcursor &position
) const {
    fostlib::jcursor location = relocated(db, position);
    int status = raw_view::del(options, pathname, req, host, db, location);
    if ( status == 410 && db[position] == fostlib::json(fostlib::json::object_t()) ) {
        db.remove(position);
        db.commit();
    }
    return status;
}
