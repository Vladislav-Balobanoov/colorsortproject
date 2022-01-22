#include "additonalfunc.hpp"
#include "subject.hpp"
#include <iostream>
#include "rthread.hpp"
#include <thread>
#include <mutex>
#include <algorithm>
/*
*  Основной файл программы.
*/

int main()
{
	char check;			// Переменная для ввода команды с клавиатуры.
	bool flag = true, 	// Основной флаг для продолжения/остановки работы с программой
	gFlag = true, 		// Алаг генерации.
	sFlag = true;		// Флаг сортировки.
	size_t count = 0;	// Количество элементов в наборе.
	std::string rule;	// Правило для сортировки по цветам.
	std::vector<subject<int>> subjects; // Набор объектов, которые будут отсортированы. 

	while (flag)		// Основной цикл отвечайщий за работу программы до тех пор пока пользователь не захочет выйти.
	{
		std::cout << "Hello.\nPlease, insert rule(example: \"rgb\") - ";
		std::getline(std::cin, rule);	// Ввод правила с клавиатуры в формате строка из 3-х символов.

		std::cout << "Please, insert count of subjects: ";
		// /std::cin >> count;				
		while (!(std::cin >> count))	// Количество объектов для генерации. 
		{
			// Проверка ввода на случай ввода не числа а символа или строки.
			std::cin.clear();
			while (std::cin.get() != '\n')
				continue;
			
			std::cout << "It is wrong count, plese try agqin!\nInsert count here: ";
		}
		
		{
			std::cout << "Do you want to generate array? Y/N - ";
			std::cin >> check;				// Ввод символа y/n для начала/остановки генерации.
			gFlag = threadSwitch(check);	// Вызов функции для переключения состояний потоков.
			rThread th_1(std::thread([&]() {gFlag = generate(count, subjects); }));		// Генерация.

			std::cout << "Do you want to sort array? Y/N - ";
			std::cin >> check;				// Ввод символа y/n для начала/остановки сортировки.
			sFlag = threadSwitch(check);	// Вызов функции для переключения состояний потоков.
			rThread th_2(std::thread([&]() {sFlag = sortColors(subjects, rule); }));	// Сортировка.
		}

		if (gFlag && sFlag)	{	// Если оба потока отработали выводим результат.
		
			std::cout << std::endl << "=====Result=====\n";
			print(subjects);
		} else {				// Иначе выводим сообщение.
		
			std::cout << "Something was wrong\n";
		}

		std::cout << "Do you want to exit? Y/N - ";
		std::cin >> check;				// Проверка хочет ли пользователь продолжить работу.
		flag = !inputChecker(check);	// Вызываем функцию проверки ввода.

		subjects.clear();	// Отчистка массива для дальнейшей работы.
		rule.clear();		// Отчистка правила для дальнейшей работы.
		std::cin.get();		// Отчистка для повторного ввода с клавиатуры.
	}

	return 0;
}