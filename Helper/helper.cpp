#include "helper.h"

std::vector<std::string_view> split(std::string_view text, std::string_view delimiter) {
    std::vector<std::string_view> splits;

    while (!text.empty()) {
        size_t pos = text.find(delimiter);
        splits.push_back(text.substr(0, pos));
        text = text.substr(pos+delimiter.size());
    }

    return splits;
}

std::pair<std::string_view, std::string_view> split2(std::string_view text, std::string_view delimiter) {
    size_t pos = text.find(delimiter);
    return std::make_pair(text.substr(0, pos), text.substr(pos));
}

std::tuple<std::string_view, std::string_view, std::string_view> split3(std::string_view text, std::string_view delimiter) {
    auto [first, rest] = split2(text, delimiter);
    auto [second, third] = split2(rest, delimiter);
    return std::make_tuple(first, second, third);
}