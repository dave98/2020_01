
import random

import pygame

from constants import *
from gametemplate import GameTemplate


class SteeringBehavior(GameTemplate):
    """Seeking Behavior."""

    def __init__(self, name):
        """Initialize."""
        super(SteeringBehavior, self).__init__()
        self.name = name
        self.gameobjects = []
        self.all_positions = []
        random.seed()

    def addtobatch(self, gameobject):
        """Add gameobjects to this game."""
        self.gameobjects.append(gameobject)

    def update_positions_for_all(self):
        self.all_positions.clear()
        for object in self.gameobjects:
            self.all_positions.append(object.pos) # Game object must have this parameter (agents).

    def update(self):
        """Update this games logic."""
        if not super(SteeringBehavior, self).update():
            return False
        if self.get_state() == "running":
            for i in self.gameobjects:
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.update(self.deltatime)
        if self.get_state() == "seek":
            for i in self.gameobjects:
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.update(self.deltatime)
        if self.get_state() == "flee":
            for i in self.gameobjects:
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.update(self.deltatime)
        if self.get_state() == "wander":
            for i in self.gameobjects:
                i.update(self.deltatime)

        if self.get_state() == "stop":
            for i in self.gameobjects:
                i.update(self.deltatime)
        if self.get_state() == "arrive":
            for i in self.gameobjects:
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.update(self.deltatime)
        if self.get_state() == "separate":
            self.update_positions_for_all() # Use this funtion only when is necessary. For example here
            for h, i in enumerate(self.gameobjects):
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.set_others_pos( self.all_positions, h)
                i.update(self.deltatime)
        if self.get_state() == "cohesion":
            self.update_positions_for_all()
            for h, i in enumerate(self.gameobjects):
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.set_others_pos( self.all_positions, h)
                i.update(self.deltatime)
        if self.get_state() == "alineation":
            for i in self.gameobjects:
                i.set_target( (pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]) )
                i.update(self.deltatime)
        return True

    def draw(self):
        """Draw all gameobjects added to this game."""
        for i in self.gameobjects:
            i.draw(self.surface)
        super(SteeringBehavior, self).draw()

    def run(self):
        """Runnning."""
        if super(SteeringBehavior, self).startup():
            while self.update():
                self.draw()
        super(SteeringBehavior, self).shutdown()


if __name__ == '__main__':
    import main as Main
    Main.main()
