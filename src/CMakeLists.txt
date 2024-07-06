# src/CMakeLists.txt

# Add include
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(main ${SOURCES} main.cpp order_book_1.cpp
        simple_order_book.cpp)