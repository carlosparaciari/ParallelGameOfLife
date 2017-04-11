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

set(GAMEOFLIFE_APPS
  golSerialApp
)
foreach(app ${GAMEOFLIFE_APPS})
  add_executable(${app} ${app}.cpp)
  target_link_libraries(${app} gameoflife ${ALL_THIRD_PARTY_LIBRARIES})
endforeach()
