cmake_minimum_required(VERSION 3.12)
project(hello)


set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_LINK_WHAT_YOU_USE TRUE)
#find_program(TIDY "clang-tidy-6.0")
#set(CMAKE_CXX_CLANG_TIDY ${TIDY} "-checks=*")
#find_program(CPPCHECK cppcheck "--std=c++14")
#set(CMAKE_CXX_CPPCHECK ${CPPCHECK})
#find_program(IWYU include-what-you-use)
#set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE  ${IWYU})

find_package(OpenCV REQUIRED)
add_executable(hough_line_detector main.cpp)
target_include_directories(hough_line_detector PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(hough_line_detector PRIVATE opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc)
#target_link_libraries(hough_line_detector PRIVATE opencv_imgcodecs opencv_core)