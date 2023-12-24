cmake_minimum_required (VERSION 3.2.0)
project (learn)

# Set Configuration specific DEFINES
IF ( CMAKE_BUILD_TYPE STREQUAL "Debug" ) 
  add_definitions ( "-DUSE_PERFORMANCE_DATA")
  add_definitions ( "-DDEBUG " )
  add_definitions ( "-D_DEBUG " )
  add_definitions ( "-std=c++20")
  add_definitions ( "-rdynamic ")
  add_definitions ( "-g ")

  add_definitions ( "-Wno-deprecated ")
  add_definitions ( "-Wno-unknown-pragmas ")

ELSE()
  add_definitions ( "-Wall ")
  add_definitions ( "-DNDEBUG " )
  add_definitions ( "-DUSE_PERFORMANCE_DATA")
  add_definitions ( "-O3 ")
  add_definitions ( "-std=c++20")
  add_definitions ( "-march=native ")
  add_definitions ( "-mtune=native ")
  add_definitions ( "-Wno-deprecated ")
  add_definitions ( "-Wno-unknown-pragmas ")
  add_definitions ( "-rdynamic ")
  add_definitions ( "-g ")
ENDIF()

include_directories (/usr/include)
include_directories (/usr/local/include)

link_directories (/usr/lib)
link_directories (/usr/local/lib)

add_executable (analysis
  analysis/src/main.cpp
  analysis/src/calc_mean.cpp
  analysis/src/calc_sum.cpp
  )

add_executable (double
  double/main.cpp
)
target_link_libraries(double pthread)

add_executable (three
three/main.cpp
)
target_link_libraries(three pthread)


add_executable (sqlite
  sqlite/main.cpp
)
target_link_libraries(sqlite pthread sqlite3)

# add_library(ds
#   datastruct/vector.cpp
# ) 

add_executable(datastruct
  datastruct/main.cpp)

add_executable(fraction
  fraction/main.cpp)

add_executable(advent2023
  advent2023/main.cpp
)

add_executable(sandboxa
  sandboxa/main.cpp
)


  # target_link_libraries(datastruct ds pthread)
