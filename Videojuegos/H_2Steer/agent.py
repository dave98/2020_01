# Taken from https://github.com/wdonray/Steering-Behaviors for educational porpuse
# I just make some little changes
import math
import random
import pygame

from constants import *
from vector import Vector2 as Vec2

random.seed()

class Agent(object):
    def __init__(self, position, initial_id):
        # Initialization
        self.pos = position
        self.velocity = Vec2(0, 0)
        self.acceleration = Vec2(0, 0)
        self.targetpos = Vec2(0, 0)
        self.force = Vec2(0, 0)
        self.wander_angle = 45.0
        self.heading = Vec2(0, 0)
        self.max_velocity = 300

        self.neighbors_pos = [] ##
        self.my_id = initial_id          ##

        self.direction = self.velocity.direction
        self.surface = pygame.Surface((50, 30), pygame.SRCALPHA)

        if not initial_id:
            pygame.draw.lines(self.surface, RED, True, [(10, 5), (40, 15), (10, 25)], 2)
        else:
            pygame.draw.lines(self.surface, BLACK, True, [(10, 5), (40, 15), (10, 25)], 2)
        #pygame.draw.circle(self.surface, RED, (25, 15), 4)

        self.font = pygame.font.SysFont('mono', 12)
        self.wanderforce = None

        self.indseek = False
        self.indflee = False
        self.indwander = False
        #New behaviors
        self.indarrive = False
        self.indstop = False
        self.indseparate = False
        self.indseparate_state_1 = True
        self.indseparate_state_2 = False

        self.indcohesion = False
        self.indalineation = False

        self.with_debug = False # Show Extra Information
        self.with_lines = False
        self.line_extension = 0.3

    def set_target(self, target): # Objective (My mouse)
        self.targetpos = Vec2(target[0], target[1])

    def set_others_pos(self, others_pos, my_id):
        self.neighbors_pos = others_pos
        self.my_id = my_id

    def set_substate_default(self): # Return to normal
        self.indseparate_state_1 = True
        self.indseparate_state_2 = False


    def seek(self, target):
        displacement = target - self.pos
        force = displacement.direction * self.max_velocity
        seekforce = force - self.velocity
        return seekforce

    def arrive(self, target):
        slowing_distance = 750.0
        displacement = target - self.pos
        distance = math.sqrt( math.pow(displacement.getx(), 2) + math.pow(displacement.gety(), 2) ) # 500 minimun distance
        ramped_speed = self.max_velocity * (distance / slowing_distance)
        clipped_speed = min(ramped_speed, self.max_velocity)
        force = displacement.direction * clipped_speed
        seekforce = force - self.velocity
        return seekforce

    def flee(self, target):                                           # Flee behavior
        displacement = target - self.pos
        force = displacement.direction * self.max_velocity * -1
        fleeforce = force - self.velocity
        return fleeforce

    def wander(self, distance, radius):                               # Wander behavior
        center_circle = self.velocity.get_direction()
        center_circle = center_circle * distance

        displacement = self.velocity.get_direction()
        displacement = Vec2(0, 1) * radius
        self.wander_angle += (random.random() * 1.0 - (1.0 * .5))
        displacement.xpos = math.cos(self.wander_angle) * displacement.get_mag()
        displacement.ypos = math.sin(self.wander_angle) * displacement.get_mag()
        self.wanderforce = center_circle + displacement
        return self.wanderforce

    def stop(self, target):
        return self.arrive(target)

    def separate(self, target, extern_targets, id):                                          # Separate Behavior
        displacement = target - self.pos
        force = displacement.direction * self.max_velocity
        seekforce = force - self.velocity
        return seekforce

    def cohesion(self, target, extern_targets, id):                                          # Cohesion Behavior
        velocity_to_new_substate = 30.0
        distance_to_new_substate = 50
        if self.indseparate_state_1:
            if ((self.pos - self.neighbors_pos[0]).get_mag() < distance_to_new_substate) and (self.velocity.get_mag() < velocity_to_new_substate):
                if self.my_id != 0:
                    self.indseparate_state_1 = False
            return self.arrive(self.neighbors_pos[0])
        else:
            return self.stop(self.pos)


    def alineation(self, target):                                                              # Seek Behavior
        displacement = target - self.pos
        force = displacement.direction * self.max_velocity
        seekforce = force - self.velocity
        return seekforce

    def draw(self, screen):
        # Drawing object
        middle = Vec2(self.pos.xpos + self.surface.get_width() /2,
                      self.pos.ypos + self.surface.get_height() / 2)

        lineseek = Vec2(middle.xpos + self.velocity.direction.xpos * self.velocity.get_mag() * self.line_extension,
                        middle.ypos + self.velocity.direction.ypos * self.velocity.get_mag() * self.line_extension)
        lineflee = Vec2(middle.xpos + self.velocity.direction.xpos * self.velocity.get_mag() * -1 * self.line_extension,
                        middle.ypos + self.velocity.direction.ypos * self.velocity.get_mag() * -1 * self.line_extension)
        linewander = Vec2(middle.xpos + self.wanderforce.xpos / 6,
                          middle.ypos + self.wanderforce.ypos / 6)

        #Drawing lines
        if self.with_lines:
            pygame.draw.line(screen, RED, middle.value, lineflee.value, 1)
            pygame.draw.line(screen, BLUE, middle.value, lineseek.value, 1)
            pygame.draw.line(screen, BLACK, middle.value, linewander.value, 1)

        if self.with_debug:
            textpos = "Pos: <{:0.5}{}{:1.5}>".format( self.pos.xpos, ", ", self.pos.ypos)
            surfacep = self.font.render(textpos, True, (0, 0, 0))
            screen.blit(surfacep, (self.pos.xpos - 50, self.pos.ypos + 50))

            targetpos = "TargetPos: <{0:.5} {1:.5}>".format( str(self.targetpos.xpos), str(self.targetpos.ypos))
            surfacet = self.font.render(targetpos, True, (0, 0, 0))
            screen.blit(surfacet, (self.pos.xpos - 50, self.pos.ypos + 60))

            velpos = "Velocity: <{0:.5} {1:.5}>".format( str(self.velocity.xpos), str(self.velocity.ypos))
            surfacev = self.font.render(velpos, True, (0, 0, 0))
            screen.blit(surfacev, (self.pos.xpos - 50, self.pos.ypos + 70))


        # This part shouldnt be here, each agent is drawing it!. But it look cool so anyway...
        howpos = "Steering Behavior created by Williams, Donray"
        surfaceh = self.font.render(howpos, True, (0, 0, 0))
        screen.blit(surfaceh, (10, screen.get_height() - 40))

        howpos_2 = "New Behaviors added by Dave"
        surfaceh_2 = self.font.render(howpos_2, True, (0, 0, 0))
        screen.blit(surfaceh_2, (10, screen.get_height() - 20))

        inspos = "z = Show lines / d = Show extra information"
        surfaceh = self.font.render(inspos, True, (0, 0, 0))
        screen.blit(surfaceh, (screen.get_width() - 450, screen.get_height() - 60))

        inspos = "F1 = Buscar / F2 = Huir / F3 = Deambular / F4 = Correr / F5 = Arrive"
        surfaceh = self.font.render(inspos, True, (0, 0, 0))
        screen.blit(surfaceh, (screen.get_width() - 450, screen.get_height() - 40))

        inspos = "F6 = Stop / F7 = Separate / F8 = Cohesion / F9 = Alineation"
        surfaceh = self.font.render(inspos, True, (0, 0, 0))
        screen.blit(surfaceh, (screen.get_width() - 450, screen.get_height() - 20))


        rotate = pygame.transform.rotate( self.surface, -180 * math.atan2(self.heading[1], self.heading[0]) / math.pi)
        self.heading = Vec2.get_direction(self.velocity)
        screen.blit(rotate, (self.pos.xpos, self.pos.ypos))



    def update(self, deltatime):
        # Agent States
        if self.indseek is True:
            self.force = self.seek(self.targetpos)
        elif self.indflee is True:
            self.force = self.flee(self.targetpos)
        elif self.indwander is True:
            self.force = self.wander(250, 250)
        elif self.indarrive is True:    #Adding new behaviors
            self.force = self.arrive(self.targetpos)
        elif self.indstop is True:
            self.force = self.stop(self.pos)
        elif self.indseparate is True:
            self.force = self.separate(self.targetpos, self.neighbors_pos, self.my_id)
        elif self.indcohesion is True:
            self.force = self.cohesion(self.targetpos, self.neighbors_pos, self.my_id)
        elif self.indalineation is True:
            self.force = self.alineation(self.targetpos)
        elif self.indseek is False or self.indflee is False or self.indwander is False or self.indarrive is False or self.indstop is False or self.indseparate is False or self.indcohesion is False or self.indalineation is False:
            self.force = self.seek(self.targetpos) * 25 + self.flee(self.targetpos) + self.wander(100, 100) # WTF

        # Behaviors when out of screen
        if (self.pos.xpos >= SCREEN.get_width() or
                (self.pos.ypos >= SCREEN.get_height())):
            self.pos.xpos = SCREEN.get_width() / 2
            self.pos.ypos = SCREEN.get_height() / 2

        elif self.pos.xpos <= 0 or self.pos.ypos <= 0:
            self.pos.xpos = SCREEN.get_width() / 2
            self.pos.ypos = SCREEN.get_height() / 2

        self.acceleration = self.force
        self.velocity += self.acceleration * deltatime

        if self.velocity.get_mag() > self.max_velocity:
            self.velocity = self.velocity.direction * self.max_velocity

        self.direction = self.velocity.direction
        self.pos += self.velocity * deltatime



if __name__ == "__main__":
    import main as Main
    Main.main()
