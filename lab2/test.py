import unittest
from lab_python_oop.rectangle import Rectangle
from lab_python_oop.circle import Circle
from lab_python_oop.square import Square

class TestFigures(unittest.TestCase):
    def test_rectangle_area(self):
        rect = Rectangle(5, 5, "синего")
        self.assertEqual(rect.area(), 25)

    def test_circle_area(self):
        circle = Circle(5, "зеленого")
        self.assertAlmostEqual(circle.area(), 78.54, places=2)

    def test_square_area(self):
        square = Square(5, "красного")
        self.assertEqual(square.area(), 25)

if __name__ == '__main__':
    unittest.main()
