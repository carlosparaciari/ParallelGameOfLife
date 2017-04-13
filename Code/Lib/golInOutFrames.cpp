/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golInOutFrames.h"

namespace gol {

	/// The class constructor.
  InOutFrames::InOutFrames(std::string seed_file_name, std::string config_file_name) {}

  /// Method to load the parameters from the configuration file.
	game_parameters InOutFrames::load_configuration_parameters() {}

	/// Method to save the parameters into a configuration file for the video script.
	void InOutFrames::save_configuration_to_file() {}

	/// Method to load the seed pattern into the initial frame.
  void InOutFrames::load_seed_frame(frame & initial_frame) {}

  /// Method to save the current frame into an output file.
	void InOutFrames::save_frame_to_file(frame & current_frame, int iteration) {}

} // end namespace
