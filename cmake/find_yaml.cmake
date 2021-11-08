find_library(YAMLCPP_LIBRARY
        NAMES ${YAMLCPP_STATIC} yaml-cpp
        PATH_SUFFIXES lib64 lib lib/aarch64-linux-gnu
        PATHS ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        ${YAMLCPP_DIR}/lib)