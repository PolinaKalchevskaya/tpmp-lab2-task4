#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"

void create_test_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create test file\n");
        return;
    }

    fprintf(file, "Марка;Номер;Пункт назначения;Грузоподъемность;Стоимость ед.;Общая стоимость\n");
    fprintf(file, "Volvo;AB1234;Минск;1.5;100;1500\n");
    fprintf(file, "MAN;CD5678;Гродно;3.2;120;3840\n");
    fprintf(file, "Scania;EF9012;Брест;2.8;110;3080\n");
    fprintf(file, "Mercedes;GH3456;Витебск;1.8;130;2340\n");
    fprintf(file, "Renault;IJ7890;Гомель;4.0;90;3600\n");
    fprintf(file, "Iveco;KL1234;Могилев;2.2;95;2090\n");
    fprintf(file, "DAF;MN5678;Минск;3.5;115;4025\n");
    fprintf(file, "Volvo;OP9012;Брест;2.5;105;2625\n");

    fclose(file);
    printf("Test file '%s' created successfully.\n", filename);
}

Car* read_cars_from_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    // Пропускаем заголовок
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    // Подсчитываем количество записей
    *count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strlen(buffer) > 1) (*count)++;
    }

    // Возвращаемся в начало файла
    rewind(file);
    fgets(buffer, sizeof(buffer), file); // пропускаем заголовок

    // Выделяем память
    Car* cars = (Car*)malloc(*count * sizeof(Car));
    if (cars == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Читаем данные
    for (int i = 0; i < *count; i++) {
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%[^;];%[^;];%[^;];%f;%f;%f",
               cars[i].brand, cars[i].number, cars[i].destination,
               &cars[i].capacity, &cars[i].unit_cost, &cars[i].total_cost);
    }

    fclose(file);
    return cars;
}

void write_cars_to_file(const char* filename, Car* cars, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create output file %s\n", filename);
        return;
    }

    fprintf(file, "Марка;Номер;Пункт назначения;Грузоподъемность;Стоимость ед.;Общая стоимость\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%s;%.1f;%.0f;%.0f\n",
                cars[i].brand, cars[i].number, cars[i].destination,
                cars[i].capacity, cars[i].unit_cost, cars[i].total_cost);
    }

    fclose(file);
    printf("Results written to '%s'\n", filename);
}

void print_cars(Car* cars, int count) {
    printf("\n%-10s %-10s %-15s %-5s %-10s %-10s\n",
           "Марка", "Номер", "Назначение", "Тонн", "Стоим/ед", "Всего");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-10s %-15s %-5.1f %-10.0f %-10.0f\n",
               cars[i].brand, cars[i].number, cars[i].destination,
               cars[i].capacity, cars[i].unit_cost, cars[i].total_cost);
    }
}

Car* filter_cars_by_capacity(Car* cars, int count, int* new_count, float min_capacity) {
    // Сначала подсчитываем, сколько подходит
    *new_count = 0;
    for (int i = 0; i < count; i++) {
        if (cars[i].capacity > min_capacity) {
            (*new_count)++;
        }
    }

    if (*new_count == 0) return NULL;

    // Выделяем память
    Car* filtered = (Car*)malloc(*new_count * sizeof(Car));
    if (filtered == NULL) return NULL;

    // Заполняем
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (cars[i].capacity > min_capacity) {
            filtered[j++] = cars[i];
        }
    }

    return filtered;
}

void free_cars(Car* cars) {
    free(cars);
}
