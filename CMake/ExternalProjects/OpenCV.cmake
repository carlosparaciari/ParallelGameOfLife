#/*============================================================================
#
#  GameOfLife: Let us mix together the Game of Life and parallel programming.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

#-----------------------------------------------------------------------------
# OpenCV
#-----------------------------------------------------------------------------
if(NOT BUILD_OpenCV)
  return()
endif()

# Sanity checks
if(DEFINED OpenCV_DIR AND NOT EXISTS ${OpenCV_DIR})
  message(FATAL_ERROR "OpenCV_DIR variable is defined but corresponds to non-existing directory")
endif()

set(version "2.4.11")
set(location "${NIFTK_EP_TARBALL_LOCATION}/OpenCV-${version}.tar.gz")

mpMacroDefineExternalProjectVariables(OpenCV ${version} ${location})

if(NOT DEFINED OpenCV_DIR)

  if(CTEST_USE_LAUNCHERS)
    list(APPEND additional_cmake_args
      "-DCMAKE_PROJECT_${proj}_INCLUDE:FILEPATH=${CMAKE_ROOT}/Modules/CTestUseLaunchers.cmake"
    )
  endif()

  ExternalProject_Add(${proj}
    LIST_SEPARATOR ^^
    PREFIX ${proj_CONFIG}
    SOURCE_DIR ${proj_SOURCE}
    BINARY_DIR ${proj_BUILD}
    INSTALL_DIR ${proj_INSTALL}
    URL ${proj_LOCATION}
    URL_MD5 ${proj_CHECKSUM}
    # Related bug: http://bugs.mitk.org/show_bug.cgi?id=5912
    PATCH_COMMAND ${PATCH_COMMAND} -N -p1 -i ${CMAKE_CURRENT_LIST_DIR}/OpenCV-2.4.11.patch
    CMAKE_GENERATOR ${gen}
    CMAKE_ARGS
      ${EP_COMMON_ARGS}
      -DCMAKE_PREFIX_PATH:PATH=${GAMEOFLIFE_PREFIX_PATH}
      -DBUILD_opencv_core:BOOL=ON
      -DBUILD_opencv_calib3d:BOOL=ON
      -DBUILD_opencv_features2d:BOOL=ON
      -DBUILD_opencv_imgproc:BOOL=ON
      -DBUILD_opencv_video:BOOL=ON
      -DBUILD_opencv_python:BOOL=OFF
      -DBUILD_opencv_ts:BOOL=OFF
      -DBUILD_opencv_java:BOOL=OFF
      -DBUILD_opencv_nonfree:BOOL=${OPENCV_WITH_NONFREE}
      -DBUILD_DOCS:BOOL=OFF
      -DBUILD_DOXYGEN_DOCS:BOOL=OFF
      -DBUILD_PERF_TESTS:BOOL=OFF
      -DWITH_CUDA:BOOL=OFF
      -DWITH_QT:BOOL=OFF
      -DWITH_EIGEN:BOOL=OFF
      -DWITH_FFMPEG:BOOL=${OPENCV_WITH_FFMPEG}
      -DADDITIONAL_C_FLAGS:STRING=${OPENCV_ADDITIONAL_C_FLAGS}
      -DADDITIONAL_CXX_FLAGS:STRING=${OPENCV_ADDITIONAL_CXX_FLAGS}
      ${additional_cmake_args}
    CMAKE_CACHE_ARGS
      ${EP_COMMON_CACHE_ARGS}
    CMAKE_CACHE_DEFAULT_ARGS
      ${EP_COMMON_CACHE_DEFAULT_ARGS}
    DEPENDS ${proj_DEPENDENCIES}
  )

  set(OpenCV_DIR ${proj_INSTALL})
  set(GAMEOFLIFE_PREFIX_PATH ${proj_INSTALL}^^${GAMEOFLIFE_PREFIX_PATH})
  mitkFunctionInstallExternalCMakeProject(${proj})

  message("SuperBuild loading OpenCV from ${OpenCV_DIR}")

else()

  mitkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")

endif()

