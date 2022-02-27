from simulator.Organism import Organism
import random


class Animal(Organism):
    def __init__(self, current_world, x_coordinate, y_coordinate, strength, initiative, is_alive, token, image):
        super().__init__(current_world, x_coordinate, y_coordinate, strength, initiative, is_alive, token, image)

    @staticmethod
    def is_animal():
        return True

    def action(self):
        if self.get_age() != 0:
            self.move()

    def collision(self, predator):
        text = ""
        if predator.get_token() != self.get_token():
            text += str(predator.get_token()) + " attacks " + str(self.get_token()) + " "
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
        elif self.get_age() > 3 and predator.get_age() > 3:
            self.get_world().new_organism(self)

    def move(self):
        legal_move = False
        while not legal_move:
            x = 0
            y = 0
            direction = random.randint(0, 3)
            if direction == 0:
                y += self.get_move_dist()
                if not self.get_world().is_outside(self.get_x() + x, self.get_y() + y):
                    legal_move = True
            elif direction == 1:
                x += self.get_move_dist()
                if not self.get_world().is_outside(self.get_x() + x, self.get_y() + y):
                    legal_move = True
            elif direction == 2:
                y -= self.get_move_dist()
                if not self.get_world().is_outside(self.get_x() + x, self.get_y() + y):
                    legal_move = True
            elif direction == 3:
                x -= self.get_move_dist()
                if not self.get_world().is_outside(self.get_x() + x, self.get_y() + y):
                    legal_move = True
            if legal_move:
                if self.get_world().is_occupied(self.get_x() + x, self.get_y() + y):
                    self.get_world().get_field(self.get_x() + x, self.get_y() + y).collision(self)
                else:
                    new_x = self.get_x() + x
                    new_y = self.get_y() + y
                    self.new_location(new_x, new_y)
