TEMPLATE = app
TARGET = "localization-in-polygon"

CONFIG += QtGui 
QT += opengl

OBJECTS_DIR = bin

QMAKE_CXXFLAGS = -std=c++0x


DEPENDPATH += src \
              visualization/headers \
              visualization/headers/geom/primitives/ \
              visualization/headers/common \
              visualization/headers/io \
              visualization/headers/visualization \

INCLUDEPATH += visualization/headers \
           

HEADERS += src/*.h \
           

SOURCES += src/*.cpp \

LIBS += -Lvisualization -lvisualization



mytarget.target = commit

mytarget.commands = 	hg addremove -X *.sw[po] -X */*.sw[po] -X */*/*.sw[po] -X */*/*/*.sw[po] -X */*/*/*/*sw[po] ;
mytarget.commands += 	hg commit -m \"make commit $(CMSG)\" ;
mytarget.commands +=	hg push 

mytarget.depends = clean

QMAKE_EXTRA_TARGETS += mytarget

