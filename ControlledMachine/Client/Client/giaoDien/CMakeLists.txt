cmake_minimum_required(VERSION 3.10)
project(MyFLTKApp)

# Specify the path to your FLTK installation
set(FLTK_DIR "D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/build")

# Force static linking
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# Add executable
add_executable(MyFLTKApp WIN32 UI.cpp)

# Include directories
target_include_directories(MyFLTKApp PRIVATE 
    ${FLTK_DIR}
    ${FLTK_DIR}/..
)

# Link directories
target_link_directories(MyFLTKApp PRIVATE
    ${FLTK_DIR}/lib
)

# Link libraries with GDI+ support
target_link_libraries(MyFLTKApp PRIVATE
    ${FLTK_DIR}/lib/libfltk.a
    ${FLTK_DIR}/lib/libfltk_forms.a
    ${FLTK_DIR}/lib/libfltk_images.a
    ${FLTK_DIR}/lib/libfltk_gl.a
    -lgdiplus
    -lgdi32
    -luser32
    -lshell32
    -lole32
    -luuid
    -lcomdlg32
    -ladvapi32
    -loleaut32
    -lws2_32
    -lcomctl32
)

# Add compile definitions
target_compile_definitions(MyFLTKApp PRIVATE
    WIN32
    _WINDOWS
    _CRT_SECURE_NO_WARNINGS
    FL_LIBRARY
)