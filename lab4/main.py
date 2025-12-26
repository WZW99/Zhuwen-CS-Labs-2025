# === 1. Фабричный метод (порождающий паттерн) ===
class Tour:
    def __init__(self, name, price):
        self.name = name
        self.price = price

    def calculate_cost(self, days):
        return self.price * days

class AdventureTour(Tour):
    def get_type(self):
        return "Приключенческий тур"

class CulturalTour(Tour):
    def get_type(self):
        return "Культурный тур"

class TourFactory:
    @staticmethod
    def create_tour(tour_type, name, price):
        if tour_type == "adventure":
            return AdventureTour(name, price)
        elif tour_type == "cultural":
            return CulturalTour(name, price)
        else:
            raise ValueError(f"Неизвестный тип тура: {tour_type}")


# === 2. Адаптер (структурный паттерн) ===
class PayPalSystem:
    def pay_in_usd(self, amount_usd):
        return f"PayPal: Оплачено ${amount_usd}"

class StripeSystem:
    def charge(self, amount_cents):
        return f"Stripe: Списано {amount_cents} центов"

class PaymentAdapter:
    def __init__(self, system_type):
        self.system_type = system_type
        if system_type == "paypal":
            self.system = PayPalSystem()
        elif system_type == "stripe":
            self.system = StripeSystem()
        else:
            raise ValueError(f"Неизвестная система: {system_type}")

    def pay(self, amount_rub):
        if self.system_type == "paypal":
            amount_usd = amount_rub / 75
            return self.system.pay_in_usd(amount_usd)
        else:  # stripe
            amount_cents = int((amount_rub / 75) * 100)
            return self.system.charge(amount_cents)


# === 3. Стратегия (поведенческий паттерн) ===
class DiscountStrategy:
    def calculate_discount(self, price):
        return 0

class StudentDiscount(DiscountStrategy):
    def calculate_discount(self, price):
        return price * 0.15  # 15% скидка

class GroupDiscount(DiscountStrategy):
    def calculate_discount(self, price):
        return price * 0.10  # 10% скидка

class PriceCalculator:
    def __init__(self, discount_strategy=None):
        self.discount_strategy = discount_strategy or DiscountStrategy()

    def calculate_final_price(self, price):
        discount = self.discount_strategy.calculate_discount(price)
        return price - discount


# === Основная программа ===
def main():
    print("=== Демонстрация паттернов ===")

    # 1. Фабричный метод
    print("\n1. Фабричный метод:")
    tour1 = TourFactory.create_tour("adventure", "Поход в горы", 5000)
    tour2 = TourFactory.create_tour("cultural", "Музейный тур", 3000)
    print(f"{tour1.name}: {tour1.get_type()}")
    print(f"{tour2.name}: {tour2.get_type()}")

    # 2. Стратегия
    print("\n2. Паттерн Стратегия:")
    calculator = PriceCalculator()
    price = 10000

    calculator.discount_strategy = StudentDiscount()
    print(f"Студенческая скидка: {calculator.calculate_final_price(price)} руб.")

    calculator.discount_strategy = GroupDiscount()
    print(f"Групповая скидка: {calculator.calculate_final_price(price)} руб.")

    # 3. Адаптер
    print("\n3. Паттерн Адаптер:")
    adapter1 = PaymentAdapter("paypal")
    adapter2 = PaymentAdapter("stripe")

    print(adapter1.pay(7500))
    print(adapter2.pay(7500))

    print("\n=== Завершение ===")


if __name__ == "__main__":
    main()
