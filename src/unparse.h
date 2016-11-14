#pragma once
#include <string>
#include <vector>
#include "elementary_types.h"

namespace spartsi {
    using lines = std::vector<std::string>;

    namespace unparsed {
        using declaration = lines;
        using definition = lines;

        using pair = std::pair<declaration, definition>;
    }

    template<typename It>
    void indent(It first, It last, size_t no) {
        std::for_each(first, last, [no](std::string &line) {
            line = std::string(no, ' ') + line;
        });
    }

    lines unparse_attribute_value(std::string const &val);

    lines unparse_comment(std::string const &val);

    lines unparse(std::string const &name, spartsi::attribute const &attribute);

    unparsed::pair unparse(std::string const &name, spartsi::ref_attribute const &attribute);

    unparsed::pair unparse(spartsi::attributes_map const &attrs);

    lines unparse(spartsi::tree const &tree);
}