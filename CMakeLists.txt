cmake_minimum_required(VERSION 3.11.0)
project(filmownia VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)
FetchContent_Declare(
  csvReader
  GIT_REPOSITORY https://github.com/ben-strasser/fast-cpp-csv-parser.git
  GIT_TAG master
)

FetchContent_MakeAvailable(csvReader)
set(PROJECT_SOURCES_USER user.h)

set(PROJECT_SOURCES_FILM film.cpp review.cpp film.h review.h)

include_directories("${csvreader_SOURCE_DIR}")

add_executable(testFilm testFilm.cpp ${PROJECT_SOURCES_FILM})
target_link_libraries(testFilm PUBLIC gtest_main)
target_link_libraries(testFilm PUBLIC ${csvReader_SOURCE_DIR})
add_executable(test test.cpp ${PROJECT_SOURCES_FILM})
target_link_libraries(test PUBLIC ${csvReader_SOURCE_DIR})

add_executable(testUser testUser.cpp ${PROJECT_SOURCES_USER})
target_link_libraries(testUser PUBLIC gtest_main)
