# Taken from https://github.com/wdonray/Steering-Behaviors for educational porpuse
# I just make some little changes

import pygame

PINK = (255, 153, 255)
MAROON = (128, 0, 0)
YELLOW = (255, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
CLOCK = pygame.time.Clock()
SCREEN = pygame.display.set_mode((1300, 700), pygame.FULLSCREEN)

if __name__ == "__main__":
    import main as Main
    print(pygame.FULLSCREEN)

    Main.main()
