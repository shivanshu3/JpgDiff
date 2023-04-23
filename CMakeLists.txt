project(HelloJpg)
cmake_minimum_required(VERSION 3.0)

add_executable(hellojpg
    image_loader.cpp
    image.cpp
    main.cpp
)

target_link_libraries(hellojpg /usr/lib/x86_64-linux-gnu/libjpeg.a)
