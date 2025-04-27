# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ChatServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ChatServer_autogen.dir\\ParseCache.txt"
  "ChatServer_autogen"
  "CustomWidget\\CMakeFiles\\customwidget_lib_autogen.dir\\AutogenUsed.txt"
  "CustomWidget\\CMakeFiles\\customwidget_lib_autogen.dir\\ParseCache.txt"
  "CustomWidget\\customwidget_lib_autogen"
  "DataBase\\CMakeFiles\\database_lib_autogen.dir\\AutogenUsed.txt"
  "DataBase\\CMakeFiles\\database_lib_autogen.dir\\ParseCache.txt"
  "DataBase\\database_lib_autogen"
  "NetWork\\CMakeFiles\\network_lib_autogen.dir\\AutogenUsed.txt"
  "NetWork\\CMakeFiles\\network_lib_autogen.dir\\ParseCache.txt"
  "NetWork\\network_lib_autogen"
  "NewChat\\CMakeFiles\\newchat_lib_autogen.dir\\AutogenUsed.txt"
  "NewChat\\CMakeFiles\\newchat_lib_autogen.dir\\ParseCache.txt"
  "NewChat\\newchat_lib_autogen"
  "Utility\\CMakeFiles\\utility_lib_autogen.dir\\AutogenUsed.txt"
  "Utility\\CMakeFiles\\utility_lib_autogen.dir\\ParseCache.txt"
  "Utility\\utility_lib_autogen"
  )
endif()
