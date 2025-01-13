# Cube_Solver_Robot

This work was created as part of a project in my mechatronics course at Hochschule Wismar, University of Applied Sciences: Technology, Business and Design. 
I worked on it together with a friend of mine. 

It's a Robot which can scan and solve a Rubik's Cube. It's possible to take out the Cube and twitch it by yourself. If you don't want to twist it by yourself, we have a mode which will turn it for you randomly with 20 moves.

The Robot have two main modes: Automatic and external.
Those modes are explained in a special PDF which you can find in the Repo.

The automatic mode solves the cube using an algorithm we wrote ourselves. It is based on the manual solution method, as a human would solve it.
This Code can be found under the following link: 

[Repo](https://github.com/snech99/Cube_Solver_Algorithm)

For external communication, the algorithm must be written by the user. There is a Python template for this, which communicates with the robot via a C program.
Download the folder /src/external_PC and compile the C program with make. You can then start the program as follows:

```bash
sudo ./main my_script
```


