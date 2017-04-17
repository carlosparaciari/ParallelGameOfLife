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
#include "golSerialGame.h"
#include <vector>

// This class is used to test the protected methods of the SerialGame class.
GAMEOFLIFE_WINEXPORT class TestProtectedSerialGame : public gol::SerialGame {

  public:

  	// The constructor of SerialGame is used for this test class
  	using SerialGame::SerialGame;

  	int test_count_alive_neighbours(int x_coord, int y_coord, gol::frame & current_frame) {
  		return count_alive_neighbours(x_coord, y_coord, current_frame);
  	}

  	gol::cell test_change_state_cell(int alive_neighbours, gol::cell current_state) {
  		return change_state_cell(alive_neighbours, current_state);
  	}

};

TEST_CASE( "The method to change state of a cell is tested for different numbers of near alive cells", "[change_state]" ) {

	gol::game_parameters game_settings;
  TestProtectedSerialGame change_state_example(game_settings);

  SECTION( "Underpopulation") {
	  REQUIRE( change_state_example.test_change_state_cell(0, gol::alive) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(1, gol::alive) == gol::dead );
  }

  SECTION( "Stability") {
	  REQUIRE( change_state_example.test_change_state_cell(2, gol::alive) == gol::alive );
  	REQUIRE( change_state_example.test_change_state_cell(3, gol::alive) == gol::alive );
  }

  SECTION( "Overpopulation") {
	  REQUIRE( change_state_example.test_change_state_cell(4, gol::alive) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(5, gol::alive) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(6, gol::alive) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(7, gol::alive) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(8, gol::alive) == gol::dead );
  }

  SECTION( "Reproduction") {
	  REQUIRE( change_state_example.test_change_state_cell(3, gol::dead) == gol::alive );
  }

  SECTION( "Other") {
  	REQUIRE( change_state_example.test_change_state_cell(0, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(1, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(2, gol::dead) == gol::dead );
	  REQUIRE( change_state_example.test_change_state_cell(4, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(5, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(6, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(7, gol::dead) == gol::dead );
  	REQUIRE( change_state_example.test_change_state_cell(8, gol::dead) == gol::dead );
  }

}

TEST_CASE( "Test for the method which count the number of alive nearest-neighbour cells", "[alive_nearest]" ) {

	gol::game_parameters game_settings;
	game_settings.number_x_cells = 3;
	game_settings.number_y_cells = 3;
  TestProtectedSerialGame alive_nearest_example(game_settings);

  int obtained_number;

  SECTION( "The frame is empty." ) {
    gol::frame current_frame;
    REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) );
  }

  SECTION( "The frame size is wrong - small along y." ) {
    gol::frame current_frame(3, std::vector<gol::cell>(2, gol::dead));
    REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) );
  }

  SECTION( "The frame size is wrong - small along x." ) {
    gol::frame current_frame(1, std::vector<gol::cell>(3, gol::dead));
    REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) );
  }

  SECTION( "The frame size is wrong - big along y." ) {
    gol::frame current_frame(3, std::vector<gol::cell>(4, gol::dead));
    REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) );
  }

  SECTION( "The frame size is wrong - big along x." ) {
    gol::frame current_frame(5, std::vector<gol::cell>(3, gol::dead));
    REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) );
  }

  gol::frame current_frame(3, std::vector<gol::cell>(3, gol::dead));
  current_frame[0][1] = gol::alive;
  current_frame[2][2] = gol::alive;

	SECTION( "Out of boundaries.") {
	  REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(-1, 0, current_frame) );
	  REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(5, 2, current_frame) );
	  REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(1, -2, current_frame) );
	  REQUIRE_THROWS( obtained_number = alive_nearest_example.test_count_alive_neighbours(0, 4, current_frame) );
  }

  SECTION( "Boundaries.") {
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(0, 0, current_frame) == 1 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(0, 1, current_frame) == 0 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(0, 2, current_frame) == 1 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(2, 0, current_frame) == 0 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(2, 1, current_frame) == 1 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(2, 2, current_frame) == 0 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(1, 0, current_frame) == 1 );
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(1, 2, current_frame) == 2 );
  }

  SECTION( "Internal.") {
	  REQUIRE( alive_nearest_example.test_count_alive_neighbours(1, 1, current_frame) == 2 );
  }

}
