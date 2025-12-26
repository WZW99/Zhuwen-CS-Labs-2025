# run_tests.py
import unittest
import sys

if __name__ == '__main__':
    # Загрузка тестов из модуля test_rk1
    test_loader = unittest.TestLoader()
    test_suite = test_loader.discover('.', pattern='test_*.py')

    # Запуск тестов
    test_runner = unittest.TextTestRunner(verbosity=2)
    result = test_runner.run(test_suite)

    # Возврат кода выхода в зависимости от результата тестов
    sys.exit(0 if result.wasSuccessful() else 1)
