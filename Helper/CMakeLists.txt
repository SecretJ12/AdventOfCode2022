
add_library(helper helper.cpp)

target_include_directories(helper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(helper PUBLIC cxx_std_20)