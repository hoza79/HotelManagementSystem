# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appHotelManagementSystem_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appHotelManagementSystem_autogen.dir/ParseCache.txt"
  "appHotelManagementSystem_autogen"
  )
endif()
