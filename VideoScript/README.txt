Series of instruction for the example.

Starting from the build directory of the project:

>  cp .\bin\golSerialApp.exe .\VideoScript\Data\
>  cd .\VideoScript\Data\
>  .\golSerialApp.exe -c ..\config.dat ..\gosper_glider_gun.life
>  mv .\config.yaml ..\
>  cd ..
>  python .\MakeVideo.py
>  cd .\Video\

In the floder ViseoScript\Video there is an mp4 video of the game.
