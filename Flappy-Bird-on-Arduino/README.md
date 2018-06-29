# Flappy-bird-on-Arduino

Play the famous 'Flappy Birds' game on the Arduino Touchscreen Shield.
Click [here](https://www.hackster.io/techmirtz/the-flappy-bird-on-arduino-6e4c4f) to open the Hackster project.

## Overview
This is a very simple project as far as the hardware is concerned ,and commonly available on internet. This is interesting to share with you all. On the Arduino Mega 2560 directly place the Arduino TFT LCD Touch Screen display. The program is inserted into the Arduino Mega.

The game is quite simple but interesting and addictive. Using the touch screen we control the bird and try to avoid the moving pillars which speed increase as we progress. Also the game can store your highest score even if you unplug the power.

## How "Flappy Bird" works
The "flappy" object is located in a fixed position on the **X-axis** while actions are performed by moving the **Y-axis.**

When you touch the keys or the display object, Flappy moves to -10 px Y-axis. Obstacles appear. Flappy either gets in contact with an obstacle or exits from the world which is dictated by the edges of the screen display. The game is stopped when Flappy stops and the message "GAME OVER" and an achieved score are displayed. Game stores your highest score even if you unplug the power using EEPROM.

We will use the **UTFT** and **URTouch** libraries made by Henning Karlsen. You can download these libraries from his website, [www.RinkyDinkElectronics.com](http://www.rinkydinkelectronics.com/). Also we will use the **EEPROM library** for storing the highest score in the EEPROM. The EEPROM is a memory which can store data even when the board is turned off.

After we have included the libraries we need to create the **UTFT** and **URTouch objects** as well as define the variables needed for the game. In the setup section we need to initiate the display and the touch, read the highest score from the EEPROM and initiate the game using the **initiateGame()** custom function.

So with the **initiateGame()** custom function we will draw the initial state of the game and here’s how we will do that. First we need to clear the screen, then draw the blue background, draw the bottom section, add the text and call the **drawBird()** custom function to draw the bird. After this we need a while loop which will prevent the game to start until we tap the screen. So while we are at this state, if we press the upper right corner we can reset the highest score to zero and if we press anywhere else on the screen we will get out of the while loop and get into the main loop of the code which will start the game.

In the main loop section we have the **xP variable** which is used for drawing the pillars, as well as the **yP variable.** At the beginning, the xP variable has the value of 319 as the size of the screen and the yP variable has the value of 100 which is the height of the first pillar. Each iteration the value of the xP variable is decreased by the value of the movingRate variable which at the beginning has the value of 3 and as we progress the game it increases.

Here’s the working principle of game: we have 50 pixels wide pillars which move from right to left and every next pillar has a different random height. In order to make them moving, logically, after each iteration we need to clear the screen and redraw the graphic with the pillars at their new position. However, we cannot do that because of the low refresh rate of the screen, which would cause flickering of the graphics. In order to activate all of its pixels the screen needs a bit more time so therefore we will have to improvise and redraw just those things that are moving.

So let’s take a look how the **drawPilars()** custom function will do that. It takes the **xP and yP** variables and using them and the **fillRect()** function it will draw the pillars. So each iteration it draws the pillars at their new location with additional blue rectangles from their left and right side which clear the previous drawn pillar and in that way we actually do the improvisation of just redrawing the moving pillars. The if statements here are an additional improvisation because for some reason the **fillRect()** function didn’t work if its ‘x2’ parameter had a value out of the screen size. Also, at the end of this custom function we need to print the value of reached score.

Back in the loop section we have the yB variable which is the y position of the bird and it depends on the falling rate which after each iteration is increased and in that way we get the effect of acceleration or gravity. Also, here we check for collisions and use the if statements to confine the bird so that if it hit the top, the ground or the pillars the game will over.

Next is the **drawBird()** custom function and let’s see how it works. The bird is actually a photo which is converted into a bitmap using the **ImageConverter565 tool** made by Henning Karlsen. The “.c” file which is created using the tool needs to be included in the directory so that it load when launching the sketch. Also we have to define the bitmap like this and using the **drawBitmap() function** we will draw the photo on the screen. The bird has a fixed X – coordinate and the yB variable as Y – coordinate. Similar to the pillars we will clear the previous state of the bird by drawing two blue rectangles above and under the bird.

Back in the loop we can see that after the pillar has passed through the screen the xP variable will be reset to 319, yP will get new random value from 20 to 100 for the height of the pillars and the score will increase by one. With the next if statement we control the bird. If we tap the screen we will set the falling rate to negative what will make the bird jump and the else if statement will not allow to happen that if we just hold the screen. The last if statement is for the difficulty of the game and it increase the moving rate of the pillars after each fine points.

Ok what’s left now is to see how the **gameOver()** custom function works. After a delay of one second it will clear the screen, print the score and some text, if score is higher than the highest score it will write it down into the EEPROM, it will reset all variables to their starting position values and at the end it will call the **initiateGame()** custom function to restart the game.

