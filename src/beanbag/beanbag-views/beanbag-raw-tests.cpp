/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/test>
#include "databases.hpp"
#include <beanbag/beanbag>


FSL_TEST_SUITE(beanbag_raw);


namespace {
    struct setup {
        setup()
        : view("beanbag.test"), status(0) {
            fostlib::insert(options, "database", "beanbag.test");
            fostlib::insert(options, "html", "template",
                "../../usr/share/beanbag/raw/template.html");
        }

        const beanbag::raw_view view;
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


FSL_TEST_FUNCTION(get_non_existent_path_returns_404) {
    setup env;
    env.headers.set("Accept", "application/json");
    env.do_request("GET", "/not/a/path/");
    FSL_CHECK_EQ(env.status, 404);
    FSL_CHECK_EQ(
        env.response->headers()["Content-Type"].value(),
        "text/html");
    FSL_CHECK(
        fostlib::coerce<fostlib::string>(*env.response).find(
            "Resource not found") != fostlib::string::npos);
}


FSL_TEST_FUNCTION(get_with_path_gives_200) {
    setup env;
    env.headers.set("Accept", "application/json");
    fostlib::insert(env.database, "is", "a", "path", true);
    env.do_request("GET", "/is/a/path/");
    FSL_CHECK_EQ(env.status, 200);
    FSL_CHECK_EQ("true\n",
        fostlib::coerce<fostlib::string>(*env.response));
}


FSL_TEST_FUNCTION(get_html_has_etag) {
    setup env;
    env.do_request("GET", "/");
    FSL_CHECK_EQ(env.status, 200);
    FSL_CHECK_EQ(
        env.response->headers()["Content-Type"].value(),
        "text/html");
    FSL_CHECK(env.response->headers().exists("ETag"));
}


FSL_TEST_FUNCTION(get_json_has_etag) {
    setup env;
    env.headers.set("Accept", "application/json");
    env.do_request("GET", "/");
    FSL_CHECK_EQ(env.status, 200);
    FSL_CHECK_EQ(
        env.response->headers()["Content-Type"].value(),
        "application/json");
    FSL_CHECK(env.response->headers().exists("ETag"));
    FSL_CHECK_EQ(
        env.response->headers()["ETag"].value(),
        "\"37a6259cc0c1dae299a7866489dff0bd\"");
}


FSL_TEST_FUNCTION(put_to_new_path) {
    setup put;
    put.headers.set("Accept", "application/json");
    put.do_request("PUT", "/new/path/3/", "null");
    FSL_CHECK_EQ(put.status, 201);
    FSL_CHECK_EQ(
        put.response->headers()["Content-Type"].value(),
        "application/json");
    FSL_CHECK(put.response->headers().exists("ETag"));
}


FSL_TEST_FUNCTION(conditional_put_matches) {
    setup put;
    put.headers.set("Accept", "application/json");
    put.headers.set("If-Match", "\"37a6259cc0c1dae299a7866489dff0bd\"");
    put.do_request("PUT", "/", "[]");
    FSL_CHECK_EQ(put.status, 201);
    FSL_CHECK_EQ(
        put.response->headers()["Content-Type"].value(),
        "application/json");
}


FSL_TEST_FUNCTION(conditional_put_does_not_match) {
    setup put;
    put.headers.set("Accept", "application/json");
    put.headers.set("If-Match", "\"invalid-etag-value\"");
    put.do_request("PUT", "/", "[]");
    FSL_CHECK_EQ(put.status, 412);
    FSL_CHECK_EQ(
        put.response->headers()["Content-Type"].value(),
        "text/html");
}


FSL_TEST_FUNCTION(conditional_put_matches_wildcard) {
    setup put;
    fostlib::insert(put.database, "path", fostlib::json());
    put.headers.set("Accept", "application/json");
    put.headers.set("If-Match", "*");
    put.do_request("PUT", "/path/", "[]");
    FSL_CHECK_EQ(put.status, 200);
    FSL_CHECK_EQ(
        put.response->headers()["Content-Type"].value(),
        "application/json");
}


FSL_TEST_FUNCTION(conditional_put_does_not_match_wildcard) {
    setup put;
    put.headers.set("Accept", "application/json");
    put.headers.set("If-Match", "*");
    put.do_request("PUT", "/path/", "[]");
    FSL_CHECK_EQ(put.status, 412);
    FSL_CHECK_EQ(
        put.response->headers()["Content-Type"].value(),
        "text/html");
}

