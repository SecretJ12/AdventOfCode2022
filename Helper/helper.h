#pragma once

#include <vector>
#include <tuple>
#include <string_view>


/**
 * Splits string view into substrings separated by given delimiter
 * @param text
 * @param delimiter
 * @return
 */
std::vector<std::string_view> split(std::string_view text, std::string_view delimiter);

/**
 * Splits string view into pair separated by given delimiter
 * @param text
 * @param delimiter
 * @return
 */
std::pair<std::string_view, std::string_view> split2(std::string_view text, std::string_view delimiter);

/**
 * Splits string view into tuple of three separated by given delimiter
 * @param text
 * @param delimiter
 * @return
 */
std::tuple<std::string_view, std::string_view, std::string_view> split3(std::string_view text, std::string_view delimiter);