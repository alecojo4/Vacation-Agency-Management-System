# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\labQTFinal_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\labQTFinal_autogen.dir\\ParseCache.txt"
  "labQTFinal_autogen"
  )
endif()
