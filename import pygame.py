import pygame
import time
import random

# Inicializar o Pygame
pygame.init()

# Definir dimensões
width, height = 600, 400
window = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()

# Cores
black = (0, 0, 0)
white = (255, 255, 255)
red = (213, 50, 80)
green = (0, 255, 0)
blue = (50, 153, 213)

snake_block = 10
snake_speed = 15

font_style = pygame.font.SysFont(None, 50)

def message(msg, color):
    text = font_style.render(msg, True, color)
    window.blit(text, [width / 6, height / 3])

def gameLoop():
    game_over = False
    game_close = False

    x, y = width / 2, height / 2
    x_change, y_change = 0, 0

    snake = []
    snake_length = 1

    food_x = round(random.randrange(0, width - snake_block) / 10.0) * 10.0
    food_y = round(random.randrange(0, height - snake_block) / 10.0) * 10.0

    while not game_over:
        while game_close:
            window.fill(black)
            message("Perdeste! Pressiona Q para sair ou C para continuar", red)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        game_over = True
                        game_close = False
                    if event.key == pygame.K_c:
                        gameLoop()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x_change = -snake_block
                    y_change = 0
                elif event.key == pygame.K_RIGHT:
                    x_change = snake_block
                    y_change = 0
                elif event.key == pygame.K_UP:
                    y_change = -snake_block
                    x_change = 0
                elif event.key == pygame.K_DOWN:
                    y_change = snake_block
                    x_change = 0

        if x >= width or x < 0 or y >= height or y < 0:
            game_close = True
        x += x_change
        y += y_change
        window.fill(blue)

        pygame.draw.rect(window, green, [food_x, food_y, snake_block, snake_block])

        snake.append([x, y])
        if len(snake) > snake_length:
            del snake[0]

        for segment in snake[:-1]:
            if segment == [x, y]:
                game_close = True

        for segment in snake:
            pygame.draw.rect(window, white, [segment[0], segment[1], snake_block, snake_block])

        pygame.display.update()

        if x == food_x and y == food_y:
            food_x = round(random.randrange(0, width - snake_block) / 10.0) * 10.0
            food_y = round(random.randrange(0, height - snake_block) / 10.0) * 10.0
            snake_length += 1

        clock.tick(snake_speed)

    pygame.quit()
    quit()

gameLoop()
