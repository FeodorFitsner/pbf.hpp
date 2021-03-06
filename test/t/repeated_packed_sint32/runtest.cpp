
#include <test.hpp>

TEST_CASE("read repeated packed sint32 field") {

    SECTION("empty") {
        std::string buffer = load_data("repeated_packed_sint32/data-empty");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(!item.next());
    }

    SECTION("one") {
        std::string buffer = load_data("repeated_packed_sint32/data-one");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        auto it_pair = item.packed_sint32();
        REQUIRE(!item.next());

        REQUIRE(*it_pair.first == 17L);
        REQUIRE(++it_pair.first == it_pair.second);
    }

    SECTION("many") {
        std::string buffer = load_data("repeated_packed_sint32/data-many");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        auto it_pair = item.packed_sint32();
        REQUIRE(!item.next());

        auto it = it_pair.first;
        REQUIRE(*it++ == 17L);
        REQUIRE(*it++ ==  0L);
        REQUIRE(*it++ ==  1L);
        REQUIRE(*it++ == -1L);
        REQUIRE(*it++ == std::numeric_limits<int32_t>::max());
        REQUIRE(*it++ == std::numeric_limits<int32_t>::min());
        REQUIRE(it == it_pair.second);
    }

    SECTION("end_of_buffer") {
        std::string buffer = load_data("repeated_packed_sint32/data-many");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.packed_sint32(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

}

TEST_CASE("write repeated packed sint32 field") {

    std::string buffer;
    mapbox::util::pbf_writer pw(buffer);

    SECTION("empty") {
        const int32_t* dummy = 0;
        pw.add_packed_sint32(1, dummy, dummy);

        REQUIRE(buffer == load_data("repeated_packed_sint32/data-empty"));
    }

    SECTION("one") {
        int32_t data[] = { 17L };
        pw.add_packed_sint32(1, std::begin(data), std::end(data));

        REQUIRE(buffer == load_data("repeated_packed_sint32/data-one"));
    }

    SECTION("many") {
        int32_t data[] = { 17L, 0L, 1L, -1L, std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::min() };
        pw.add_packed_sint32(1, std::begin(data), std::end(data));

        REQUIRE(buffer == load_data("repeated_packed_sint32/data-many"));
    }

}

