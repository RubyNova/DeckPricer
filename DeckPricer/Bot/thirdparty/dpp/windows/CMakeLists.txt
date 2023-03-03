add_library(dpp SHARED IMPORTED GLOBAL)

set_property(TARGET dpp PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/dpp.dll)
set_property(TARGET dpp PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/dpp-10.0/dpp.lib)

target_include_directories(dpp
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dpp-10.0/>
    $<INSTALL_INTERFACE:include>
)