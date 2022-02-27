from simulator.Organisms.Animal import Animal
import random


class Fox(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 3, 7, True, 'F', 'simulator\\images\\fox.png')

    def scan_neighbors(self):
        if (self.get_world().is_outside(self.get_x() - 1, self.get_y())
                or not self.is_stronger(self.get_x() - 1, self.get_y())):
            if (self.get_world().is_outside(self.get_x() + 1, self.get_y())
                    or not self.is_stronger(self.get_x() + 1, self.get_y())):
                if (self.get_world().is_outside(self.get_x(), self.get_y() - 1)
                        or not self.is_stronger(self.get_x(), self.get_y() - 1)):
                    if (self.get_world().is_outside(self.get_x(), self.get_y() + 1)
                            or not self.is_stronger(self.get_x(), self.get_y() + 1)):
                        return False
        return True

    def action(self):
        if self.get_age() != 0:
            if self.scan_neighbors():
                self.move()

    def move(self):
        legal_move = False
        while not legal_move:
            x = 0
            y = 0
            direction = random.randint(0, 3)
            if direction == 0:
                y += self.get_move_dist()
                if (not self.get_world().is_outside(self.get_x() + x, self.get_y() + y)
                        and self.is_stronger(self.get_x() + x, self.get_y() + y)):
                    legal_move = True
            elif direction == 1:
                x += self.get_move_dist()
                if (not self.get_world().is_outside(self.get_x() + x, self.get_y() + y)
                        and self.is_stronger(self.get_x() + x, self.get_y() + y)):
                    legal_move = True
            elif direction == 2:
                y -= self.get_move_dist()
                if (not self.get_world().is_outside(self.get_x() + x, self.get_y() + y)
                        and self.is_stronger(self.get_x() + x, self.get_y() + y)):
                    legal_move = True
            elif direction == 3:
                x -= self.get_move_dist()
                if (not self.get_world().is_outside(self.get_x() + x, self.get_y() + y)
                        and self.is_stronger(self.get_x() + x, self.get_y() + y)):
                    legal_move = True
            if legal_move is True:
                if self.get_world().is_occupied(self.get_x() + x, self.get_y() + y):
                    self.get_world().get_field(self.get_x() + x, self.get_y() + y).collision(self)
                else:
                    new_x = self.get_x() + x
                    new_y = self.get_y() + y
                    self.new_location(new_x, new_y)
