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

set(PROJECT_SOURCES_FILM film.h review.h film.cpp review.cpp cppio.hpp )

set(PROJECT_SOURCES_USER user.h admin.h logged.h guest.h role.h user.cpp logged.cpp guest.cpp role.cpp ${PROJECT_SOURCES_FILM})

set(PROJECT_SOURCES_PERSON person.h person.cpp date.h date.cpp global.h global.cpp ${PROJECT_SOURCES_USER} ${PROJECT_SOURCES_FILM})

set(PROJECT_SOURCES_MAIN ${PROJECT_SOURCES_FILM} ${PROJECT_SOURCES_PERSON} ${PROJECT_SOURCES_USER} global.h global.cpp filmPage.h page.h page.cpp filmPage.cpp browsePage.h browsePage.cpp startPage.h startPage.cpp reviewsPage.h reviewsPage.cpp userPage.h userPage.cpp addReviewPage.h addReviewPage.cpp actorPage.h actorPage.cpp databaseManager.h databaseManager.cpp directorPage.h directorPage.cpp producerPage.h producerPage.cpp writerPage.h writerPage.cpp)

include_directories("${csvreader_SOURCE_DIR}")

add_executable(testFilm testFilm.cpp ${PROJECT_SOURCES_FILM})
target_link_libraries(testFilm PUBLIC gtest_main)
target_link_libraries(testFilm PUBLIC ${csvReader_SOURCE_DIR})
add_executable(test test.cpp ${PROJECT_SOURCES_MAIN})
target_link_libraries(test PUBLIC ${csvReader_SOURCE_DIR})

add_executable(testUser testUser.cpp ${PROJECT_SOURCES_USER})
target_link_libraries(testUser PUBLIC gtest_main)

add_executable(testPerson testPerson.cpp ${PROJECT_SOURCES_PERSON})
target_link_libraries(testPerson PUBLIC gtest_main)

add_executable(testDate testDate.cpp date.h date.cpp)
target_link_libraries(testDate PUBLIC gtest_main)


add_executable(main main.cpp ${PROJECT_SOURCES_MAIN})
target_link_libraries(main PUBLIC ${csvReader_SOURCE_DIR})

add_executable(testPage testPage.cpp ${PROJECT_SOURCES_MAIN})
target_link_libraries(testPage PUBLIC gtest_main)
