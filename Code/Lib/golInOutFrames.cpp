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
  InOutFrames::InOutFrames(std::string seed_file_name, std::string config_file_name) {

  	m_seed_file_name = seed_file_name;
  	m_config_file_name = config_file_name;

  	m_game_settings.number_x_cells = 5;
  	m_game_settings.number_y_cells = 5;
  	m_game_settings.time_steps = 1;

  	m_frame_file_name = "game_frames";
  	m_extension = "life";

  }

  /// Method to load the parameters from the configuration file.
	game_parameters InOutFrames::load_configuration_parameters() {

		std::fstream filein;
		filein.open( m_config_file_name );

    if ( !filein.is_open() ) {
      std::string message = std::string("The configuration file cannot be opened.");
      throw std::runtime_error(message);
    }

    std::string definition;
    std::string value;

    // This array is used to check that all fields are filled with the configuration parameters.
    std::array<int,5> fill_check;
    std::fill( fill_check.begin(), fill_check.end(), 0 );

    while ( true ) {
    	
    	std::getline(filein, definition, ' ');
    	std::getline(filein, value);

    	if ( filein.eof() )
    		break;

    	if ( definition == std::string("number_of_x_cells") ) {
        m_game_settings.number_x_cells = std::stoi( value );
        fill_check[0]++;
    	}
      else if ( definition == std::string("number_of_y_cells") ) {
        m_game_settings.number_y_cells = std::stoi( value );
        fill_check[1]++;
    	}
      else if ( definition == std::string("time_steps") ) {
        m_game_settings.time_steps = std::stoi( value );
        fill_check[2]++;
      }
      else if ( definition == std::string("output_filename") ) {
        m_frame_file_name = value;
        fill_check[3]++;
      }
      else if ( definition == std::string("extension") ) {
        m_extension = value;
        fill_check[4]++;
      }
      else {
        std::string message = std::string("There is an additional or misspelled parameter in the config file.");
      	throw std::runtime_error(message);
   		}

		}

    filein.close();

    bool all_field_filled = std::all_of( fill_check.begin(), fill_check.end(), [](int field){return field == 1;} );

    if ( !all_field_filled ) {
      std::string message = std::string("Not all fields have been filled. Please complete the configuration file.");
      throw std::runtime_error(message);
    }

    return m_game_settings;
	}

	/// Method to save the parameters into a configuration file for the video script.
	void InOutFrames::save_configuration_to_file() {

		std::fstream fileout;
	  fileout.open( "config.yaml", std::ofstream::out );

	  if ( !fileout.is_open() ) {
      std::string message = std::string("The configuration output file cannot be open.");
      throw std::runtime_error(message);
    }
    
    fileout << "number_x_cells : " << m_game_settings.number_x_cells << std::endl;
    fileout << "number_y_cells : " << m_game_settings.number_y_cells << std::endl;
    fileout << "time_steps : " << m_game_settings.time_steps << std::endl;
    fileout << "file_name : " << m_frame_file_name << std::endl;
    fileout << "extension : " << m_extension << std::endl;

  	fileout.close();
	}

	/// Method to load the seed pattern into the initial frame.
  void InOutFrames::load_seed_frame(frame & initial_frame) {

  	if ( initial_frame.empty() ) {
			std::string message = std::string("The frame is empty.");
      throw std::runtime_error(message);
		}

		bool notsame_x_size = initial_frame.size() != m_game_settings.number_x_cells;
		bool notsame_y_size = initial_frame[0].size() != m_game_settings.number_y_cells;

		if ( notsame_x_size || notsame_y_size ) {
			std::string message = std::string("The frame size is not correct.");
      throw std::runtime_error(message);
		}

  	std::fstream filein;
		filein.open( m_seed_file_name );

    if ( !filein.is_open() ) {
      std::string message = std::string("The seed file cannot be opened.");
      throw std::runtime_error(message);
    }

    std::string header;
    std::getline(filein, header);

    if ( header != std::string("#Life 1.06") ) {
      std::string message = std::string("The format of the seed file is wrong (use Life 1.06 format).");
      throw std::runtime_error(message);
    }

    int x_coordinate;
    int y_coordinate;
    int actual_x_coordinate;
    int actual_y_coordinate;
    int x_center = m_game_settings.number_x_cells / 2;
    int y_center = m_game_settings.number_y_cells / 2;

    while ( !filein.eof() ) {
    	filein >> x_coordinate >> y_coordinate;
    	actual_x_coordinate = x_center + x_coordinate;
    	actual_y_coordinate = y_center + y_coordinate;

    	bool x_condition = (actual_x_coordinate >= 0) &&
    										 (actual_x_coordinate < m_game_settings.number_x_cells);
    	bool y_condition = (actual_y_coordinate >= 0) &&
    										 (actual_y_coordinate < m_game_settings.number_y_cells);

    	if ( x_condition && y_condition )
    		initial_frame[actual_x_coordinate][actual_y_coordinate] = alive;
    }

    filein.close();
  }

  /// Method to save the current frame into an output file.
	void InOutFrames::save_frame_to_file(frame & current_frame, int iteration) {

		if ( current_frame.empty() ) {
			std::string message = std::string("The frame is empty.");
      throw std::runtime_error(message);
		}

		bool notsame_x_size = current_frame.size() != m_game_settings.number_x_cells;
		bool notsame_y_size = current_frame[0].size() != m_game_settings.number_y_cells;

		if ( notsame_x_size || notsame_y_size ) {
			std::string message = std::string("The frame size is not correct.");
      throw std::runtime_error(message);
		}

		/* This part would not be necessary as in C++11 one can use the to_string function.
		*  However, the g++ compiler provided by MinGW-32 has a known bug related to this function.
		*  Therefore, we prefer to utilse the following approach.
		*/
		std::ostringstream converter;
    converter << iteration;

		std::fstream fileout;
		std::string output_file = m_frame_file_name + std::string("_") + converter.str() + std::string(".") + m_extension;
	  fileout.open( output_file, std::ofstream::out );

	  if ( !fileout.is_open() ) {
      std::string message = std::string("The frame output file cannot be open.");
      throw std::runtime_error(message);
    }

    fileout << "#Life 1.06" << std::endl;

    int x_center = m_game_settings.number_x_cells / 2;
    int y_center = m_game_settings.number_y_cells / 2;

    for (int x_cell = 0 ; x_cell < m_game_settings.number_x_cells ; ++x_cell)
    	for (int y_cell = 0 ; y_cell < m_game_settings.number_y_cells ; ++y_cell)
    		if ( current_frame[x_cell][y_cell] == alive )
    			fileout << x_cell - x_center << " " << y_cell - y_center << std::endl;

    fileout.close();
	}

} // end namespace
