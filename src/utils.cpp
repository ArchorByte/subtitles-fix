#include "utils.hpp"

#include <string>
#include <regex>
#include <cctype>
#include <algorithm>

// Verify if a string is only composed of digits.
bool is_an_integer
(
    const std::string &input
)
{
    // Try to find any non-digit character in the input.
    static const std::regex pattern(R"(^-?\d+$)");
    const bool is_an_integer = std::regex_match(input, pattern);

    return is_an_integer;
}

// Remove whitespaces from the start and end of a string.
std::string trim
(
    const std::string &input
)
{
    // Calculate the real start and end of the string by ignoring whitespaces.
    const size_t string_start = input.find_first_not_of(" \t\r\n");
    const size_t string_end = input.find_last_not_of(" \t\r\n");

    // Return an empty string if necessary or the trimmed text.
    const std::string output = string_start == std::string::npos ? "" : input.substr(string_start, string_end - string_start + 1);

    return output;
}
