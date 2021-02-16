#================================================================================
# Filename: Smooth_polygon_algorithm.pro
# Description: Project that illustrates the work with Bezier curves for 
#   solving the task of smoothing polygon vertices.
#================================================================================

QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Program
TEMPLATE = app

SOURCES += \
    ./src/main.cpp \
    ./src/drawing_window.cpp \
    ./src/control_window.cpp \
    ./src/smooth_polygon.cpp \
    ./src/misc_functions.cpp

HEADERS += \
    ./include/drawing_window.h \
    ./include/control_window.h \
    ./include/constants.h \
    ./include/misc_functions.h \
    ./include/smooth_polygon.h \
    ./include/utils.h

FORMS = \
	./ui/ControlWindow.ui

INCLUDEPATH += $$PWD/include

CONFIG(release, debug|release) {
	DESTDIR = ./build/release
	OBJECTS_DIR = ./build/release/obj
	MOC_DIR = ./build/release/moc
	RCC_DIR = ./build/release/rcc
	UI_DIR = ./build/release/ui
}

CONFIG(debug, debug|release) {
	DESTDIR = ./build/debug
	OBJECTS_DIR = ./build/debug/obj
	MOC_DIR = ./build/debug/moc
	RCC_DIR = ./build/debug/rcc
	UI_DIR = ./build/debug/ui
}
