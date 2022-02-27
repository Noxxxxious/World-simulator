from simulator.Organisms.Animal import Animal
import pygame

pygame.init()


class Human(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 5, 4, True, 'X', 'simulator\\images\\human.png')
        self.__shield_duration = 0
        self.__shield_cooldown = 0

    def shield_active(self):
        if self.get_shield_dur() == 0:
            return False
        return True

    def on_cooldown(self):
        if self.get_shield_cooldown() == 0:
            return False
        return True

    def get_shield_dur(self):
        return self.__shield_duration

    def get_shield_cooldown(self):
        return self.__shield_cooldown

    def set_duration(self, duration):
        self.__shield_duration = duration

    def set_cooldown(self, cooldown):
        self.__shield_cooldown = cooldown

    def action(self):
        if self.shield_active():
            self.set_duration(self.get_shield_dur() - 1)
            if self.get_shield_dur() == 0:
                text = "Alzurs Shield wears off"
                self.set_image('simulator\\images\\human.png')
                self.get_world().add_log(text)
        if self.on_cooldown():
            self.set_cooldown(self.get_shield_cooldown() - 1)
        new_x = self.get_x()
        new_y = self.get_y()
        legal_move = False
        ability_pressed = False
        while not (legal_move or ability_pressed):
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_LEFT:
                        if not self.get_world().is_outside(new_x - 1, new_y):
                            new_x -= 1
                            legal_move = True
                    elif event.key == pygame.K_RIGHT:
                        if not self.get_world().is_outside(new_x + 1, new_y):
                            new_x += 1
                            legal_move = True
                    elif event.key == pygame.K_UP:
                        if not self.get_world().is_outside(new_x, new_y - 1):
                            new_y -= 1
                            legal_move = True
                    elif event.key == pygame.K_DOWN:
                        if not self.get_world().is_outside(new_x, new_y + 1):
                            new_y += 1
                            legal_move = True
                    elif event.key == pygame.K_SPACE and not self.on_cooldown():
                        self.set_duration(5)
                        self.set_cooldown(10)
                        text = "Alzurs shield activated"
                        self.set_image('simulator\\images\\human_shield.png')
                        self.get_world().add_log(text)
                        ability_pressed = True
                    elif event.key == pygame.K_s:
                        self.get_world().save()
                elif event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
        if not ability_pressed:
            if self.get_world().is_occupied(new_x, new_y):
                self.get_world().get_field(new_x, new_y).collision(self)
            else:
                self.new_location(new_x, new_y)

    def collision(self, predator):
        text = str(predator.get_token()) + " attacks " + str(self.get_token()) + " "
        if self.shield_active():
            text += "X defends"
            self.get_world().add_log(text)
            self.get_world().del_from_map(predator)
            predator.set_position(self.get_x(), self.get_y())
            predator.move()
            self.get_world().set_field(self.get_x(), self.get_y(), self)
        else:
            if (self.get_strength() > predator.get_strength()
                    or (self.get_strength() == predator.get_strength() and self.get_age() > predator.get_age())):
                text += str(self.get_token()) + " wins"
                self.get_world().add_log(text)
                self.get_world().del_organism(predator)
            else:
                text += str(predator.get_token()) + " wins"
                self.get_world().add_log(text)
                tmp_x = self.get_x()
                tmp_y = self.get_y()
                self.get_world().del_organism(self)
                predator.new_location(tmp_x, tmp_y)
