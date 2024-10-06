cmake_minimum_required(VERSION 3.10)

# Установка версии патча
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

# Определение проекта
project(lab03 VERSION ${PROJECT_VERSION})

# Добавление исполняемого файла
add_executable(lab03 main.cpp)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка генераторов пакетов
set(CPACK_GENERATOR "ZIP;DEB")  # Добавьте DEB для Ubuntu
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Метаданные пакета (необязательно)
set(CPACK_PACKAGE_NAME "lab03")
set(CPACK_PACKAGE_DESCRIPTION "Описание вашего проекта")
set(CPACK_PACKAGE_VENDOR "Ваше имя или компания")
set(CPACK_PACKAGE_CONTACT "Ваш контактный email")

include(CPack)

# cmake_minimum_required(VERSION 3.10)
# set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
# set(PROJECT_VESRION 0.0.${PATCH_VERSION})
# add_executable(lab03 main.cpp)
# project(lab03 VERSION ${PROJECT_VESRION})
# set(CMAKE_CXX_STANDARD 11)
# set(CXX_STANDARD_REQUIRED ON)
# set(CPACK_GENERATOR ZIP)
# set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
# set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
# include(CPack)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})