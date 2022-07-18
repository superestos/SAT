cmake_minimum_required(VERSION 3.14)
project(YetAnotherLispEvaluator)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
enable_testing()

file(GLOB_RECURSE include_files CONFIGURE_DEPENDS "./include")

add_executable(assignment_test ${include_files} test/assignment_test.cc)

target_link_libraries(assignment_test gtest_main)

# add_executable(sat ${include_files} main.cc)

include(GoogleTest)