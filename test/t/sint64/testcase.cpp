
#include <testcase.hpp>
#include "testcase.pb.h"

int main(int c, char *argv[]) {
    TestSInt64::Test msg;

    msg.set_i(0LL);
    write_to_file(msg, "data-zero.pbf");

    msg.set_i(1LL);
    write_to_file(msg, "data-pos.pbf");

    msg.set_i(-1LL);
    write_to_file(msg, "data-neg.pbf");

    msg.set_i(std::numeric_limits<int64_t>::max());
    write_to_file(msg, "data-max.pbf");

    msg.set_i(std::numeric_limits<int64_t>::min());
    write_to_file(msg, "data-min.pbf");
}

