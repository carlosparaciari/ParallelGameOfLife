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

set(DATA_DIR ${CMAKE_SOURCE_DIR}/Testing/Data)
set(TMP_DIR ${CMAKE_BINARY_DIR}/Testing/Temporary)

set(TEST_CASES
  golInOutFramesTest
  golSerialSharedGameTest
  golDistributedGameTest
)

foreach(_test_case ${TEST_CASES})
  add_executable(${_test_case} ${_test_case}.cpp golCatchMain.cpp)
  target_link_libraries(${_test_case} ${ALL_LIBRARIES})
endforeach()

# Adding tests is done outside the above loop,
# as each test will need different arguments.

##################################################################################################
# Dont forget its:  add_test(<test name (globally unique) > <exe name> <argument1> <argument2>
##################################################################################################

add_test(InOut ${EXECUTABLE_OUTPUT_PATH}/golInOutFramesTest ${DATA_DIR}/correct_config.dat
															${DATA_DIR}/wrong_config_extra_element.dat
															${DATA_DIR}/wrong_config_missing_element.dat
															${DATA_DIR}/wrong_config_misspell.dat
															${DATA_DIR}/correct_seed.life
															${DATA_DIR}/wrong_seed.life
															${DATA_DIR}/wrong_format_seed.rle)
add_test(Serial ${EXECUTABLE_OUTPUT_PATH}/golSerialSharedGameTest)
add_test(Distributed ${EXECUTABLE_OUTPUT_PATH}/golDistributedGameTest)
