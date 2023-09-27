HEADERS += \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  file_ply_stl.h \
  generation.h \
  object3d.h \
  axis.h \
  piramidedoble.h \
  tetrahedron.h \
  glwidget.h \
  window.h

SOURCES += \
  basic_object3d.cc \
  cone.cc \
  cube.cc \
  file_ply_stl.cc \
  generation.cc \
  object3d.cc \
  axis.cc \
  piramidedoble.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lopengl32

CONFIG += c++11
QT += widgets
