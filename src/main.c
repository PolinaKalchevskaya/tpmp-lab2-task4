#include <stdio.h>
#include <stdlib.h>
#include "../include/car.h"

int main() {
    const char* input_file = "data/cars.txt";
    const char* output_file = "data/filtered_cars.txt";
    Car* cars = NULL;
    Car* filtered = NULL;
    int count = 0;
    int filtered_count = 0;

    printf("=== CAR TRANSPORT PROCESSING ===\n");
    printf("Variant 35: Filter cars with capacity > 2 tons\n\n");

    // Создаем тестовый файл
    create_test_file(input_file);

    // Читаем данные из файла
    cars = read_cars_from_file(input_file, &count);
    if (cars == NULL) {
        printf("Error: Failed to read cars from file.\n");
        return 1;
    }

    printf("\n--- All cars ---\n");
    print_cars(cars, count);

    // Фильтруем по грузоподъемности (> 2 тонн)
    filtered = filter_cars_by_capacity(cars, count, &filtered_count, 2.0);

    printf("\n--- Cars with capacity > 2 tons ---\n");
    if (filtered_count > 0) {
        print_cars(filtered, filtered_count);
        write_cars_to_file(output_file, filtered, filtered_count);
    } else {
        printf("No cars found with capacity > 2 tons.\n");
    }

    // Освобождаем память
    free_cars(cars);
    if (filtered != NULL) free_cars(filtered);

    printf("\nProgram completed successfully.\n");
    return 0;
}
