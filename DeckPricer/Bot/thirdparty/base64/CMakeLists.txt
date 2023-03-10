include(FetchContent)
message(STATUS "Fetching base64...")

FetchContent_Declare(base64
  URL https://github.com/ReneNyffenegger/cpp-base64/archive/refs/tags/V2.rc.08.zip
  URL_HASH SHA512=3dedc7605ef2a18f99a39e231a1d30e179a1a16b16fddf2e90392635bc00df9c89fc3f58707e405afbb87d71cea47c13c7d2107c8d162403742b5cc4531acad8
  
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
  DOWNLOAD_EXTRACT_TIMESTAMP true
  )

FetchContent_GetProperties(base64)

if(NOT base64_POPULATED)
   
    FetchContent_Populate(base64)

    set(BASE64_SOURCES
      ${CMAKE_CURRENT_BINARY_DIR}/src/base64.cpp
    )

    add_library(base64 STATIC ${BASE64_SOURCES})

    target_include_directories(base64
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
        $<INSTALL_INTERFACE:include>
    )

endif()
