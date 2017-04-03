/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "golCatchMain.h"
#include <iostream>

TEST_CASE( "My first test", "[init]" ) {

  int expectedNumberOfArgs = 2;
  if (gol::argc != expectedNumberOfArgs)
  {
    std::cerr << "Usage: mpMyFirstCatchTest fileName.txt" << std::endl;
    REQUIRE( gol::argc == expectedNumberOfArgs);
  }
  REQUIRE(true);
}
