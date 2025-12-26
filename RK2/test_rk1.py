# test_rk1.py
import unittest
from rk1_refactored import DataService, QueryService, Detail, Supplier, DetailSupplier

class TestRK1(unittest.TestCase):
    """Тесты для рубежного контроля №1"""

    def setUp(self):
        """Подготовка тестовых данных"""
        self.data_service = DataService()
        self.query_service = QueryService()
        self.suppliers, self.details, self.detail_suppliers = self.data_service.create_test_data()
        self.one_to_many = self.data_service.create_one_to_many(self.suppliers, self.details)
        self.many_to_many = self.data_service.create_many_to_many(
            self.suppliers, self.details, self.detail_suppliers
        )

    def test_query1_details_ending_with_ov(self):
        """Тест 1: Проверка запроса деталей с названием на 'ов'"""
        # Act
        result = self.query_service.query1(self.one_to_many)

        # Assert
        # Проверяем, что все найденные детали заканчиваются на 'ов'
        for detail in result:
            self.assertTrue(detail[0].endswith('ов'),
                        f"Деталь '{detail[0]}' не заканчивается на 'ов'")

        # Проверяем количество найденных деталей - должно быть 5, а не 4
        self.assertEqual(len(result), 5,
                        f"Ожидается 5 деталей, получено {len(result)}")

        # Проверяем конкретные детали
        detail_names = [detail[0] for detail in result]
        expected_names = ['Болтов', 'Винтов', 'Шурупов', 'Гайков', 'Резьбов']
        for name in expected_names:
            self.assertIn(name, detail_names)
    def test_query2_average_cost_per_supplier(self):
        """Тест 2: Проверка расчета средней стоимости деталей по поставщикам"""
        # Act
        result = self.query_service.query2(self.one_to_many, self.suppliers)

        # Assert
        # Проверяем количество поставщиков
        self.assertEqual(len(result), 4)

        # Проверяем правильность расчетов
        expected_results = [
            ('Авангард', 1350.0),
            ('Бетакон', 2000.0),
            ('Агропром', 1800.0),
            ('Металлинвест', 2200.0)
        ]

        for expected in expected_results:
            found = False
            for actual in result:
                if actual[0] == expected[0]:
                    self.assertAlmostEqual(actual[1], expected[1], places=2,
                                         msg=f"Неверная средняя стоимость для {expected[0]}")
                    found = True
                    break
            self.assertTrue(found, f"Поставщик {expected[0]} не найден в результатах")

        # Проверяем сортировку по возрастанию средней стоимости
        for i in range(len(result) - 1):
            self.assertLessEqual(result[i][1], result[i+1][1],
                               "Результаты не отсортированы по возрастанию")

    def test_query3_suppliers_starting_with_a(self):
        """Тест 3: Проверка запроса поставщиков на 'А' и их деталей"""
        # Act
        result = self.query_service.query3(self.many_to_many, self.suppliers)

        # Assert
        # Проверяем количество поставщиков на 'А'
        self.assertEqual(len(result), 2)

        # Проверяем конкретных поставщиков
        self.assertIn('Авангард', result)
        self.assertIn('Агропром', result)

        # Проверяем детали поставщика 'Авангард'
        self.assertEqual(len(result['Авангард']), 2)
        self.assertIn('Болтов', result['Авангард'])
        self.assertIn('Шурупов', result['Авангард'])

        # Проверяем детали поставщика 'Агропром'
        self.assertEqual(len(result['Агропром']), 1)
        self.assertIn('Гайков', result['Агропром'])

        # Проверяем, что нет других поставщиков
        for supplier_name in result.keys():
            self.assertTrue(supplier_name.startswith('А'),
                          f"Поставщик '{supplier_name}' не начинается с 'А'")

class TestDataService(unittest.TestCase):
    """Тесты для сервиса данных"""

    def test_create_one_to_many(self):
        """Тест создания связи один-ко-многим"""
        # Arrange
        suppliers = [Supplier(1, 'TestSupplier')]
        details = [
            Detail(1, 'TestDetail1', 100, 1),
            Detail(2, 'TestDetail2', 200, 1),
            Detail(3, 'TestDetail3', 300, 2),  # Другая связь
        ]

        # Act
        result = DataService.create_one_to_many(suppliers, details)

        # Assert
        self.assertEqual(len(result), 2)
        self.assertEqual(result[0][0], 'TestDetail1')
        self.assertEqual(result[0][1], 100)
        self.assertEqual(result[0][2], 'TestSupplier')

if __name__ == '__main__':
    # Запуск тестов
    unittest.main(verbosity=2)
