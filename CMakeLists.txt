cmake_minimum_required(VERSION 3.10)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(lab03 VERSION ${PROJECT_VERSION})
add_executable(lab03 main.cpp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
install(TARGETS lab03 DESTINATION bin)
set(CPACK_GENERATOR "ZIP;DEB")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME "lab03")
set(CPACK_PACKAGE_DESCRIPTION "Описание вашего проекта")
set(CPACK_PACKAGE_VENDOR "Ваше имя или компания")
set(CPACK_PACKAGE_CONTACT "Ваш контактный email")
include(CPack)