# Awesome Pinball
by There can only be two.

Inspired by the 3D Pinball for Windows - Space Cadet https://alula.github.io/SpaceCadetPinball/

Link of the Github Repository: https://github.com/There-can-only-be-two/Pinball

## Developers
- Xavi Alcañiz Carrillo (@StarvinXarvin)
- Héctor Báscones Zamora (@Hekbas)
- Jan Neto Llorens (@JanNetoLlorens)
- Júlia Serra Trujillo (@softdrawss)

## Keys
- LEFT AND RIGHT ARROWS: Flippers
- DOWN ARROW: Kicker
- SPACE: Go through scenes
- ESC: Quit

### Debug
- TAB: Enables and displays the following debug functionality
  - F1: Draws all colliders and allow to use a mouse joint
  - F2: Turn the lights of the pinball ON/OFF
  - F3: Turn the music of the pinball ON/OFF
  - Frame Control: (Q-/E+)
  - Gravity: (S-/W+)
  - Bounce coef: (A-/D+)
  - V: Displays the following variables - Ball(x, y), Spring force, Gravity and Bounce coef
  - F: Finishes the game and displays rankings
  - U: Change display of the UI
  - R: Resets ranking to default (Only after the game has finished and the ranking is displayed)

## Information
- AMOUNT OF BALLS PER GAME: 3 balls
  - Number of balls remaining is displayed at the bottom of the pinball.
- TIME: Even though game finishes when the player is out of balls, it can also finish when the player is out of time.
  - Time remaining is displayed at the bottom left of the pinball.
  
## Combos and Feautures
- EXTRA KIKCERS: Automatically shoots the ball when touched. Once activated, the kicker used turns off and will not activate again.
- EXTRA TIME: Passing through the Time feauture rewards the player extra time. However, Extra Time cancels the X2 multiplier and equals it to 1.
- MULTIPLIER: 
  - X2: Activating the three parts in the upper right zone of the map will sum 2 to the current value of the multiplier.
  - X10: Activating the three parts in the upper right zone of the map will temporally sum 10 to the current value of the multiplier.
- LIGHTS: Lights will turn on and off when ball bounces, parts of the pinball are activated, etc.
- RANKING: When the game finishes, the ranking displays the TOP 5 scores of the game. Scores by player are displayed in yellow. Try to get to TOP 1!
- UI: Highscore, Current Score, Multiplier, Previous Score, Time remaining, Balls remaining

## Development
During the development of the Pinball, we had some bugs with little details. For example, we had an issue at the end of the game, when displaying the ranking, as everytime that we clicked ESC in order to quit the game showed an execution. After revising our code, we saw that it was a little issue in the ModuleScene. Someone had written two time "sensorDeath = nullptr" and never "sensorTime = nullptr", and that created an interrumption in the code.

Another moment that we dealt with similar circumstances was when we changed the collider of the map to make the ball fall. We started at first without any space for the ball to fall, but eventually we changed it in order to make it look more appealing and similar to a Pinball. However, when we changed the points for the chain in Vertex Box 2D, someone did two times the same point which created a big interrumption in the code when the .exe started, but after some revising we found it.

We had to be very organized. With colliders and sensors, the CleanUp() is almost 75 lines, so we created lots of Modules, subdivisions, functions, etc. We even did a very organized Discord server to keep on track bugs, ideas, license of the assets, links and useful stuff.

Sometimes one of us had another idea to write some code, and we can see that in some functions related to UI and how do you display the scores. And sometimes we had trouble at contacting as most of us do extracurricular activities of had other events during the afternoon. But we made sure everyone understood code of everything, that all of us did code and editing (related to the assets, the background, etc which can be boring sometimes) as each of us had different aproaches and we made sure to keep in mind and listen to everyone's opinion and ideas.

Overall, even the bugs and issues we found eventually during development, we spent lots of hours coding, editing and testing in class and as a group we are very happy with the result. - There can only be two
