cmake_minimum_required(VERSION 3.20) project(
    curator VERSION 0.1.0 DESCRIPTION
    "Artisan Writer" HOMEPAGE_URL
    "https://github.com/mistericy/curator" LANGUAGES "C")

    set(CMAKE_C_STANDARD 17) set(CMAKE_C_STANDARD_REQUIRED True)

        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} /
            lib) set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} / lib)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} / bin)

                find_package(PkgConfig REQUIRED) find_package(SQLite3 REQUIRED)

                    include_directories(${SQLite3_INCLUDE_DIR})

                        add_executable(${PROJECT_NAME} src / main.c src /
                                       database / database.h src / database /
                                       database.c) target_link_libraries(${
                            PROJECT_NAME} ${SQLite3_LIBRARY})
