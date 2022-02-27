from abc import ABC, abstractmethod
import pygame


class Organism(ABC):
    def __init__(self, current_world, x_coordinate, y_coordinate, strength, initiative, is_alive, token, image):
        self.__strength = strength
        self.__initiative = initiative
        self.__is_alive = is_alive
        self.__move_distance = 1
        self.__x_coordinate = x_coordinate
        self.__y_coordinate = y_coordinate
        self.__current_world = current_world
        self.__token = token
        self.__image = pygame.image.load(image)
        self.__age = 0
        self.__current_world.add_to_world(self)
        self.__current_world.add_to_list(self)

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self, predator):
        pass

    def get_x(self):
        return self.__x_coordinate

    def get_y(self):
        return self.__y_coordinate

    def get_age(self):
        return self.__age

    def get_strength(self):
        return self.__strength

    def get_init(self):
        return self.__initiative

    def get_move_dist(self):
        return self.__move_distance

    def get_alive(self):
        return self.__is_alive

    def get_token(self):
        return self.__token

    def get_world(self):
        return self.__current_world

    def get_image(self):
        return self.__image

    def set_position(self, x_coordinate, y_coordinate):
        self.__x_coordinate = x_coordinate
        self.__y_coordinate = y_coordinate

    def set_age(self, age):
        self.__age = age

    def set_strength(self, strength):
        self.__strength = strength

    def set_image(self, image):
        self.__image = pygame.image.load(image)

    def set_move_dist(self, distance):
        self.__move_distance = distance

    def new_location(self, x_coordinate, y_coordinate):
        self.__current_world.set_field(x_coordinate, y_coordinate, self)
        self.__current_world.set_field(self.get_x(), self.get_y(), None)
        self.set_position(x_coordinate, y_coordinate)

    def kill(self):
        self.__is_alive = False

    def is_stronger(self, x_coordinate, y_coordinate):
        if self.get_world().get_field(x_coordinate, y_coordinate) is not None:
            if self.get_strength() >= self.__current_world.get_field(x_coordinate, y_coordinate).get_strength():
                return True
            else:
                return False
        return True
