from .figure import Figure
from .color import FigureColor
import math

class Rectangle(Figure):
    def __init__(self, width, height, color):
        self.width = width
        self.height = height
        self.color = FigureColor()
        self.color.color = color
        self._name = "Прямоугольник"

    def area(self):
        return self.width * self.height

    def __repr__(self):
        return "{} {} цвета шириной {} и высотой {} площадью {:.2f}".format(
            self._name,
            self.color.color,
            self.width,
            self.height,
            self.area()
        )
