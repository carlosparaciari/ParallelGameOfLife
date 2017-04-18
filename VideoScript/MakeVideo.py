#!/usr/bin/env python

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

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.animation as animation

import os
my_path = os.path.dirname( os.path.abspath( __file__ ) )

import yaml
config = yaml.load( open( os.path.join( my_path, 'config.yaml' ) ) )

# Initialise the class to create the video from data 
Writer = animation.writers['ffmpeg']
my_metadata = dict( title = 'Game of Life', artist = 'Carlo Sparaciari' )
writer = Writer( fps = 10, metadata = my_metadata , bitrate = -1 )

# Load the input data and create frames
video_frames = []

fig = plt.figure()
plt.axis('off')

for iterator in range( config['time_steps'] ):
    frame = np.zeros( ( config['number_x_cells'] , config['number_y_cells'] ) , dtype = 'int' )
    file_name = ''.join( [config['file_name'], '_', str(iterator), '.', config['extension']] )
    alive_cells = np.loadtxt( os.path.join( my_path, 'Data' , file_name ), dtype = 'int' )
    centre_array = np.full( (alive_cells.size/2, 2), np.array( [config['number_x_cells']/2, config['number_y_cells']/2] ), dtype = 'int' )
    alive_cells = centre_array + alive_cells;
    frame[tuple(alive_cells.T)] = 1
    video_frames.append([plt.imshow(frame)])

# Create the video  
my_animation = animation.ArtistAnimation( fig, video_frames, blit = True )
video_name = ''.join( [config['file_name'], '.mp4'] )
my_animation.save( os.path.join( my_path, 'Video', video_name ), writer = writer )
