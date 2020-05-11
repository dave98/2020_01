import random

from agent import Agent
from constants import *
from steeringbehavior import SteeringBehavior
from vector import Vector2

random.seed()

def main():
    game = SteeringBehavior("Steering Behaviors")
    number_of_actors = 10
    for x in range(number_of_actors):
        game.addtobatch(Agent(Vector2(0.0 + (random.randint(0, SCREEN.get_width())),
                                      0.0 + (random.randint(0, SCREEN.get_height()))),
                                      x )) # x is initial_id 

    game.run()


if __name__ == "__main__":
    main()
