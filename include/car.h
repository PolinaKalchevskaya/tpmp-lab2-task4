#ifndef CAR_H
#define CAR_H

typedef struct {
    char brand[50];          // марка автомобиля
    char number[20];          // номер автомобиля
    char destination[100];    // пункт назначения
    float capacity;           // грузоподъемность (тонны)
    float unit_cost;          // стоимость единицы груза
    float total_cost;         // общая стоимость груза
} Car;

// Функции для работы с файлами
Car* read_cars_from_file(const char* filename, int* count);
void write_cars_to_file(const char* filename, Car* cars, int count);
void print_cars(Car* cars, int count);

// Функция для задания: автомобили с грузоподъемностью > 2 тонн
Car* filter_cars_by_capacity(Car* cars, int count, int* new_count, float min_capacity);

// Создание тестового файла
void create_test_file(const char* filename);

// Освобождение памяти
void free_cars(Car* cars);

#endif
