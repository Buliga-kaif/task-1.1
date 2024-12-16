
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
/*
 * @brief Заполняет массив числами, случайными или пользовательскими.
 * @param array Указатель на первый элемент массива.
 * @param size Размер массива.
 * @param useRandom Если равно 1, заполняет случайными числами; если 0, запрашивает ввод от пользователя.
 */
void fillArray(int* array, const size_t size, const int useRandom);
/*
 * @brief Выводит массив на экран.
 * @param array Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void printArray(const int* array, const size_t size);
/*
 * @brief Вычисляет произведение четных элементов массива.
 * @param array Указатель на первый элемент массива.
 * @param size Размер массива.
 * @return Произведение четных элементов. Возвращает 0, если нет четных элементов.
 */
long long productOfEven(const int* array, const size_t size);
/*
 * @brief Заменяет элементы на нечетных индексах квадратами их индексов.
 * @param array Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void replaceOddIndicesWithSquares(const int* array, int* newArray, const size_t size);
/*
 * @brief Проверяет, имеются ли положительные элементы с остатком 2 при делении на k.
 * @param array Указатель на первый элемент массива.
 * @param size Размер массива.
 * @param k Значение делителя.
 * @return 1, если найдены такие элементы, иначе 0.
 */
int hasPositiveModulo(const int* array, const size_t size, const int k);
/*
 * @brief Процедура обработки массива: проверяет положительные элементы и выполняет замену по индексам.
 * @param array Исходный массив.
 * @param size Размер массива.
 * @param newArray Модифицированный массив.
 * @param k Делитель для проверки с остатком 2.
 */
void processArray(const int* array, const size_t size, int* newArray, const int k);
/*
 * @brief Запрашивает у пользователя ввод целого числа.
 * @param prompt Строка запроса для вывода пользователю.
 * @return Введенное пользователем целое число.
 */
int inputInt(const char* prompt);
/*
 * @brief Запрашивает у пользователя ввод положительного целого числа (size_t).
 * @param prompt Строка запроса для вывода пользователю.
 * @return Введенное пользователем положительное целое число типа size_t.
 */
size_t inputSizeT(const char* prompt);
/*
 * @brief Выделяет память для массива целых чисел и проверяет успешность выделения.
 * @param size Количество элементов, для которых выделяется память.
 * @return Указатель на выделенную область памяти, если выделение успешно.
 *         Программа завершает выполнение, если выделение памяти не удалось.
 */
int* allocateAndCheckMemory(size_t size);
/*
 * @brief Главная функция программы, выполняющая несколько операций над массивом целых чисел.
 * Функция main выполняет следующие шаги:
 * 1. Инициализирует локализацию для вывода строк.
 * 2. Запрашивает у пользователя размер массива n и значение k.
 * 3. Выделяет динамическую память для массива целых чисел.
 * 4. Запрашивает у пользователя заполнить массив случайными числами или вручную.
 * 5. Заполняет массив и выводит его на экран.
 * 6. Вычисляет и выводит произведение чётных элементов массива.
 * 7. Заменяет элементы на нечетных индексах их квадратами.
 * 8. Проверяет наличие положительных элементов, дающих остаток 2 при делении на k, и выводит результат.
 * 9. Освобождает выделенную память и завершает программу.
 * @return 0 при успешном завершении, 1 при ошибке.
 */
int main(void) {
    setlocale(LC_ALL, "");

    size_t n = inputSizeT("Введите размер массива: ");
    int k = inputInt("Введите число k: ");
    int* array = allocateAndCheckMemory(n);
    int* newArray = allocateAndCheckMemory(n);

    int useRandom = inputInt("Заполнить массив случайными числами? (1 - да, 0 - нет): ");
    fillArray(array, n, useRandom);

    printf("Массив:\n");
    printArray(array, n);

    long long product = productOfEven(array, n);
    printf("Произведение четных элементов: %lld\n", product);

    processArray(array, n, newArray, k);

    printf("Массив после процесса:\n");
    printArray(newArray, n);

    free(array);
    free(newArray);

    return 0;
}

void fillArray(int* array, const size_t size, const int useRandom) {
    int minRange, maxRange;

    if (useRandom) {
        do {
            minRange = inputInt("Введите минимальное значение для случайных чисел: ");
            maxRange = inputInt("Введите максимальное значение для случайных чисел: ");
            if (minRange > maxRange) {
                printf("Ошибка: минимальное значение не должно превышать максимальное. Попробуйте снова.\n");
            }
        } while (minRange > maxRange);

        srand(time(NULL));
        for (size_t i = 0; i < size; ++i) {
            array[i] = minRange + rand() % (maxRange - minRange + 1);
        }
    }
    else {
        for (size_t i = 0; i < size; ++i) {
            array[i] = inputInt("Введите элемент: ");
        }
    }
}

void printArray(const int* array, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

long long productOfEven(const int* array, const size_t size) {
    long long product = 1;
    bool foundEven = false;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            product *= array[i];
            foundEven = true;
        }
    }
    return foundEven ? product : 0;
}

int hasPositiveModulo(const int* array, const size_t size, const int k) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > 0 && array[i] % k == 2) {
            return 1;
        }
    }
    return 0;
}

void replaceOddIndicesWithSquares(const int* array, int* newArray, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    for (size_t i = 1; i < size; i += 2) {
        newArray[i] = i * i;
    }
}

void processArray(const int* array, const size_t size, int* newArray, const int k) {
    if (hasPositiveModulo(array, size, k)) {
        printf("Есть положительные числа с остатком 2.\n");
    }
    else {
        printf("Положительных чисел с остатком 2 нет.\n");
    }

    replaceOddIndicesWithSquares(array, newArray, size);
}

int inputInt(const char* prompt) {
    int value;
    while (true) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            while (getchar() != '\n');
            break;
        }
        else {
            printf("Ошибка ввода. Повторите попытку.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

size_t inputSizeT(const char* prompt) {
    size_t value;
    while (true) {
        printf("%s", prompt);
        if (scanf("%zu", &value) == 1 && value > 0) {
            while (getchar() != '\n');
            break;
        }
        else {
                printf("Ошибка ввода. Повторите попытку.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

int* allocateAndCheckMemory(size_t size) {
    int* array = (int*)malloc(size * sizeof(int));
    if (!array) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    return array;
}

