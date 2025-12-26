# rk1_refactored.py
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

class DataService:
    """Сервис для работы с данными"""

    @staticmethod
    def create_test_data():
        """Создание тестовых данных"""
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

        return suppliers, details, detail_suppliers

    @staticmethod
    def create_one_to_many(suppliers, details):
        """Создание связи один-ко-многим"""
        return [(d.name, d.cost, s.name)
                for s in suppliers
                for d in details
                if d.supplier_id == s.id]

    @staticmethod
    def create_many_to_many(suppliers, details, detail_suppliers):
        """Создание связи многие-ко-многим"""
        many_to_many_temp = [(s.name, ds.supplier_id, ds.detail_id)
                           for s in suppliers
                           for ds in detail_suppliers
                           if s.id == ds.supplier_id]

        return [(d.name, d.cost, supplier_name)
                for supplier_name, supplier_id, detail_id in many_to_many_temp
                for d in details if d.id == detail_id]

class QueryService:
    """Сервис для выполнения запросов"""

    @staticmethod
    def query1(one_to_many):
        """Запрос 1: Детали с названием на 'ов'"""
        return list(filter(lambda i: i[0].endswith('ов'), one_to_many))

    @staticmethod
    def query2(one_to_many, suppliers):
        """Запрос 2: Средняя стоимость деталей по поставщикам"""
        res_unsorted = []
        for s in suppliers:
            s_details = list(filter(lambda i: i[2] == s.name, one_to_many))
            if len(s_details) > 0:
                s_costs = [cost for _, cost, _ in s_details]
                avg_cost = round(sum(s_costs) / len(s_costs), 2)
                res_unsorted.append((s.name, avg_cost))
        return sorted(res_unsorted, key=itemgetter(1))

    @staticmethod
    def query3(many_to_many, suppliers):
        """Запрос 3: Поставщики на 'А' и их детали"""
        res = {}
        for s in suppliers:
            if s.name.startswith('А'):
                s_details = list(filter(lambda i: i[2] == s.name, many_to_many))
                s_detail_names = [name for name, _, _ in s_details]
                if s_detail_names:  # Добавляем только если есть детали
                    res[s.name] = s_detail_names
        return res

def main():
    """Основная функция"""
    data_service = DataService()
    query_service = QueryService()

    # Получение данных
    suppliers, details, detail_suppliers = data_service.create_test_data()
    one_to_many = data_service.create_one_to_many(suppliers, details)
    many_to_many = data_service.create_many_to_many(suppliers, details, detail_suppliers)

    # Выполнение запросов
    print('Задание Д1:')
    result1 = query_service.query1(one_to_many)
    print(result1)

    print('\nЗадание Д2:')
    result2 = query_service.query2(one_to_many, suppliers)
    print(result2)

    print('\nЗадание Д3:')
    result3 = query_service.query3(many_to_many, suppliers)
    print(result3)

    return result1, result2, result3

if __name__ == '__main__':
    main()
