cmake_minimum_required(VERSION 3.16)


project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp )


if(MINGW)
    target_compile_options(main PRIVATE "-pthread" "-static-libgcc" "-static-libstdc++")
    target_link_options(main PRIVATE "-static" "-pthread" "-static-libgcc" "-static-libstdc++")
    

endif()






