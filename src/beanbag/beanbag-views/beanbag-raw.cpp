/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <beanbag/raw.hpp>
#include <fost/exception/parse_error.hpp>
#include <fost/crypto>
#include "databases.hpp"


namespace {
    const class beanbag::raw_view c_raw_beanbag("beanbag.raw");
}


beanbag::raw_view::raw_view(const fostlib::string &name)
: view(name) {
}

std::pair<boost::shared_ptr<fostlib::mime>, int> beanbag::raw_view::operator () (
    const fostlib::json &options, const fostlib::string &pathname,
    fostlib::http::server::request &req, const fostlib::host &host
) const {
    fostlib::mime::mime_headers response_headers;
    fostlib::jsondb::local db(*beanbag::database(options["database"]));
    fostlib::string html(fostlib::utf::load_file(
        fostlib::coerce<boost::filesystem::wpath>(options["html"]["template"])));

    fostlib::split_type path = fostlib::split(pathname, "/");
    fostlib::json data_path; fostlib::jcursor position;
    for ( fostlib::split_type::const_iterator part(path.begin());
            part != path.end(); ++part ) {
        try {
            int index = fostlib::coerce<int>(*part);
            fostlib::push_back(data_path, index);
            position /= index;
        } catch ( fostlib::exceptions::parse_error& ) {
            fostlib::push_back(data_path, *part);
            position /= *part;
        }
    }

    if ( req.method() == "GET" ) {
        fostlib::json data(get(options, pathname, req, host, db, position));
        html = replaceAll(html, "[[data]]",
            fostlib::json::unparse(data, true));
        html = replaceAll(html, "[[path]]",
            fostlib::json::unparse(data_path, false));

        boost::shared_ptr<fostlib::mime> response(
                new fostlib::text_body(html,
                    response_headers, L"text/html" ));
        return std::make_pair(response, 200);
    } else if ( req.method() == "PUT" ) {
        fostlib::json data(put(options, pathname, req, host, db, position));
        boost::shared_ptr<fostlib::mime> response(
                new fostlib::text_body(
                    fostlib::json::unparse(data, true),
                    response_headers, L"application/json" ));
        return std::make_pair(response, 200);
    } else {
        boost::shared_ptr<fostlib::mime> response(
                new fostlib::text_body(
                    req.method() + " not supported",
                    response_headers, L"text/plain" ));
        return std::make_pair(response, 403);
    }
}


fostlib::string beanbag::raw_view::etag(const fostlib::json &structure) {
    fostlib::string json_string = fostlib::json::unparse(structure, false);
    return fostlib::md5(json_string);
}


fostlib::json beanbag::raw_view::get(
    const fostlib::json &, const fostlib::string &,
    fostlib::http::server::request &, const fostlib::host &,
    fostlib::jsondb::local &db, const fostlib::jcursor &position
) const {
    return db[position];
}


fostlib::json beanbag::raw_view::put(
    const fostlib::json &options, const fostlib::string &pathname,
    fostlib::http::server::request &req, const fostlib::host &host,
    fostlib::jsondb::local &db, const fostlib::jcursor &position
) const {
    boost::shared_ptr< fostlib::binary_body > data(req.data());
    fostlib::string json_string = fostlib::coerce<fostlib::string>(
        data->data());
    fostlib::json new_data = fostlib::json::parse(json_string);
    if ( db.has_key(position) )
        db.update(position, new_data);
    else
        db.insert(position, new_data);
    db.commit();
    return get(options, pathname, req, host, db, position);
}
