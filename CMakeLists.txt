cmake_minimum_required(VERSION 3.16)
project(findback LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(findback
    main.cpp
    src/Item.cpp
    src/TextPreprocessor.cpp
    src/TfidfVectorizer.cpp
    src/SimilarityEngine.cpp
    src/MatchEngine.cpp
)
target_include_directories(findback PRIVATE include)
if(MSVC)
    target_compile_options(findback PRIVATE /W4)
else()
    target_compile_options(findback PRIVATE -Wall -Wextra -Wpedantic)
endif()
add_custom_target(self-test COMMAND findback --test DEPENDS findback)
