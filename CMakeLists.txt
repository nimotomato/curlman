cmake_minimum_required(VERSION 3.19)
project(curlman LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(CURL REQUIRED)

qt_standard_project_setup()

add_custom_target(DatabaseFiles SOURCES
    migrations/20260726T095000_request.sql
    migrations/20260726T095100_response.sql
    migrations/20260726T095700_request_header.sql
)

file(COPY
    ${CMAKE_SOURCE_DIR}/migrations
    DESTINATION ${CMAKE_BINARY_DIR}
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
qt_add_executable(curlman
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/appsettings.cpp
    src/header.cpp
    src/headervector.cpp
    src/request.cpp
    src/response.cpp

    include/mainwindow.h
    include/appsettings.h
    include/header.h
    include/headervector.h
    include/request.h
    include/response.h

    ui/mainwindow.ui
)

target_include_directories(curlman PRIVATE include)

qt_add_translations(
    TARGETS curlman
    TS_FILES curlman_en_US.ts
)

target_link_libraries(curlman
    PRIVATE
        Qt::Core
        Qt::Widgets
        CURL::libcurl
)

install(TARGETS curlman
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET curlman
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
