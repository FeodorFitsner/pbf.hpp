
#include <testcase.hpp>
#include "testcase.pb.h"

int main(int c, char *argv[]) {
    TestSFixed32::Test msg;

    msg.set_i(0);
    write_to_file(msg, "data-zero.pbf");

    msg.set_i(std::numeric_limits<int32_t>::max());
    write_to_file(msg, "data-max-int.pbf");

    msg.set_i(std::numeric_limits<int32_t>::min());
    write_to_file(msg, "data-min-int.pbf");
}

