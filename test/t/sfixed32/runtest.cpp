
#include <test.hpp>

TEST_CASE("read sfixed32 field") {

    SECTION("zero") {
        std::string buffer = load_data("sfixed32/data-zero");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_sfixed32() == 0L);
        REQUIRE(!item.next());
    }

    SECTION("max-int") {
        std::string buffer = load_data("sfixed32/data-max-int");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_sfixed32() == std::numeric_limits<int32_t>::max());
        REQUIRE(!item.next());
    }

    SECTION("min-int") {
        std::string buffer = load_data("sfixed32/data-min-int");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_sfixed32() == std::numeric_limits<int32_t>::min());
        REQUIRE(!item.next());
    }

    SECTION("end_of_buffer") {
        std::string buffer = load_data("sfixed32/data-min-int");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.get_sfixed32(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

}

TEST_CASE("write sfixed32 field") {

    std::string buffer;
    mapbox::util::pbf_writer pw(buffer);

    SECTION("zero") {
        pw.add_sfixed32(1, 0);
        REQUIRE(buffer == load_data("sfixed32/data-zero"));
    }

    SECTION("max-uint") {
        pw.add_sfixed32(1, std::numeric_limits<int32_t>::max());
        REQUIRE(buffer == load_data("sfixed32/data-max-int"));
    }

    SECTION("min-uint") {
        pw.add_sfixed32(1, std::numeric_limits<int32_t>::min());
        REQUIRE(buffer == load_data("sfixed32/data-min-int"));
    }

}

