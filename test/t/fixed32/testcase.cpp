
#include <testcase.hpp>
#include "testcase.pb.h"

int main(int c, char *argv[]) {
    TestFixed32::Test msg;

    msg.set_i(0);
    write_to_file(msg, "data-zero.pbf");

    msg.set_i(std::numeric_limits<uint32_t>::max());
    write_to_file(msg, "data-max-uint.pbf");

    msg.set_i(std::numeric_limits<uint32_t>::min());
    write_to_file(msg, "data-min-uint.pbf");
}

