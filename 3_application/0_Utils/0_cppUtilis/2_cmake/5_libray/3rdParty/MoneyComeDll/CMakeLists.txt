project(MyLibraryProject)

set(LIBRARY_SOURCES money.cpp)
set(LIBRARY_HEADERS money.h)

add_library(MyStaticLibrary STATIC ${LIBRARY_SOURCES})

