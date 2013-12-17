2013-12-14

NOTE: this repo replaces another, <a target="_blank" href="https://github.com/jmatthewgriffis/Space_Odyssey_2_-OLD_REPO-">found here</a>. It was necessary to create a new repo because the original was created to hold only a single app and the project eventually expanded to include additional apps and other files. Most of the history of the project can be viewed in the older repo.

----------

Space Odyssey 2 was and is created by me, J. Matthew Griffis, and <a target="_blank" href="https://github.com/sheva29">Mauricio Sanchez-Duque</a>, as a collaborative final project for:

Parsons MFA Design and Technology - 
Fall 2013 semester - 
Algorithmic Animation (aka "Algo")

My other work for that class can be <a target="_blank" href="https://github.com/jmatthewgriffis/griffis_algo2013">found here</a>;
Mauricio's can be <a target="_blank" href="https://github.com/sheva29/sanchez-duque_algo2013">found here</a>.

----------

Space Odyssey 2 is the follow-up to the original classic, <a target="_blank" href="http://www.openprocessing.org/sketch/93227">Space Odyssey</a>. Mauricio and I decided to build upon that game, porting it from Processing.js to openFrameworks and improving it with techniques from Algo.

HOW TO PLAY:

Build and run "Space Odyssey 2." Press SPACE to begin.

Four players control individual spaceships on the same screen using the same keyboard and work together to defeat an enemy before it consumes them all.

One button rotates the engine. One button fires the engine. One button fires the cannon.

Player 1: use Q/W/E.
<br>Player 2: use I/O/P.

Player 1 or 2: press R to restart.

Players 3 and 4 must use a second computer's keyboard, due to limitations on how many keys may be pressed simultaneously. You will need a network connection.

On the second computer:

Build and run "Space Odyssey 2 controller." Follow the instructions to set up communications between the two computers/apps.

Player 3: use Q/W/E.
<br>Player 4: use I/O/P.

Good luck!

----------

HOW ALGO IS INVOLVED:

The movement of the spaceships and bullets and the physics of all the collisions are controlled through forces using vector math. All homegrown, no Box2d.

The rotation of various elements uses trigonometry.

The starfield and the enemy visuals were created using recursion/branching/fractals.

The enemy's apperance was a sufficient performance drag for us to use an fbo (frame buffer object) to create an animated series of images and use that instead.

The enemy AI uses flocking.

The secondary background (still in development, not currently displaying) uses steering.

The communication between apps uses OSC.


-J. Matthew Griffis