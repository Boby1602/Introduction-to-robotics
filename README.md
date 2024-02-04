# Introduction-to-robotics
Introduction to robotics studied at University of Bucharest, section FMI. Here I will have all my homework that will carefully be sorted. Each one will have its requirements, files, code, images, videos, etc.

# Simon Says
This project is a game like "Simon says". It has these components:
  1. 6 LEDs (3 blue, 1 green, 1 red, 1 yellow)
  2. 3 push-buttons
  3. 6 resistors
  4. 1 breadboard
  5. 1 arduino uno

The project presents itself looking like this:
![SimonSays1](https://github.com/Boby1602/Introduction-to-robotics/assets/115077495/d177f506-99fd-483e-a529-e89be1925f78)


![SimonSays2](https://github.com/Boby1602/Introduction-to-robotics/assets/115077495/deb5485f-46be-4b99-b0a1-340c0419df64)

# Video
https://www.youtube.com/watch?v=hfo4mBGNPa4

# Description
The project is described in the video but I will provide a short description here as well. When we begin to play, we have the red, yellow and green pin lighting up (like a street light) to let us know the game will begin. After they turn off, a random sequence of the 3 blue LEDs begins to light up. At first, it starts with only one instance of a LED turning on, then two and so on until we reach 10 instances. The player, after the sequence is over, has to push the button for each LED to light them up in the same order they were lit up. If you manage to win the game (You win the game by guessing 10 in a row correctly) the difficulty will go up. At first, when one of the blue LEDs lights up, it stays on for 1.5 seconds. When you win, the game restarts but with half that time (So the next round will only be 0.75 seconds). This goes on forever until yoou can't keep up (So basically it will stay lit up for 1.5 seconds then 0,75; 0,375; 0,1875 etc.). However, guessing wrongly, you will restart at the beginning of the round but at the same difficulty.

# Code
You can find the code here:
https://github.com/Boby1602/Introduction-to-robotics/blob/main/Simon_Says.ino
