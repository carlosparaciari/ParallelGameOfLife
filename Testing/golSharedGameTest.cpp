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
#include "golBasicTypes.h"
#include "golSharedGame.h"
#include <vector>

// This class is used to test the protected methods of the SharedGame class.
GAMEOFLIFE_WINEXPORT class TestProtectedSharedGame : public gol::SharedGame {

  public:

  	// The constructor of SharedGame is used for this test class
  	using SharedGame::SharedGame;

  	int test_count_alive_neighbours(int x_coord, int y_coord, gol::frame & current_frame) {
  		return count_alive_neighbours(x_coord, y_coord, current_frame);
  	}

  	gol::cell test_change_state_cell(int alive_neighbours, gol::cell current_state) {
  		return change_state_cell(alive_neighbours, current_state);
  	}

};

TEST_CASE( "test SharedGame class", "[shared]" ) {
  #ifndef _OPENMP
    REQUIRE(false);
  #endif
  REQUIRE(true);
}
