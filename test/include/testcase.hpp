#ifndef TESTCASE_HPP
#define TESTCASE_HPP

#include <cassert>
#include <string>
#include <fstream>
#include <limits>

template <class T>
std::string write_to_file(const T& msg, const char* filename) {
    std::string out;

    msg.SerializeToString(&out);
    std::ofstream d(filename);
    assert(d.is_open());
    d << out;

    return out;
}

#endif // TESTCASE_HPP
