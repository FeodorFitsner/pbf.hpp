
#include <test.hpp>

TEST_CASE("skip") {

    SECTION("check that skip() skips the right amount of bytes") {

        // These are all the data files which contain exactly one field.
        //
        // Create this list with:
        //   cd test/t
        //   find . -name data\*pbf -not -empty | sed -e 's/^.\/\(.*\).pbf/"\1",/'
        // and then remove everything manually that contains more than one
        // field.
        std::vector<std::string> filenames = {
            "bool/data-also-true",
            "bool/data-false",
            "bool/data-still-true",
            "bool/data-true",
            "bytes/data-binary",
            "bytes/data-empty",
            "bytes/data-one",
            "bytes/data-string",
            "double/data-neg",
            "double/data-pos",
            "double/data-zero",
            "enum/data-black",
            "enum/data-blue",
            "fixed32/data-max-uint",
            "fixed32/data-min-uint",
            "fixed32/data-zero",
            "fixed64/data-max-uint",
            "fixed64/data-min-uint",
            "fixed64/data-zero",
            "float/data-neg",
            "float/data-pos",
            "float/data-zero",
            "int32/data-max",
            "int32/data-min",
            "int32/data-neg",
            "int32/data-pos",
            "int32/data-zero",
            "int64/data-max",
            "int64/data-min",
            "int64/data-neg",
            "int64/data-pos",
            "int64/data-zero",
            "message/data-message",
            "repeated/data-one",
            "repeated_packed_fixed32/data-many",
            "repeated_packed_fixed32/data-one",
            "repeated_packed_fixed64/data-many",
            "repeated_packed_fixed64/data-one",
            "repeated_packed_int32/data-many",
            "repeated_packed_int32/data-one",
            "repeated_packed_int64/data-many",
            "repeated_packed_int64/data-one",
            "repeated_packed_sfixed32/data-many",
            "repeated_packed_sfixed32/data-one",
            "repeated_packed_sfixed64/data-many",
            "repeated_packed_sfixed64/data-one",
            "repeated_packed_sint32/data-many",
            "repeated_packed_sint32/data-one",
            "repeated_packed_sint64/data-many",
            "repeated_packed_sint64/data-one",
            "repeated_packed_uint32/data-many",
            "repeated_packed_uint32/data-one",
            "repeated_packed_uint64/data-many",
            "repeated_packed_uint64/data-one",
            "sfixed32/data-max-int",
            "sfixed32/data-min-int",
            "sfixed32/data-zero",
            "sfixed64/data-max-int",
            "sfixed64/data-min-int",
            "sfixed64/data-zero",
            "sint32/data-max",
            "sint32/data-min",
            "sint32/data-neg",
            "sint32/data-pos",
            "sint32/data-zero",
            "sint64/data-max",
            "sint64/data-min",
            "sint64/data-neg",
            "sint64/data-pos",
            "sint64/data-zero",
            "string/data-empty",
            "string/data-one",
            "string/data-string",
            "tags/data-tag-1",
            "tags/data-tag-200000",
            "tags/data-tag-200",
            "tags/data-tag-max",
            "uint32/data-max",
            "uint32/data-pos",
            "uint32/data-zero",
            "uint64/data-max",
            "uint64/data-pos",
            "uint64/data-zero",
        };

        for (const auto& filename : filenames) {
            std::string buffer = load_data(filename);

            mapbox::util::pbf item(buffer.data(), buffer.size());

            REQUIRE(item.next());
            item.skip();
            REQUIRE(!item);
        }

    }

    SECTION("check that skip() throws on unknown field type") {
        std::string buffer;

        mapbox::util::pbf_writer pw(buffer);
        pw.add_fixed32(1, 123);

        buffer[0] += 1; // hack to create illegal field type

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE_THROWS_AS(item.skip(), mapbox::util::pbf::unknown_field_type_exception);
    }

    SECTION("check that skip() throws on short buffer") {
        std::string buffer;

        mapbox::util::pbf_writer pw(buffer);
        pw.add_fixed32(1, 123);

        buffer.resize(buffer.size() - 1); // "remove" last byte from buffer
        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE_THROWS_AS(item.skip(), mapbox::util::pbf::end_of_buffer_exception);
    }

}

