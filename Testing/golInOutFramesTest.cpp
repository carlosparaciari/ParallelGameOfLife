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
#include "golInOutFrames.h"
#include "golBasicTypes.h"
#include <string>
#include <array>
#include <fstream>
#include <algorithm>

TEST_CASE( "Test the files with configuration parameters and seed", "[input_files]" ) {

  SECTION( "Test if the number of input files is correct" ) {
    int expected_number_of_file_passed = 7;
    REQUIRE( gol::argc == expected_number_of_file_passed );
  }

  SECTION( "Test if the input files can be opened" ) {
    std::fstream filein;
    for ( int i = 1 ; i < gol::argc ; ++i) {
      filein.open( gol::argv[i] );
      REQUIRE( filein.is_open() );
      filein.close();
    }
  }

}

TEST_CASE( "Test the method which load the configuration parameters", "[load_config]" ) {

  gol::game_parameters obtained_parameters;
  gol::game_parameters expected_parameters;

  expected_parameters.number_x_cells = 5;
  expected_parameters.number_y_cells = 7;
  expected_parameters.time_steps = 10;

  std::string seed_filename = gol::argv[5];
  std::string config_filename;

  SECTION( "Load the wrong configuration file - it does not exists." ) {
    config_filename = std::string("non_existing_file.dat");
    gol::InOutFrames correct_load_config( seed_filename, config_filename );
    REQUIRE_THROWS( obtained_parameters = correct_load_config.load_configuration_parameters() );
  }

  SECTION( "Load the wrong configuration file - one parameter more that expected." ) {
    config_filename = gol::argv[2];
    gol::InOutFrames correct_load_config( seed_filename, config_filename );
    REQUIRE_THROWS( obtained_parameters = correct_load_config.load_configuration_parameters() );
  }

  SECTION( "Load the wrong configuration file - less parameters that expected." ) {
    config_filename = gol::argv[3];
    gol::InOutFrames correct_load_config( seed_filename, config_filename );
    REQUIRE_THROWS( obtained_parameters = correct_load_config.load_configuration_parameters() );
  }

  SECTION( "Load the wrong configuration file - one parameter was misspelled." ) {
    config_filename = gol::argv[4];
    gol::InOutFrames correct_load_config( seed_filename, config_filename );
    REQUIRE_THROWS( obtained_parameters = correct_load_config.load_configuration_parameters() );
  }

  SECTION( "Load the correct configuration file." ) {
    config_filename = gol::argv[1];
    gol::InOutFrames correct_load_config( seed_filename, config_filename );
    obtained_parameters = correct_load_config.load_configuration_parameters();
    REQUIRE( obtained_parameters.number_x_cells == expected_parameters.number_x_cells );
    REQUIRE( obtained_parameters.number_y_cells == expected_parameters.number_y_cells );
    REQUIRE( obtained_parameters.time_steps == expected_parameters.time_steps );
  }

}
