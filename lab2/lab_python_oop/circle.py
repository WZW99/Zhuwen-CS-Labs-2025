from .figure import Figure
from .color import FigureColor
import math

class Circle(Figure):
    def __init__(self, radius, color):
        self.radius = radius
        self.color = FigureColor()
        self.color.color = color
        self._name = "Круг"

    def area(self):
        return math.pi * self.radius ** 2

    def __repr__(self):
        return "{} {} цвета радиусом {} площадью {:.2f}".format(
            self._name,
            self.color.color,
            self.radius,
            self.area()
        )
