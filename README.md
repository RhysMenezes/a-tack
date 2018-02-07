# @tack

@tack is a 2d ASCII strategy game, where the player is tasked with eliminating enemy AI by making strategic moves in levels that they can create themselves. Though the use of a wide range of smart AI's, players are tested on their ability to plan and make decisions to see who can earn the best score. Players can also experiment by creating their own levels to test their ability and the different AI's capabilities. @tack's straightforward and fun gameplay carries a deep amount of complexity that makes it easy to learn and hard to master.

## Installation and running
@tack has no dependencies, just follow:
```
cd build
make
./@tack
```
## Levels
You can create levels by making text files in the `levels` folder with the following format:
```
10 (width)
10 (height)
......
*.....
...@..
......
```
The different objects are representated by:
- `@` : The player.
- `*` : A normal enemy.
- `X` : A bishop.
- `+` : A rook.
- `#` : A wall.

# 
Made by [Rhys Menezes](https://github.com/RhysMenezes) and [Dallas McNeil](https://github.com/DallasMcNeil).
