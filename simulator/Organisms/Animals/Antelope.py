from simulator.Organisms.Animal import Animal
import random


class Antelope(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 4, 4, True, 'A', 'simulator\\images\\antelope.png')
        self.set_move_dist(2)

    def collision(self, predator):
        text = ""
        if predator.get_token() != self.get_token():
            text += str(predator.get_token()) + " attacks " + str(self.get_token()) + " "
            if random.randint(0, 1) == 0:
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
            else:
                tmp_x = self.get_x()
                tmp_y = self.get_y()
                free_space = False
                new_x = self.get_x()
                new_y = self.get_y()
                if not self.get_world().is_outside(self.get_x() - 1, self.get_y()):
                    if not self.get_world().is_occupied(self.get_x() - 1, self.get_y()):
                        new_x -= 1
                        free_space = True
                if not self.get_world().is_outside(self.get_x() + 1, self.get_y()) and not free_space:
                    if not self.get_world().is_occupied(self.get_x() + 1, self.get_y()):
                        new_x += 1
                        free_space = True
                if not self.get_world().is_outside(self.get_x(), self.get_y() - 1) and not free_space:
                    if not self.get_world().is_occupied(self.get_x(), self.get_y() - 1):
                        new_y -= 1
                        free_space = True
                if not self.get_world().is_outside(self.get_x(), self.get_y() + 1) and not free_space:
                    if not self.get_world().is_occupied(self.get_x(), self.get_y() + 1):
                        new_y += 1
                        free_space = True
                if free_space:
                    text += "A escapes"
                    self.get_world().add_log(text)
                    self.new_location(new_x, new_y)
                    predator.new_location(tmp_x, tmp_y)
                    predator.get_world().set_field(tmp_x, tmp_y, predator)
        elif self.get_age() > 3 and predator.get_age() > 3:
            self.get_world().new_organism(self)
