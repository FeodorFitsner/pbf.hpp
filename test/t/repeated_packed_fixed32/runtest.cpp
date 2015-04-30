
#include <test.hpp>

TEST_CASE("repeated_packed_fixed32") {

    SECTION("empty") {
        std::string buffer = get_file_data("test/t/repeated_packed_fixed32/data-empty.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(!item.next());
    }

    SECTION("one") {
        std::string buffer = get_file_data("test/t/repeated_packed_fixed32/data-one.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        auto it_pair = item.packed_fixed32();
        REQUIRE(!item.next());

        REQUIRE(*it_pair.first == 17l);
        REQUIRE(++it_pair.first == it_pair.second);
    }

    SECTION("many") {
        std::string buffer = get_file_data("test/t/repeated_packed_fixed32/data-many.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        auto it_pair = item.packed_fixed32();
        REQUIRE(!item.next());

        auto it = it_pair.first;
        REQUIRE(*it++ == 17l);
        REQUIRE(*it++ == 0l);
        REQUIRE(*it++ == 1l);
        REQUIRE(*it++ == std::numeric_limits<int32_t>::max());
        REQUIRE(it == it_pair.second);
    }

    SECTION("end_of_buffer") {
        std::string buffer = get_file_data("test/t/repeated_packed_fixed32/data-many.pbf");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.packed_fixed32(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

}

