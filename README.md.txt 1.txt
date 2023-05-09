## Structrure
The game uses SFML's graphics library to implement textures located within the image folder. Using sprites to present the textures as well as other classes within SFML's extensive library to detect clicks and to actively refresh.

The test boards used are simply read from the files found within the boards folder holding groups of 1s and 0s, 1s being a mine and 0s being an empty space. They are read by the program and size the play window as well as tell the program where and how many mines are located within the field using a simple 1 or 0. Users are able to create their own maps if they choose to by manually modifying one of these files


## Features
This implementation of Minesweeper includes all standard features including Flags and a mine counter which changes based on the number of flags placed or if the user wins the game it automatically puts flags on remaining mines.

Users are also able to either load in a pre-generated minefield using test boards 1, 2, or 3 using the test buttons located at the bottom right of the screen. Or load in a randomly generated minefield with 50 mines using the smiley face button located in the bottom center just like the game!

Also included is a Debug button used to reveal where all mines are located within the map any time the user chooses.

The Smiley face also acts as a status indicator as a regular smiley face means an active game but it will change to a frowning face with Xs for eyes if the user clicks on a mine and loses. Additionally, the smiley face will gain a pair of sunglasses if the user clears the map successfully!

## How to Use
To use this game you must download SFML's extensions for graphics, windows, as well as system all can be downloaded from SFML's site here https://www.sfml-dev.org/

You must also download the images folder as well as the boards folder as the former holds the textures nicely to run the game and the latter holds all the test boards files for loading


