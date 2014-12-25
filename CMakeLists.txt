set(CMAKE_PREFIX_PATH "C:\\Work\\Tools\\Qt\\5.4.0\\5.4\\mingw491_32")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

cmake_minimum_required(VERSION 2.8.11)
project(simple_raytracer)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)


find_package(OpenMP)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)

get_target_property(QtCore_location Qt5::Core LOCATION)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -std=c++11 -msse4.1 -O3 -ffast-math -falign-functions -falign-jumps -finline-functions -fweb -ftree-vectorize -mfpmath=sse")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=core2 -fno-align-functions -fno-align-labels -mfpmath=sse -msse4.1 -finline-functions --param l2-cache-size=512 -fomit-frame-pointer -pipe -Wno-all")

set(SOURCE_FILES
    src/kdtree/rtkdnode.cpp
    src/kdtree/rtkdnode.h
    src/kdtree/rtkdsplitplane.cpp
    src/kdtree/rtkdsplitplane.h
    src/kdtree/rtkdtree.cpp
    src/kdtree/rtkdtree.h
    src/lights/lightsCommon.h
    src/lights/rtlight.cpp
    src/lights/rtlight.h
    src/materials/materialsCommon.h
    src/materials/rtmaterial.cpp
    src/materials/rtmaterial.h
    src/objects/objectsCommon.h
    src/objects/rtconeobject.cpp
    src/objects/rtconeobject.h
    src/objects/rtcylinderobject.cpp
    src/objects/rtcylinderobject.h
    src/objects/rtobject.cpp
    src/objects/rtobject.h
    src/objects/rtplaneobject.cpp
    src/objects/rtplaneobject.h
    src/objects/rtsphereobject.cpp
    src/objects/rtsphereobject.h
    src/objects/rtpolyobject.cpp
    src/objects/rtpolyobject.h
    src/textures/rtimagetexture.cpp
    src/textures/rtimagetexture.h
    src/textures/rtmasktexture.cpp
    src/textures/rtmasktexture.h
    src/textures/rtnormalmap.cpp
    src/textures/rtnormalmap.h
    src/textures/rtsolidcolortexture.cpp
    src/textures/rtsolidcolortexture.h
    src/textures/rttexture.cpp
    src/textures/rttexture.h
    src/textures/textureCommon.h
    src/utils/color3.cpp
    src/utils/color3.h
    src/utils/geometry.cpp
    src/utils/geometry.h
    src/utils/utilsCommon.h
    src/utils/rtbbox.cpp
    src/utils/rtbbox.h
    src/main.cpp
    src/raytracewindow.cpp
    src/raytracewindow.h
    src/rtscene.cpp
    src/rtscene.h
    )

include_directories(src)

add_executable(simple_raytracer ${SOURCE_FILES})

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(simple_raytracer ${Qt5Widgets_LIBRARIES})
qt5_use_modules(simple_raytracer Widgets)