
import unittest
from unittest.mock import Mock, patch

# Импортируем классы из основного файла
import main

class TestTourFactory(unittest.TestCase):
    """Тесты фабричного метода"""

    def test_create_adventure_tour(self):
        """Создание приключенческого тура"""
        tour = main.TourFactory.create_tour("adventure", "Рафтинг", 7000)
        self.assertIsInstance(tour, main.AdventureTour)
        self.assertEqual(tour.name, "Рафтинг")
        self.assertEqual(tour.get_type(), "Приключенческий тур")

    def test_create_cultural_tour(self):
        """Создание культурного тура"""
        tour = main.TourFactory.create_tour("cultural", "Экскурсия", 4000)
        self.assertIsInstance(tour, main.CulturalTour)
        self.assertEqual(tour.get_type(), "Культурный тур")

    def test_invalid_tour_type(self):
        """Тест с неверным типом тура"""
        with self.assertRaises(ValueError):
            main.TourFactory.create_tour("spa", "SPA-тур", 10000)


class TestPaymentAdapter(unittest.TestCase):
    """Тесты адаптера"""

    def test_paypal_adapter(self):
        """Тест PayPal адаптера"""
        adapter = main.PaymentAdapter("paypal")
        result = adapter.pay(7500)
        self.assertIn("PayPal", result)
        self.assertIn("Оплачено", result)

    def test_stripe_adapter(self):
        """Тест Stripe адаптера"""
        adapter = main.PaymentAdapter("stripe")
        result = adapter.pay(7500)
        self.assertIn("Stripe", result)
        self.assertIn("Списано", result)


class TestDiscountStrategy(unittest.TestCase):
    """Тесты стратегии скидок"""

    def test_student_discount(self):
        """Тест студенческой скидки"""
        discount = main.StudentDiscount()
        self.assertEqual(discount.calculate_discount(10000), 1500)

    def test_group_discount(self):
        """Тест групповой скидки"""
        discount = main.GroupDiscount()
        self.assertEqual(discount.calculate_discount(10000), 1000)

    def test_no_discount(self):
        """Тест отсутствия скидки"""
        discount = main.DiscountStrategy()
        self.assertEqual(discount.calculate_discount(10000), 0)


class TestWithMocks(unittest.TestCase):
    """Тесты с использованием Mock объектов"""

    @patch('main.PayPalSystem')
    def test_paypal_mock(self, mock_paypal):
        """Тест с моком PayPal"""
        mock_instance = Mock()
        mock_instance.pay_in_usd.return_value = "Mock PayPal Payment"
        mock_paypal.return_value = mock_instance

        adapter = main.PaymentAdapter("paypal")
        result = adapter.pay(10000)

        self.assertEqual(result, "Mock PayPal Payment")
        mock_instance.pay_in_usd.assert_called_once()

    def test_tour_mock(self):
        """Тест с моком тура"""
        mock_tour = Mock()
        mock_tour.name = "Mock Tour"
        mock_tour.price = 5000
        mock_tour.calculate_cost.return_value = 15000

        result = mock_tour.calculate_cost(3)
        self.assertEqual(result, 15000)
        mock_tour.calculate_cost.assert_called_once_with(3)


if __name__ == '__main__':
    unittest.main(verbosity=2)
