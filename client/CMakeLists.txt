set(gammaray_clientlib_srcs
  client.cpp
  remotemodel.cpp
  selectionmodelclient.cpp
  clientconnectionmanager.cpp
  propertycontrollerclient.cpp
  probecontrollerclient.cpp
  toolmanagerclient.cpp
  clientdevice.cpp
  tcpclientdevice.cpp
  localclientdevice.cpp
  messagestatisticsmodel.cpp
  paintanalyzerclient.cpp
  remoteviewclient.cpp
  enumrepositoryclient.cpp
  classesiconsrepositoryclient.cpp
)

qt4_add_resources(gammaray_clientlib_srcs ${CMAKE_SOURCE_DIR}/resources/gammaray.qrc)
add_library(gammaray_client SHARED ${gammaray_clientlib_srcs})
generate_export_header(gammaray_client)
set_target_properties(gammaray_client PROPERTIES
  ${GAMMARAY_DEFAULT_LIBRARY_PROPERTIES}
)

gammaray_target_relocatable_interfaces(gammaray_client_ipaths)
target_include_directories(gammaray_client PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<INSTALL_INTERFACE:${gammaray_client_ipaths}>)
target_link_libraries(gammaray_client
  LINK_PUBLIC
  ${QT_QTCORE_LIBRARIES}

  LINK_PRIVATE
  gammaray_ui
  gammaray_ui_internal
  gammaray_common
  ${QT_QTGUI_LIBRARIES}
  ${QT_QTNETWORK_LIBRARIES}
)


set(gammaray_client_srcs main.cpp)
gammaray_add_win_icon(gammaray_client_srcs)

add_executable(gammaray-client WIN32 ${gammaray_client_srcs})

target_link_libraries(gammaray-client
  gammaray_client
  gammaray_common
  ${QT_QTGUI_LIBRARIES}
)

gammaray_embed_info_plist(gammaray-client ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in)
set_target_properties(gammaray-client PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${LIBEXEC_INSTALL_DIR}"
)

if(NOT GAMMARAY_PROBE_ONLY_BUILD)
  install(TARGETS gammaray_client EXPORT GammaRayTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

  gammaray_install_headers(
    ${CMAKE_CURRENT_BINARY_DIR}/gammaray_client_export.h
    clientconnectionmanager.h
  )

  ecm_generate_pri_file(BASE_NAME GammaRayClient
                        LIB_NAME gammaray_client
                        DEPS "core gui widgets network GammaRayCommon GammaRayUi"
                        FILENAME_VAR PRI_FILENAME
                        INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_DIR}
  )

  install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
else()
  install(TARGETS gammaray_client ${INSTALL_TARGETS_DEFAULT_ARGS})
endif()
if(MSVC)
  install(FILES "$<TARGET_PDB_FILE_DIR:gammaray_client>/$<TARGET_PDB_FILE_NAME:gammaray_client>" DESTINATION ${BIN_INSTALL_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()

install(TARGETS gammaray-client DESTINATION ${LIBEXEC_INSTALL_DIR})
