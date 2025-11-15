import sys
import math

def get_coefficient(input_prompt):
    """Функция для безопасного ввода коэффициента с проверкой на корректность."""
    while True:
        try:
            value = float(input(input_prompt))
            return value
        except ValueError:
            print("Ошибка: введите действительное число.")

def get_coefficients_from_keyboard():
    """Функция для ввода всех коэффициентов с клавиатуры."""
    print("Введите коэффициенты A, B, C для уравнения A*x^4 + B*x^2 + C = 0:")
    a = get_coefficient("A = ")
    b = get_coefficient("B = ")
    c = get_coefficient("C = ")
    return a, b, c

def parse_command_line_arguments():
    """Функция для парсинга параметров командной строки."""
    coefficients = []
    if len(sys.argv) == 4:
        for arg in sys.argv[1:]:
            try:
                coefficients.append(float(arg))
            except ValueError:
                print(f"Неверный параметр: {arg}. Будет запрошен ввод с клавиатуры.")
                return None
        return coefficients
    return None

def validate_coefficient_a(a):
    """Функция для проверки коэффициента A."""
    if a == 0:
        print("Ошибка: коэффициент A не может быть нулем.")
        return False
    return True

def calculate_discriminant(a, b, c):
    """Функция для вычисления дискриминанта."""
    return b**2 - 4*a*c

def solve_quadratic(a, b, c):
    """Функция для решения квадратного уравнения a*y^2 + b*y + c = 0."""
    discriminant = calculate_discriminant(a, b, c)

    if discriminant < 0:
        return []  # Нет действительных корней
    elif discriminant == 0:
        y = -b / (2 * a)
        return [y]
    else:
        y1 = (-b + math.sqrt(discriminant)) / (2 * a)
        y2 = (-b - math.sqrt(discriminant)) / (2 * a)
        return [y1, y2]

def get_real_roots_from_quadratic_solutions(quadratic_roots):
    """Функция для получения действительных корней из решений квадратного уравнения."""
    roots = []
    for y in quadratic_roots:
        if y > 0:
            root1 = math.sqrt(y)
            root2 = -math.sqrt(y)
            roots.extend([root1, root2])
        elif y == 0:
            roots.append(0.0)
    return roots

def solve_biquadratic(a, b, c):
    """Функция для решения биквадратного уравнения a*x^4 + b*x^2 + c = 0."""
    # Решаем квадратное уравнение относительно y = x^2
    quadratic_roots = solve_quadratic(a, b, c)

    # Получаем действительные корни биквадратного уравнения
    biquadratic_roots = get_real_roots_from_quadratic_solutions(quadratic_roots)

    return biquadratic_roots

def format_roots(roots):
    """Функция для форматирования вывода корней."""
    if not roots:
        return "Действительных корней нет."

    # Убираем дубликаты корней и сортируем
    unique_roots = sorted(set(roots))
    roots_str = ", ".join([f"{root:.6f}".rstrip('0').rstrip('.') for root in unique_roots])
    return f"Действительные корни: {roots_str}"

def main():
    """Основная функция программы."""
    # Пытаемся получить коэффициенты из командной строки
    coefficients = parse_command_line_arguments()

    if coefficients:
        a, b, c = coefficients
        print(f"Использованы коэффициенты из командной строки: A={a}, B={b}, C={c}")
    else:
        # Если не получилось, вводим с клавиатуры
        a, b, c = get_coefficients_from_keyboard()

    # Проверяем коэффициент A
    if not validate_coefficient_a(a):
        return

    # Решаем биквадратное уравнение
    roots = solve_biquadratic(a, b, c)

    # Форматируем и выводим результат
    result = format_roots(roots)
    print(result)

if __name__ == "__main__":
    main()
