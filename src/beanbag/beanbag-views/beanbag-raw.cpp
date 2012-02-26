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
            const fostlib::json &options, const fostlib::string &pathname,
            fostlib::http::server::request &req,
            const fostlib::host &
        ) const {
            fostlib::jsondb::local db(*beanbag::database(options["database"]));
            fostlib::string html(fostlib::utf::load_file(
                fostlib::coerce<boost::filesystem::wpath>(options["html"]["template"])));

            fostlib::split_type path = fostlib::split(pathname, "/");
            fostlib::json data_path; fostlib::jcursor position;
            for ( fostlib::split_type::const_iterator part(path.begin());
                    part != path.end(); ++part ) {
                fostlib::push_back(data_path, *part);
            }

            if ( req.method() == "GET" ) {
                html = replaceAll(html, "[[data]]",
                    fostlib::json::unparse(db[fostlib::jcursor()], true));
                html = replaceAll(html, "[[path]]",
                    fostlib::json::unparse(data_path, false));

                boost::shared_ptr<fostlib::mime> response(
                        new fostlib::text_body(
                            html,
                            fostlib::mime::mime_headers(), L"text/html" ));
                return std::make_pair(response, 200);
            } else if ( req.method() == "PUT" ) {
                boost::shared_ptr< fostlib::binary_body > data(req.data());
                fostlib::string json_string = fostlib::coerce<fostlib::string>(
                    data->data());
                fostlib::json new_data = fostlib::json::parse(json_string);
                db.update(fostlib::jcursor(), new_data);
                db.commit();
                boost::shared_ptr<fostlib::mime> response(
                        new fostlib::text_body(
                            fostlib::json::unparse(db[fostlib::jcursor()], true),
                            fostlib::mime::mime_headers(), L"application/json" ));
                return std::make_pair(response, 200);
            } else {
                boost::shared_ptr<fostlib::mime> response(
                        new fostlib::text_body(
                            req.method() + " not supported",
                            fostlib::mime::mime_headers(), L"text/plain" ));
                return std::make_pair(response, 403);
            }
        }
} c_beanbag_raw;
