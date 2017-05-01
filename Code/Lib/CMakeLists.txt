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

set(GAMEOFLIFE_SRCS
  golBasicTypes.cpp
  golInOutFrames.cpp
  golSerialGame.cpp
  golSharedGame.cpp
)

add_library(gameoflife ${GAMEOFLIFE_SRCS})

if(BUILD_SHARED_LIBS)
  if(WIN32)
    add_definitions(-DGAMEOFLIFE_WINDOWS_EXPORT)
  endif(WIN32)
endif(BUILD_SHARED_LIBS)

target_link_libraries(gameoflife PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})
