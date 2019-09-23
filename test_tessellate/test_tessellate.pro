TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../dict.c \
        ../geom.c \
        ../memalloc.c \
        ../mesh.c \
        ../normal.c \
        ../priorityq-heap.c \
        ../priorityq.c \
        ../render.c \
        ../sweep.c \
        ../tess.c \
        ../tessellate.c \
        ../tessmono.c \
        test_tessellate.c

DISTFILES += \
    ../LICENSE \
    ../README.md

HEADERS += \
    ../dict-list.h \
    ../dict.h \
    ../geom.h \
    ../glu.h \
    ../gluos.h \
    ../memalloc.h \
    ../mesh.h \
    ../normal.h \
    ../priorityq-heap.h \
    ../priorityq-sort.h \
    ../priorityq.h \
    ../render.h \
    ../sweep.h \
    ../tess.h \
    ../tessellate.h \
    ../tessmono.h
