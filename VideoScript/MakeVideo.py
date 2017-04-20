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

from datetime import datetime
start_time = datetime.now()

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

# Set the size of the figure to have 1 cell per dot
my_dpi = 96
my_width = float(config['number_x_cells'])/float(my_dpi)
my_height = float(config['number_y_cells'])/float(my_dpi)
if min( my_width, my_height ) < 10:
    my_aspect_ratio = float(config['number_y_cells'])/float(config['number_x_cells'])
    if my_width < my_height:
        my_width = 10
        my_height = my_width*my_aspect_ratio
    else:
        my_height = 10
        my_width = my_height/my_aspect_ratio
my_plot_size = (my_width, my_height)

# Define set of frames we add into the video
if 'initial_frame' in config:
    start_frame = config['initial_frame']
else:
    start_frame = 0

if 'final_frame' in config:
    end_frame = config['final_frame']
else:
    end_frame = config['time_steps']

# Configure the figure
fig = plt.figure( figsize = my_plot_size, dpi = my_dpi )
ax = plt.subplot(111)
plt.axis('off')
fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
ax.set_frame_on(False)
plt.axis('off')
centre_frame = np.array( [config['number_x_cells']/2, config['number_y_cells']/2] )

# Load the input data and create frames
video_frames = []
after_config = datetime.now()


print( ''.join( ['Time needed to configure the script : ', str(after_config - start_time)] ) )
print( 'Start reading from files and create array of figures.' )
for iterator in range( start_frame, end_frame ):
    frame = np.zeros( ( config['number_x_cells'] , config['number_y_cells'] ) , dtype = 'int' )
    file_name = ''.join( [config['file_name'], '_', str(iterator), '.', config['extension']] )
    alive_cells = np.loadtxt( os.path.join( my_path, 'Data' , file_name ), dtype = 'int' )
    centre_array = np.full( (alive_cells.size/2, 2), centre_frame, dtype = 'int' )
    alive_cells = centre_array + alive_cells;
    frame[tuple(alive_cells.T)] = 1
    video_frames.append([plt.imshow(frame.T, aspect='auto')])

# Create the video  
after_reading = datetime.now()
print( ''.join( ['Time needed to read files and create images : ', str(after_reading - after_config)] ) )
print( 'Ready to create the video.' )
my_animation = animation.ArtistAnimation( fig, video_frames, blit = True )
after_video = datetime.now()
print( ''.join( ['Time needed to create the video : ', str(after_video - after_reading)] ) )
print( 'Video created.' )
video_name = ''.join( [config['file_name'], '.mp4'] )
my_animation.save( os.path.join( my_path, 'Video', video_name ), dpi = my_dpi, writer = writer )
after_save = datetime.now()
print( ''.join( ['Time needed to save the video : ', str(after_save - after_video)] ) )
print( 'Video saved.' )
