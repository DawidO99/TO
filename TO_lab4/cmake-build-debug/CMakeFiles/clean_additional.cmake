# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SKKM_Symulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SKKM_Symulator_autogen.dir/ParseCache.txt"
  "SKKM_Symulator_autogen"
  )
endif()
