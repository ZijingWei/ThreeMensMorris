## 1. What is this project.

This project implements the game three men's morris (A 3*3 board game) using Cinder. Users can have a battle with our algorithm, which, can always find the optimal step with the shortest way reaching the victory on each step.

## 2. Background Knowledge 

###### 1) The Rules of [Three Men’s Morris](https://en.wikipedia.org/wiki/Three_men%27s_morris).
The game can be seen as a slightly more complicated version of tik-tak-toe. The two players first take turn to put their pieces on any empty spots in the board, 3 pieces each, just as they would in a tik-tak-tow game. After all 6 pieces are set, however, each of them can move one of their pieces in a turn. A piece can be moved to a empty adjacent spots along the vertical, horizontal and diagonal paths on the board of the game. In this process, the player that first achieves a three-in-a-row pattern will win the game.

###### 2) Algorithms
Given a possible state in the game, this project compute, according to the rules, every possible next-step states, put them into a queue, and later generate the next-steps of these states. this project will use a hash-based node list to avoid duplication. This breadth-first graph-generating algorithm is expected to be O(# of verticles) time. This project also propose to implement a [min-max](https://en.wikipedia.org/wiki/Minimax) search strategy of the game that always takes the step that maximizes a player's chances of winning. If this project can be implemented earlier than the schedule, I plan to implement PageRank to analyse a completed game and find the most critical steps in it (This is the extra goal).

## 3. Timeline
###### Week 1.
-create classes of the project
-generate game states based on rules
-testing and debuging
###### Week 2. 
-working on the min-max algorithm to find the best move
-testing and debuging
###### week 3.
-implementing UI using cinder
###### week 4.
-testing and debuging
