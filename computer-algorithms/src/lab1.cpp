#include "stdio.h"

#define size 6 // задаем константу размерности
// объявляем массив с инициализацией значениями
// длину массива указывать не обязательно, если есть инициализация
// компилятор определяет длину массива из кол-ва заданных значений
int arr[] = {3, 2, 4, 0, 2, 3};

// Умножение итеративное, функция запускает один раз и считает результат умножения, пока не дойдет конца массива
// Параметров нет.
int simple_multiple()
{
	int result;
	for (int i = 0; i < size; ++i)
	{
		// Это не первая итерации?
		if (i > 0)
		{
			// Значение из массива не нулевое?
			if (arr[i] > 0) {
				// Умножаем значение прошлоа на значение из массива
				result *= arr[i];
			}
		} else {
			// Просто сохраняем значение из массива
			result = arr[i];
		}
	}
	return result;
}

// Умножение рекурсивное, функция запускает сама себя, пока не дойдет конца массива
// Первый параметр: глубина текущей позиции т.е. позицию в массиве
// Второй параметр: результат прошлого умножения
int recursive_multiple(int depth, int source)
{
	// Ностигнут ли еще конец массива?
	if (depth < size)
	{
		// Пытаемся умножить
		int multiple_result; // Временная переменная
		// Проверяем значение. Положительное в текущей позиции массива?
		if (arr[depth] > 0)
		{
			// Есть что умножать
			// Проверяем прошлое значение больше нуля?
			if (source == 0)
			{
				source = 1; // измененяем 0 на 1 т.к. в умножении на ноль нет смысла
			}
			// Функция запускает сама себя, параметром педаем увеличенную глубину на 1
			// умножает значение из массива на значение переданное параметром
			// depth + 1, можно заменит на ++depth
			return recursive_multiple(depth + 1, arr[depth] * source);
		} else {
			// Функция запускает сама себя, параметром педаем увеличенную глубину на 1
			// значение передается без изменения
			return recursive_multiple(depth + 1, source);
		}
	} else {
		return source; // Возвращаем переданное значение аргументом без изменений
	}
}

int main()
{
	// Считаем и выводим результа. Умножение итерацией по массиву
	printf("by iteration=%d\n", simple_multiple());

	// Считаем и выводим результат. Умножение рекурсивным методом
	// Функции нужно задать начальные параметры.
	// Первый параметр: глубина, начиная с нуля (первая позиция в массиве)
	// Второй параметр: инициализация значение(которое будет умножено и передано дальше для умножения)
	printf("by recursion=%d\n", recursive_multiple(0, 0));
	return 0;
}

// RESULT
// vlad@localhost:~/projects/fun/labsFromUniversity$ make
// cd computer-algorithms; make;
// make[1]: Entering directory '/home/vlad/projects/fun/labsFromUniversity/computer-algorithms'
// gcc src/lab1.cpp -o lab1
// make[1]: Leaving directory '/home/vlad/projects/fun/labsFromUniversity/computer-algorithms'
// vlad@localhost:~/projects/fun/labsFromUniversity$ computer-algorithms/lab1
// by iteration=144
// by recursion=144
