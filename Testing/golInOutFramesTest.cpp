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
    int expected_number_of_file_passed = 8;
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

TEST_CASE( "Test the method which load the seed file", "[load_seed]" ) {

  std::string seed_filename;
  std::string config_filename = gol::argv[1];

  gol::frame obtained_input_seed(5, std::vector<gol::cell>(5, gol::dead));
  gol::frame expected_input_seed(5, std::vector<gol::cell>(5, gol::dead));

  expected_input_seed[1][3] = gol::alive;
  expected_input_seed[2][1] = gol::alive;
  expected_input_seed[2][3] = gol::alive;
  expected_input_seed[3][2] = gol::alive;
  expected_input_seed[3][3] = gol::alive;

  SECTION( "Load the wrong seed file - it does not exists." ) {
    seed_filename = std::string("non_existing_file.life");
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(obtained_input_seed) );
  }

  SECTION( "Load the seed file - wrong format." ) {
    seed_filename = gol::argv[7];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(obtained_input_seed) );
  }

  SECTION( "Load the seed file - bigger than expected." ) {
    seed_filename = gol::argv[6];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    correct_load_seed.load_seed_frame(obtained_input_seed);
    REQUIRE(obtained_input_seed == expected_input_seed);
  }

  SECTION( "Load the seed file, correct size." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    correct_load_seed.load_seed_frame(obtained_input_seed);
    REQUIRE(obtained_input_seed == expected_input_seed);
  }

  SECTION( "The frame which receives the seed is empty." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    gol::frame input_seed;
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(input_seed) );
  }

  SECTION( "The frame which receives the seed has a wrong size - small along y." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    gol::frame input_seed(5, std::vector<gol::cell>(4, gol::dead));
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(input_seed) );
  }

  SECTION( "The frame which receives the seed has a wrong size - small along x." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    gol::frame input_seed(3, std::vector<gol::cell>(5, gol::dead));
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(input_seed) );
  }

  SECTION( "The frame which receives the seed has a wrong size - big along y." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    gol::frame input_seed(5, std::vector<gol::cell>(6, gol::dead));
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(input_seed) );
  }

  SECTION( "The frame which receives the seed has a wrong size - big along x." ) {
    seed_filename = gol::argv[5];
    gol::InOutFrames correct_load_seed( seed_filename, config_filename );
    gol::frame input_seed(7, std::vector<gol::cell>(5, gol::dead));
    REQUIRE_THROWS( correct_load_seed.load_seed_frame(input_seed) );
  }
}

TEST_CASE( "Test the method which save the frame in a file", "[save_frame]" ) {

  std::string seed_filename = gol::argv[5];
  std::string config_filename = gol::argv[1];

  SECTION( "The frame is empty." ) {
    gol::InOutFrames save_frame_example( seed_filename, config_filename );
    gol::frame current_frame;
    REQUIRE_THROWS( save_frame_example.save_frame_to_file(current_frame, 0) );
  }

  SECTION( "The frame size is wrong - small along y." ) {
    gol::InOutFrames save_frame_example( seed_filename, config_filename );
    gol::frame current_frame(5, std::vector<gol::cell>(4, gol::dead));
    REQUIRE_THROWS( save_frame_example.save_frame_to_file(current_frame, 0) );
  }

  SECTION( "The frame size is wrong - small along x." ) {
    gol::InOutFrames save_frame_example( seed_filename, config_filename );
    gol::frame current_frame(3, std::vector<gol::cell>(5, gol::dead));
    REQUIRE_THROWS( save_frame_example.save_frame_to_file(current_frame, 0) );
  }

  SECTION( "The frame size is wrong - big along y." ) {
    gol::InOutFrames save_frame_example( seed_filename, config_filename );
    gol::frame current_frame(5, std::vector<gol::cell>(6, gol::dead));
    REQUIRE_THROWS( save_frame_example.save_frame_to_file(current_frame, 0) );
  }

  SECTION( "The frame size is wrong - big along x." ) {
    gol::InOutFrames save_frame_example( seed_filename, config_filename );
    gol::frame current_frame(7, std::vector<gol::cell>(5, gol::dead));
    REQUIRE_THROWS( save_frame_example.save_frame_to_file(current_frame, 0) );
  }

}
