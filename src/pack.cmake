#-------------------------------------------------------------------------------
# Helper macro to setup installer packages
macro(setup_package)
    set(PACKAGE_ROOT_DIR @CMAKE_INSTALL_PREFIX@/packages/${PACKAGE_NAME})
    set(PACKAGE_DIR ${PACKAGE_ROOT_DIR}/data)
    file(REMOVE_RECURSE @CMAKE_INSTALL_PREFIX@/packages/${PACKAGE_NAME})
    file(MAKE_DIRECTORY @CMAKE_INSTALL_PREFIX@/packages/${PACKAGE_NAME}/data)
    file(MAKE_DIRECTORY @CMAKE_INSTALL_PREFIX@/packages/${PACKAGE_NAME}/meta)
    configure_file(${PACKAGE_CONFIG_TEMPLATE} ${PACKAGE_ROOT_DIR}/meta/package.xml)
endmacro()

#-------------------------------------------------------------------------------
# For simple script modules, this macro will package the full module directory
macro(pack_module_dir)
    file(INSTALL DESTINATION ${PACKAGE_DIR}/modules
        TYPE DIRECTORY
        FILES
            ${SOURCE_DIR}/modules/${PACKAGE_NAME}
        PATTERN ".git" EXCLUDE
        )
endmacro()

#-------------------------------------------------------------------------------
# pack instructions for the omegalib core.
# Copy over some variables, they will be substituted by configure_file.
# Needed since this file will be executed from outside the main omegalib cmake
# run.
set(PACKAGE_ROOT_DIR @CMAKE_INSTALL_PREFIX@/packages/core)
set(PACKAGE_DIR @CMAKE_INSTALL_PREFIX@/packages/core/data)
set(OMEGALIB_VERSION @OMEGALIB_VERSION@)
set(BUILD_DIR @CMAKE_BINARY_DIR@)
set(SOURCE_DIR @CMAKE_SOURCE_DIR@)

# needed to avoid wrong substitution in installer files
set(RootDir "@RootDir@")

set(PACKAGE_CONFIG_TEMPLATE ${PACKAGE_ROOT_DIR}/meta/package.xml.in)

if(WIN32)
    set(BIN_DIR ${BUILD_DIR}/bin/release)
else()
    set(BIN_DIR ${BUILD_DIR}/bin)
endif()

# Save the current date to a variable. Will be used during packaging.
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")

file(REMOVE_RECURSE ${PACKAGE_DIR})
file(MAKE_DIRECTORY ${PACKAGE_DIR})

configure_file(
    @CMAKE_INSTALL_PREFIX@/config/config-offline.xml.in 
    @CMAKE_INSTALL_PREFIX@/config/config-offline.xml)

configure_file(
    @CMAKE_INSTALL_PREFIX@/config/config-online.xml.in 
    @CMAKE_INSTALL_PREFIX@/config/config-online.xml)
    
configure_file(
    ${PACKAGE_ROOT_DIR}/meta/core-package.xml.in 
    ${PACKAGE_ROOT_DIR}/meta/package.xml)

# Copy core files.
if(WIN32)
	file(INSTALL DESTINATION ${PACKAGE_DIR}/modules/python 
        TYPE DIRECTORY
        FILES
            ${SOURCE_DIR}/modules/python/DLLs
            ${SOURCE_DIR}/modules/python/Lib)

	file(INSTALL DESTINATION ${PACKAGE_DIR}/modules/python 
        TYPE DIRECTORY
        FILES
            ${SOURCE_DIR}/modules/python/DLLs
            ${SOURCE_DIR}/modules/python/Lib)
            
    file(INSTALL DESTINATION ${PACKAGE_DIR}/bin
        TYPE FILE
        FILES
            # Dlls
            ${BIN_DIR}/Collage.dll
            ${BIN_DIR}/Equalizer.dll
            ${BIN_DIR}/EqualizerServer.dll
            ${BIN_DIR}/msvcp120.dll
            ${BIN_DIR}/msvcr120.dll
            ${BIN_DIR}/omega.dll
            ${BIN_DIR}/omegaToolkit.dll
            ${BIN_DIR}/omicron.dll
            ${BIN_DIR}/PQMTClient.dll
            ${BIN_DIR}/pthread.dll
            ${BIN_DIR}/python27.dll
            # Executables
            ${BIN_DIR}/orun.exe
        )
        
    file(APPEND ${PACKAGE_DIR}/orun.bat ".\\bin\\orun.exe -D %~dp0%")
endif()

file(INSTALL DESTINATION ${PACKAGE_DIR}
    TYPE DIRECTORY
    FILES
        ${SOURCE_DIR}/fonts
        ${SOURCE_DIR}/menu_sounds
        ${SOURCE_DIR}/ui
        ${SOURCE_DIR}/system
    )
    
file(INSTALL DESTINATION ${PACKAGE_DIR}
    TYPE FILE
    FILES
        ${SOURCE_DIR}/default.cfg
        ${SOURCE_DIR}/default_init.py
        ${SOURCE_DIR}/omegalib-transparent-white.png
    )

    
#-------------------------------------------------------------------------------
# create the examples package
set(PACKAGE_NAME core.examples)
set(PACKAGE_DISPLAY_NAME "Examples")
set(PACKAGE_DESCRIPTION "Omegalib core examples")
set(PACKAGE_DEPENDENCIES "")
set(PACKAGE_VERSION ${OMEGALIB_VERSION})

setup_package()

if(WIN32)
    file(INSTALL DESTINATION ${PACKAGE_DIR}/bin
        TYPE FILE
        FILES
            ${BIN_DIR}/ohello.exe
            ${BIN_DIR}/ohelloWidgets.exe
            ${BIN_DIR}/text2texture.exe
        )
endif()

file(INSTALL DESTINATION ${PACKAGE_DIR}/examples
    TYPE DIRECTORY
    FILES
        ${SOURCE_DIR}/examples/python
    )

#-------------------------------------------------------------------------------
# create the utils package
set(PACKAGE_NAME core.utils)
set(PACKAGE_DISPLAY_NAME "Utilities")
set(PACKAGE_DESCRIPTION 
    "Omegalib core utilities. Includes mission control server, input server and asset cache server")
set(PACKAGE_DEPENDENCIES "")
set(PACKAGE_VERSION ${OMEGALIB_VERSION})

setup_package()

if(WIN32)
    file(INSTALL DESTINATION ${PACKAGE_DIR}/bin
        TYPE FILE
        FILES
            ${BIN_DIR}/mcsend.exe
            ${BIN_DIR}/mcserver.exe
            ${BIN_DIR}/ocachesrv.exe
            ${BIN_DIR}/ocachesync.exe
            ${BIN_DIR}/oimg.exe
            ${BIN_DIR}/oinputserver.exe
            ${BIN_DIR}/olauncher.exe
        )
endif()

    