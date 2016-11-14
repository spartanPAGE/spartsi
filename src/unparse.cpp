#include "unparse.h"
#include "boost/algorithm/string.hpp"

//TODO: customizable whitespace length & type
namespace spartsi {

    template<typename F>
    lines split_to_lines_and_transform(std::string const &val, std::string const &splitters, F f) {
        lines result;
        boost::split(result, val, boost::is_any_of(splitters));
        for(auto &line: result) {
            f(line);
        }
        return result;
    }

    lines unparse_attribute_value(std::string const &val) {
        return split_to_lines_and_transform(val, "\n", [](std::string &line) {
            line = "\"" + line + "\"";
        });
    }

    lines unparse_comment(std::string const &val) {
        return split_to_lines_and_transform(val, "\n", [](std::string &line) {
            auto trimmed = boost::algorithm::trim_copy(line);
            line = trimmed.empty()? "::" : ":: " + trimmed;
        });
    }

    lines unparse(spartsi::attribute const &attribute) {
        return {};
    }

    lines unparse(spartsi::tree const &tree) {
        return {};
    }
}