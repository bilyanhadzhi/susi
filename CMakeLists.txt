cmake_minimum_required(VERSION 3.0.0)
project(susi VERSION 0.1.0)

include(CTest)
enable_testing()

set(Sources
    main.cpp
    io_handler.cpp
    student.cpp
    course.cpp
    string.cpp
    susi.cpp
)

set(Headers
    constants.hpp
    io_handler.hpp
    student.hpp
    course.hpp
    string.hpp
    susi.hpp
)

add_executable(susi ${Sources} ${Headers})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
