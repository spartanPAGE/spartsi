#include "unparse.h"
#include "boost/algorithm/string.hpp"

//TODO: customizable whitespace length & type
namespace spartsi {

    lines unparse_attribute_value(std::string const &val) {
        lines result;
        boost::split(result, val, boost::is_any_of("\r\n"));
        for(auto &line: result) {
            line = "\"" + line + "\"";
        }
        return result;
    }

    lines unparse(spartsi::attribute const &attribute) {
        return {};
    }

    lines unparse(spartsi::tree const &tree) {
        return {};
    }
}