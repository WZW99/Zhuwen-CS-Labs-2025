from operator import itemgetter

class Detail:
    """Деталь"""
    def __init__(self, id, name, cost, supplier_id):
        self.id = id
        self.name = name
        self.cost = cost
        self.supplier_id = supplier_id

class Supplier:
    """Поставщик"""
    def __init__(self, id, name):
        self.id = id
        self.name = name

class DetailSupplier:
    """Связь многие-ко-многим"""
    def __init__(self, supplier_id, detail_id):
        self.supplier_id = supplier_id
        self.detail_id = detail_id

# Тестовые данные
suppliers = [
    Supplier(1, 'Авангард'),
    Supplier(2, 'Бетакон'),
    Supplier(3, 'Агропром'),
    Supplier(4, 'Металлинвест'),
]

details = [
    Detail(1, 'Болтов', 1500, 1),
    Detail(2, 'Винтов', 2000, 2),
    Detail(3, 'Шурупов', 1200, 1),
    Detail(4, 'Гайков', 1800, 3),
    Detail(5, 'Резьбов', 2200, 4),
]

detail_suppliers = [
    DetailSupplier(1, 1),
    DetailSupplier(1, 3),
    DetailSupplier(2, 2),
    DetailSupplier(3, 4),
    DetailSupplier(4, 5),
]

def main():
    """Основная функция"""

    # Соединение данных один-ко-многим
    one_to_many = [(d.name, d.cost, s.name)
        for s in suppliers
        for d in details
        if d.supplier_id == s.id]

    # Соединение данных многие-ко-многим
    many_to_many_temp = [(s.name, ds.supplier_id, ds.detail_id)
        for s in suppliers
        for ds in detail_suppliers
        if s.id == ds.supplier_id]

    many_to_many = [(d.name, d.cost, supplier_name)
        for supplier_name, supplier_id, detail_id in many_to_many_temp
        for d in details if d.id == detail_id]

    print('Задание Д1:')
    res_1 = list(filter(lambda i: i[0].endswith('ов'), one_to_many))
    print(res_1)

    print('\nЗадание Д2:')
    res_2_unsorted = []
    for s in suppliers:
        s_details = list(filter(lambda i: i[2] == s.name, one_to_many))
        if len(s_details) > 0:
            s_costs = [cost for _, cost, _ in s_details]
            avg_cost = round(sum(s_costs) / len(s_costs), 2)
            res_2_unsorted.append((s.name, avg_cost))
    res_2 = sorted(res_2_unsorted, key=itemgetter(1))
    print(res_2)

    print('\nЗадание Д3:')
    res_3 = {}
    for s in suppliers:
        if s.name.startswith('А'):
            s_details = list(filter(lambda i: i[2] == s.name, many_to_many))
            s_detail_names = [name for name, _, _ in s_details]
            res_3[s.name] = s_detail_names
    print(res_3)

if __name__ == '__main__':
    main()
