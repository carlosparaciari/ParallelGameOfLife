/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golInOutFrames.h"
#include "golSerialSharedGame.h"
#include "golBasicTypes.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

// A helper function to simplify the help command.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

/**
 * \brief Run the Game of Life.
 * \ingroup applications
 */
int main(int argc, char** argv) {

  try {

    std::string configuration_filename;
    std::string seed_filename;

    // Allowed options, shown in the help.
    boost::program_options::options_description desc("Options");

    desc.add_options()
      ("help,h", "produce help message")
      ("config,c", boost::program_options::value< std::string >(&configuration_filename)->default_value("config.dat"),
        "the file with the configuration parameters used in the game")
    ;

    // Hidden options, are allowed on command line, but are not shown to the user.
    boost::program_options::options_description hidden("Hidden options");

    hidden.add_options()
      ("input-file", boost::program_options::value< std::vector<std::string> >(),
        "the file (Life 1.06 format) with the initial frame of the game")
    ;

    boost::program_options::options_description cmdline_options;
    cmdline_options.add(desc).add(hidden);

    boost::program_options::positional_options_description p;
    p.add("input-file", -1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
      std::cout << "Usage: options_description [options]" << std::endl;
      std::cout << desc;  // The helper function is used by the help to print the list of commands.
      return 0;
    }

    if (vm.count("input-file")) {

      auto input_filenames = vm["input-file"].as<std::vector<std::string>>();

      if (input_filenames.size() != 1) {
        std::cerr << "Provide a single seed file to the game." << std::endl;
        return 1;
      }

      seed_filename = input_filenames[0];

    }

    gol::InOutFrames framer(seed_filename, configuration_filename);
    gol::game_parameters game_settings;

    // ---------------------------- Load the parameters of the game and create yaml file for script ---------------------------

    game_settings = framer.load_configuration_parameters();
    framer.save_configuration_to_file();

    // ------------------------ Load the seed frame into a matrix of cells, and evolve it of the game -------------------------

    gol::frame game_frame(game_settings.number_x_cells, std::vector<gol::cell>(game_settings.number_y_cells, gol::dead));
    framer.load_seed_frame(game_frame);
    framer.save_frame_to_file(game_frame, 0);

    gol::SerialSharedGame evolver(game_settings);

    for (int iteration = 0 ; iteration < game_settings.time_steps ; ++iteration ) {
    	evolver.evolve(game_frame);
    	framer.save_frame_to_file(game_frame, iteration + 1);
    }

  }
  catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;

}
