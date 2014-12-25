QT += core \
    gui

SOURCES += main.cpp \
    raytracewindow.cpp \
    rtscene.cpp \
    textures/rttexture.cpp \
    textures/rtsolidcolortexture.cpp \
    textures/rtmasktexture.cpp \
    textures/rtimagetexture.cpp \
    utils/color3.cpp \
    objects/rtsphereobject.cpp \
    objects/rtplaneobject.cpp \
    objects/rtobject.cpp \
    materials/rtmaterial.cpp \
    lights/rtlight.cpp \
    textures/rtnormalmap.cpp \
    utils/geometry.cpp \
    objects/rtconeobject.cpp \
    objects/rtcylinderobject.cpp \
    kdtree/rtkdtree.cpp \
    utils/rtbbox.cpp \
    objects/rtpolyobject.cpp \
    kdtree/rtkdsplitplane.cpp \
    kdtree/rtkdnode.cpp

HEADERS +=     rtscene.h \
    raytracewindow.h \
    textures/rttexture.h \
    textures/rtsolidcolortexture.h \
    textures/rtmasktexture.h \
    textures/rtimagetexture.h \
    utils/color3.h \
    objects/rtsphereobject.h \
    objects/rtplaneobject.h \
    objects/rtobject.h \
    materials/rtmaterial.h \
    lights/rtlight.h \
    lights/lightsCommon.h \
    utils/utilsCommon.h \
    utils/geometry.h \
    materials/materialsCommon.h \
    objects/objectsCommon.h \
    textures/textureCommon.h \
    textures/rtnormalmap.h \
    objects/rtconeobject.h \
    objects/rtcylinderobject.h \
    kdtree/rtkdtree.h \
    utils/rtbbox.h \
    objects/rtpolyobject.h \
    kdtree/rtkdsplitplane.h \
    kdtree/rtkdnode.h


QMAKE_LIBS    += -lgomp -lpthread
#QMAKE_CXXFLAGS+= -fopenmp
QMAKE_CXXFLAGS+= -fopenmp -msse4.1 -O3 -ffast-math -falign-functions -falign-jumps -finline-functions -fweb -ftree-vectorize -mfpmath=sse
CFLAGS="-O3 -march=core2 -fno-align-functions -fno-align-labels -mfpmath=sse -msse4.1 -finline-functions --param l2-cache-size=512 -fomit-frame-pointer -pipe -Wno-all"
