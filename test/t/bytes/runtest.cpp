
#include <test.hpp>

TEST_CASE("read bytes field") {

    SECTION("empty") {
        std::string buffer = load_data("bytes/data-empty");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "");
        REQUIRE(!item.next());
    }

    SECTION("one") {
        std::string buffer = load_data("bytes/data-one");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "x");
        REQUIRE(!item.next());
    }

    SECTION("string") {
        std::string buffer = load_data("bytes/data-string");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "foobar");
        REQUIRE(!item.next());
    }

    SECTION("binary") {
        std::string buffer = load_data("bytes/data-binary");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        std::string data = item.get_string();
        REQUIRE(data.size() == 3);
        REQUIRE(data[0] == char(1));
        REQUIRE(data[1] == char(2));
        REQUIRE(data[2] == char(3));
        REQUIRE(!item.next());
    }

    SECTION("end_of_buffer") {
        std::string buffer = load_data("bytes/data-binary");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.get_string(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

}

TEST_CASE("write bytes field") {

    std::string buffer;
    mapbox::util::pbf_writer pw(buffer);

    SECTION("empty") {
        pw.add_string(1, "");
        REQUIRE(buffer == load_data("bytes/data-empty"));
    }

    SECTION("one") {
        pw.add_string(1, "x");
        REQUIRE(buffer == load_data("bytes/data-one"));
    }

    SECTION("string") {
        pw.add_string(1, "foobar");
        REQUIRE(buffer == load_data("bytes/data-string"));
    }

    SECTION("binary") {
        std::string data;
        data.append(1, char(1));
        data.append(1, char(2));
        data.append(1, char(3));

        pw.add_string(1, data);

        REQUIRE(buffer == load_data("bytes/data-binary"));
    }

}

