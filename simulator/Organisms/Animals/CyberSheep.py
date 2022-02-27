from simulator.Organisms.Animal import Animal


class CyberSheep(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 11, 4, True, 'C',
                         'simulator\\images\\cyber_sheep.png')

    def find_hogweed(self):
        closest_hogweed = None
        shortest_distance = self.get_world().get_height() + self.get_world().get_width()
        for org in self.get_world().get_list():
            if org.get_token() == 'H':
                distance = abs(self.get_x() - org.get_x()) + abs(self.get_y() - org.get_y())
                if distance < shortest_distance:
                    closest_hogweed = org
                    shortest_distance = distance
        return closest_hogweed

    def move(self):
        closest_hogweed = self.find_hogweed()
        new_x = self.get_x()
        new_y = self.get_y()
        if closest_hogweed is not None:
            if self.get_x() != closest_hogweed.get_x():
                if self.get_x() < closest_hogweed.get_x():
                    new_x += 1
                else:
                    new_x -= 1
            elif self.get_y() != closest_hogweed.get_y():
                if self.get_y() < closest_hogweed.get_y():
                    new_y += 1
                else:
                    new_y -= 1
            if self.get_world().is_occupied(new_x, new_y):
                self.get_world().get_field(new_x, new_y).collision(self)
            else:
                self.new_location(new_x, new_y)
        else:
            super().move()
