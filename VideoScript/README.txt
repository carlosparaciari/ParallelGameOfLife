With the script MakeVideo.py it is possible to make a movie out of the
life files we produce with our command-line application golSerialApp.

In what follows, we present the precise set of commands needed to create
a video. The commands will produce a video of the well-known Gosper glider
gun. You can download from LifeWiki a different pattern (the file format
you need is the Life 1.06 one) and modify the config.dat file to specify
the size of the grid and the number of steps.

Starting from the build directory of the project, type the following:

>  cp .\bin\golGameApp.exe .\VideoScript\Data\
>  cd .\VideoScript\Data\
>  .\golGameApp.exe -c ..\config.dat ..\gosper_glider_gun.life
>  mv .\config.yaml ..\
>  cd ..
>  python .\MakeVideo.py
>  cd .\Video\

In the folder .\ViseoScript\Video there should be now an mp4 video called
glide_evolution.mp4.

NOTE: The script produces high-quality frames. Therefore, the size of the
video can be large if the size of the frames is big or if the number of time
steps is high. This might be a problem because in these situations, the script
uses all the available RAM, and starts swapping (which sensibly decreases the
preformances). If this is happening, you can modify the config.yaml file by
inserting two additional field, initial_frame and final_frame. In this way,
the script will produce a video starting from initial_frame and ending with
final_frame (so that you can reduce the number of frames in a way that the
script does not swap). Then, you can divide the video in several parts, and
maybe unify them subsequently. This does improve the efficiency in the cases
in which the script swaps.

