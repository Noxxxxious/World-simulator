from simulator.Organisms.Animal import Animal


class Sheep(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 4, 4, True, 'S', 'simulator\\images\\sheep.png')