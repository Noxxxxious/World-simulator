from simulator.Organisms.Animal import Animal
import random


class Tortoise(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 2, 1, True, 'T', 'simulator\\images\\tortoise.png')

    def action(self):
        if self.get_age() != 0:
            if random.randint(0, 3) == 3:
                self.move()

    def collision(self, predator):
        text = ""
        if predator.get_token() != self.get_token():
            text += str(predator.get_token()) + " attacks " + str(self.get_token()) + " "
            if predator.get_strength() > 5:
                text += str(predator.get_token()) + " wins"
                self.get_world().add_log(text)
                tmp_x = self.get_x()
                tmp_y = self.get_y()
                self.get_world().del_organism(self)
                predator.new_location(tmp_x, tmp_y)
            else:
                text += "T defends"
                self.get_world().add_log(text)
        elif self.get_age() > 3 and predator.get_age() > 3:
            self.get_world().new_organism(self)
