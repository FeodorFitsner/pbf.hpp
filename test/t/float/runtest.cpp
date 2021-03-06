
#include <test.hpp>

TEST_CASE("read float field") {

    SECTION("zero") {
        std::string buffer = load_data("float/data-zero");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_float() == Approx(0.0f));
        REQUIRE(!item.next());
    }

    SECTION("positive") {
        std::string buffer = load_data("float/data-pos");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_float() == Approx(5.34f));
        REQUIRE(!item.next());
    }

    SECTION("negative") {
        std::string buffer = load_data("float/data-neg");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_float() == Approx(-1.71f));
        REQUIRE(!item.next());
    }

    SECTION("end_of_buffer") {
        std::string buffer = load_data("float/data-neg");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.get_float(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

}

TEST_CASE("write float field") {

    std::string buffer;
    mapbox::util::pbf_writer pw(buffer);

    SECTION("zero") {
        pw.add_float(1, 0.0f);
        REQUIRE(buffer == load_data("float/data-zero"));
    }

    SECTION("positive") {
        pw.add_float(1, 5.34f);
        REQUIRE(buffer == load_data("float/data-pos"));
    }

    SECTION("negative") {
        pw.add_float(1, -1.71f);
        REQUIRE(buffer == load_data("float/data-neg"));
    }

}

