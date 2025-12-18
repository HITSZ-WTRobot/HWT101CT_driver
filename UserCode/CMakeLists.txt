# UserCode/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(HWT101CT)

# 导库方式
# add_subdirectory({project_path}/UserCode)
# target_link_libraries(${PROJECT_NAME}.elf PRIVATE HWT101CT)

# ---------------------------------------------------------------------------
# guard: UserCode should only be included by parent project
# ---------------------------------------------------------------------------
if (PROJECT_IS_TOP_LEVEL)
    message(FATAL_ERROR "UserCode must be included via add_subdirectory() from parent project")
endif ()

# ---------------------------------------------------------------------------
# layer options
# ---------------------------------------------------------------------------
#option(ENABLE_BSP "enable BSP layer" ON)

# ---------------------------------------------------------------------------
# collect layer sources
# ---------------------------------------------------------------------------
set(ALL_SOURCES drivers/HWT101CT.c)

set(ALL_HEADERS "drivers/HWT101CT.h")

# ---------------------------------------------------------------------------
# feature options: option + source + macro
# ---------------------------------------------------------------------------
set(DRIVER_MACROS "")

# ---------------------------------------------------------------------------
# create static library
# ---------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${ALL_SOURCES})

# ---------------------------------------------------------------------------
# compile definitions
# ---------------------------------------------------------------------------
if (DRIVER_MACROS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${DRIVER_MACROS})
endif ()

# ---------------------------------------------------------------------------
# build/include 目录
# ---------------------------------------------------------------------------
set(EXPORT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${EXPORT_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXPORT_INCLUDE_DIR})

# ---------------------------------------------------------------------------
# copy selected headers
# ---------------------------------------------------------------------------
foreach (header IN LISTS ALL_HEADERS)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/${header}
            ${EXPORT_INCLUDE_DIR}/${header} COPYONLY)
endforeach ()


# ---------------------------------------------------------------------------
# declare dependencies
# ---------------------------------------------------------------------------
