project(JpgDiff)
cmake_minimum_required(VERSION 3.0)

add_executable(jpg_diff
    image_loader.cpp
    image.cpp
    image_writer.cpp
    main.cpp
)

target_link_libraries(jpg_diff
    /usr/lib/x86_64-linux-gnu/libjpeg.a
    /usr/lib/x86_64-linux-gnu/libpng16.a
    z
)
