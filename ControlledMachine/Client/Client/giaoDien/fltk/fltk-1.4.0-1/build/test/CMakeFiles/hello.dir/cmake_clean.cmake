file(REMOVE_RECURSE
  "../bin/test/hello.exe"
  "../bin/test/hello.exe.manifest"
  "../bin/test/hello.pdb"
  "../bin/test/libhello.dll.a"
  "CMakeFiles/hello.dir/hello.cxx.obj"
  "CMakeFiles/hello.dir/hello.cxx.obj.d"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/hello.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
