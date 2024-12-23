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
 * @return Произведение четных элементов. Возвращает -1, если нет четных элементов.
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
    printf("Произведение четных элементов: %lld\n", product >= 0 ? product : 0);

    processArray(array, n, newArray, k);

    printf("Массив после процесса:\n");
    printArray(newArray, n);

    free(array);
    free(newArray);

    return 0;
}

void fillArray(int* array, const size_t size, const int useRandom) {
    if (array == NULL || size == 0) {
        printf("Ошибка: некорректный массив или размер.\n");
        return;
    }

    int minRange = 0;
    int maxRange = 0;

    if (useRandom) {
        while (1) {
            minRange = inputInt("Введите минимальное значение для случайных чисел: ");
            maxRange = inputInt("Введите максимальное значение для случайных чисел: ");
            if (minRange <= maxRange) {
                break;
            }
            else {
                printf("Ошибка: минимальное значение не должно превышать максимальное. Попробуйте снова.\n");
            }
        }

        srand((unsigned)time(NULL));
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
    if (array == NULL || size == 0) {
        printf("Ошибка: некорректный массив или размер.\n");
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

long long productOfEven(const int* array, const size_t size) {
    if (array == NULL || size == 0) {
        printf("Ошибка: некорректный массив или размер.\n");
        return -1;
    }

    long long product = 1;
    bool foundEven = false;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            product *= array[i];
            foundEven = true;
        }
    }
    return foundEven ? product : -1;
}

int hasPositiveModulo(const int* array, const size_t size, const int k) {
    if (array == NULL || size == 0) {
        printf("Ошибка: некорректный массив или размер.\n");
        return 0;
    }

    if (k == 0) {
        printf("Ошибка: деление на ноль.\n");
        return 0;
    }

    for (size_t i = 0; i < size; ++i) {
        if (array[i] > 0 && array[i] % k == 2) {
            return 1;
        }
    }
    return 0;
}

void replaceOddIndicesWithSquares(const int* array, int* newArray, const size_t size) {
    if (array == NULL || newArray == NULL || size == 0) {
        printf("Ошибка: некорректные массивы или размер.\n");
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    newArray[1] = 1 * 1; 
    if (size > 2) newArray[3] = 3 * 3; 
    if (size > 4) newArray[5] = 5 * 5; 
    
}

void processArray(const int* array, const size_t size, int* newArray, const int k) {
    if (array == NULL || newArray == NULL || size == 0) {
        printf("Ошибка: некорректные массивы или размер.\n");
        return;
    }

    if (hasPositiveModulo(array, size, k)) {
        printf("Есть положительные числа с остатком 2.\n");
    }
    else {
        printf("Положительных чисел с остатком 2 нет.\n");
    }

    replaceOddIndicesWithSquares(array, newArray, size);

    
    if (size > 0) {
        if (newArray[0] % 2 == 0) {
            printf("Первый четный элемент найден: %d\n", newArray[0]);
        }
        else if (size > 1 && newArray[1] % 2 == 0) {
            printf("Первый четный элемент найден: %d\n", newArray[1]);
        }
        else if (size > 2 && newArray[2] % 2 == 0) {
            printf("Первый четный элемент найден: %d\n", newArray[2]);
        }
    }
}

int inputInt(const char* prompt) {
    int value = 0;
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
    size_t value = 0;
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
    if (array == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    return array;
}
