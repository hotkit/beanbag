/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/urlhandler>
#include "databases.hpp"


const class beanbag_raw : public fostlib::urlhandler::view {
    public:
        beanbag_raw()
        : view("beanbag.raw") {
        }

        std::pair<boost::shared_ptr<fostlib::mime>, int> operator () (
            const fostlib::json &options, const fostlib::string &path,
            fostlib::http::server::request &req,
            const fostlib::host &
        ) const {
            fostlib::jsondb::local db(*beanbag::database(options["database"]));
            fostlib::string html(fostlib::utf::load_file(
            fostlib::coerce<boost::filesystem::wpath>(options["html"]["template"])));

            boost::shared_ptr<fostlib::mime> response(
                    new fostlib::text_body(
                        replaceAll(html, "[[json]]", fostlib::json::unparse(db[fostlib::jcursor()], true)),
                        fostlib::mime::mime_headers(), L"text/html" ));
            return std::make_pair(response, 200);
        }
} c_beanbag_raw;
