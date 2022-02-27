from simulator.Organisms.Animal import Animal


class Wolf(Animal):
    def __init__(self, current_world, x_coordinate, y_coordinate):
        super().__init__(current_world, x_coordinate, y_coordinate, 9, 5, True, 'W', 'simulator\\images\\wolf.png')
