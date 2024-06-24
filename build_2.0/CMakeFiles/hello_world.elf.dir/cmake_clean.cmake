file(REMOVE_RECURSE
  "hello_world.bin"
  "hello_world.hex"
  "hello_world.map"
  "hello_world.objdump"
  "CMakeFiles/hello_world.elf.dir/main.c.obj"
  "CMakeFiles/hello_world.elf.dir/main.c.obj.d"
  "hello_world.elf"
  "hello_world.elf.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/hello_world.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
