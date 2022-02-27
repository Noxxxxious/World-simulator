import pygame
pygame.init()


class Button:
    def __init__(self, color, text_color, text_size, x, y, width, height, text=''):
        self.color = color
        self.text_color = text_color
        self.text_size = text_size
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = text

    def draw(self, win, outline=None):
        if outline:
            pygame.draw.rect(win, outline, (self.x - 2, self.y - 2, self.width + 4, self.height + 4), 0)

        pygame.draw.rect(win, self.color, (self.x, self.y, self.width, self.height), 0)

        if self.text != '':
            font = pygame.font.Font('simulator\\fonts\\arcade_font2.ttf', self.text_size)
            text = font.render(self.text, True, self.text_color)
            win.blit(text, (self.x + (self.width / 2 - text.get_width() / 2),
                            self.y + (self.height / 2 - text.get_height() / 2)))

    def is_over(self, pos):
        if self.x < pos[0] < self.x + self.width:
            if self.y < pos[1] < self.y + self.height:
                return True
        return False

    def hover(self):
        if self.is_over(pygame.mouse.get_pos()):
            self.text_color = (150, 150, 150)
        else:
            self.text_color = (255, 255, 255)

    def click(self):
        if self.is_over(pygame.mouse.get_pos()):
            return True
        return False

    def toggle(self):
        if self.text_color == (130, 130, 130):
            self.text_color = (255, 255, 255)
        else:
            self.text_color = (130, 130, 130)
