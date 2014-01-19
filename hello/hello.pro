#-------------------------------------------------
#
# Project created by QtCreator 2014-01-19T17:54:26
#
#-------------------------------------------------

QT       =

TARGET = hellocl
CONFIG   += console
CONFIG   -= app_bundle

CUDA_PATH=$$(CUDA_PATH)
INCLUDEPATH += $${CUDA_PATH}/include
win32 {
  LIBS += -L$${CUDA_PATH}/lib/Win32
} else {
  LIBS += -L$${CUDA_PATH}/lib
}
LIBS += -lOpenCL


TEMPLATE = app


SOURCES += main.cpp
