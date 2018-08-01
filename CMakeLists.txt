cmake_minimum_required(VERSION 3.5)
project( DisplayImage )
set(OpenCV_DIR /usr/local/share/OpenCV)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-W -Wall -Werror)
find_package( OpenCV REQUIRED )
set(COMMON_SRC 
    converter.cpp 
    pixel_helper.cpp
)
add_executable( main main.cpp ${COMMON_SRC} )
target_link_libraries( main ${OpenCV_LIBS} )

ENABLE_TESTING()
ADD_EXECUTABLE(test_pixel test_pixel.cpp pixel_helper.cpp ${COMMON_SRC})
target_link_libraries(test_pixel ${OpenCV_LIBS} )
ADD_TEST(main1 test_pixel)

ADD_EXECUTABLE(test_convert test_convert.cpp pixel_helper.cpp ${COMMON_SRC})
target_link_libraries(test_convert ${OpenCV_LIBS} )
ADD_TEST(main1 test_convert)

