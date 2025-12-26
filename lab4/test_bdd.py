

import main

def test_booking_scenario():
    """Простой тест сценария бронирования"""
    print("=== Тестирование сценария бронирования ===")

    # Given (Дано) - предварительные условия
    tour = main.TourFactory.create_tour("adventure", "Скалолазание", 6000)
    calculator = main.PriceCalculator(main.StudentDiscount())

    # When (Когда) - действие
    final_price = calculator.calculate_final_price(tour.price * 3)

    # Then (Тогда) - проверка результата
    assert tour.get_type() == "Приключенческий тур"
    assert final_price == (6000 * 3) * 0.85  # 15% скидка
    print("✓ Сценарий успешно пройден")

    return True


def test_payment_scenario():
    """Простой тест сценария оплаты"""
    print("\n=== Тестирование сценария оплаты ===")

    # Given
    adapter = main.PaymentAdapter("stripe")

    # When
    result = adapter.pay(5000)

    # Then
    assert "Stripe" in result
    print("✓ Оплата через Stripe успешно обработана")

    return True


if __name__ == "__main__":
    # Запуск BDD тестов
    test_booking_scenario()
    test_payment_scenario()
