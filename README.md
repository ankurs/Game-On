# Game On
===============================================
Game On is a motion based Game controler using Cell Phones, it allows any phone to work as a motion controller (kind of like Wii Controller).
The Idea behind Game On was that todays Cell Phones have most of the hardware/sensers thats on Wii, so a Cell Phone could be used as a replacement for a Wii Contoller, Game On allows you to do so but currently just for racing games!!.

This Repo tracks code for 
* Android Application Source
* PC Server Source
* Toy Car Control Server

## Android Application Source
------------------------------------------------
* Build on Android 2.1
* Just Compile and Install
* Tested on Samsung i5801 (Apollo)

## PC Server Source
-----------------------------------------------
* Uses libX11-devel and libXtst-devel (Fedora)
* Compile -> `gcc gameon.c -o gameon -lX11 -lXtst`
* just run -> ./gameon

## Toy Car Control Server
-----------------------------------------------
* Uses [PySerial](http://pypi.python.org/pypi/pyserial), just do a `pip install pyserial`

