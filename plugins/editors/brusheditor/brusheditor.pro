######################################################################
#	BrushEditor SACS2 build script. Serkov Alexander, 2007
######################################################################

TEMPLATE = lib
TARGET = BrushEditor
CONFIG += plugin
DEPENDPATH += . ./../../../pluginTool
INCLUDEPATH += . ./../../../pluginTool
LIBS += -L./../../../pluginTool
DESTDIR = ./../../../bin/plugins/BrushEditor

HEADERS += BrushEditor.h \
	Plugin.h \
	TexturesList.h \
	SignalHolder.h
SOURCES += BrushEditor.cpp
FORMS += BrushEditor.ui \
	TexturesForm.ui
QT += xml \
    xmlpatterns
