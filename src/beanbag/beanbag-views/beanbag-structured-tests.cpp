/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/test>
#include "databases.hpp"
#include <beanbag/beanbag>


FSL_TEST_SUITE(beanbag_structured);


namespace {
    struct setup {
        setup()
        : view("beanbag.test"), status(0) {
            fostlib::insert(options, "database", "beanbag.test");
            fostlib::insert(options, "html", "template",
                "../../usr/share/beanbag/raw/template.html");
        }

        const beanbag::structured_view view;
        fostlib::mime::mime_headers headers;
        fostlib::json database, options;
        fostlib::host host;
        int status;
        boost::shared_ptr<fostlib::mime> response;

        void do_request(
                const fostlib::string &method,
                const fostlib::string &pathname,
                const fostlib::string &body_data = fostlib::string() ) {
            beanbag::test_database("beanbag.test", database);
            std::auto_ptr< fostlib::binary_body > body(
                new fostlib::binary_body(
                    fostlib::coerce< std::vector<unsigned char> >(
                        fostlib::coerce<fostlib::utf8_string>(body_data)),
                    headers));
            fostlib::http::server::request req(
                method, fostlib::coerce<fostlib::url::filepath_string>(pathname), body);
            std::pair<boost::shared_ptr<fostlib::mime>, int> res =
                view(options, pathname, req, host);
            response = res.first;
            status = res.second;
        }
    };
}

