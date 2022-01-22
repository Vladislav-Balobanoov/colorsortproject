#pragma once
#include <iostream>
#include <string>
#include "subject.hpp"
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

/*
* Библиотека содержит вспомогательные функции, 
* а также функции генерации и сортировки.
*/

namespace // Глобальные переменные.
{
	std::atomic<bool> ready(false);
	std::atomic<bool> quit(false);
	std::mutex mtx;
	std::condition_variable cv;
}

bool inputChecker(char ch)
{
	return ch == 'y' ? true : false;
}

bool threadSwitch(char ch)
{
	if(inputChecker(ch)) {
		ready = true;
		quit = false;
		cv.notify_all();
	} else {
		ready = false;
		quit = true;
		cv.notify_all();
	}
}
// Вывод:
template<typename T>
void print(std::vector<subject<T>>& subjects)
{
	for (subject<T> subject : subjects)
		std::cout << subject.getColor() << ' ';
	std::cout << std::endl;
}
// Функция для проверки правила на соответствие:
bool checkRule(const std::string& str)
{
	for (auto i = 0; i < str.size(); i++)
	{
		if (str[i] != 'r' && str[i] != 'g' && str[i] != 'b') // В случае, если правило содержит не те символы,
		{
			return false;	// будет возвращено значение "ложь".
		}
		else if (i != 0 && str[i-1] == str[i])				// Или если символы повторяются.
		{
			return false;
		}
	}
			
	return true;
}
// Рандомизатор цветов:
char randChar()		// Возвращает случайным образом символ из вариантов 'r', 'g' и 'b'.
{
	int randInt = rand() % 10 + 1;
	
	if (randInt < 3)
		return 'r';
	else if (randInt < 6)
		return 'g';
	else return 'b';
}
// Генратор набора объектов:
template <typename T>
bool generate(int count, std::vector<subject<T>>& subjects)
{
	std::unique_lock<std::mutex> ul(mtx);	// Для работы в отдельном потоке и избежания гонки данных.
	cv.wait(ul, [] {return ready || quit; });
	if (quit) {								// В случае, если 'quit' = true завершение работы генератора.
		return false;
	}
	// Проверка корректности полученного размера:
	if (count <= 0) {
		quit = true;
		ready = false;
		cv.notify_one();
		return false;
	}
	// Генерация:
	for (int i = 0; i < count; i++)
	{
		subjects.push_back(subject<int>(randChar()));
	}
	// Сообщение о завершении процесса генерации:
	ready = true;
	cv.notify_one();
	return true;
}
// Сортировка:
template<typename T>
bool sortColors(std::vector<subject<T>>& subjects, std::string rule)	// Принимает набор и правило сортировки.
{
	std::unique_lock<std::mutex> ul(mtx);	

	cv.wait(ul, [] {return ready || quit; });	// Ждёт сообщение о том, что можно начать сортировку.
	if (quit){
		return false;
	}
	
	if (rule.size() != 3) {		// Проверка размера правила.
			return false;
	} 
	if (!checkRule(rule)) {		// Проверка на корректность введённых цветов.
		return false;
	}

	int j = 0; // Инедекс первого не соответствия цвета объекта и парвила.
	/*
	*****Алгоритм*****
	* 1. выбирается k-й символ из правила.
	* 2. До тех пор пока не пройдём весь набор объектов,
	* проверяем совпадает ли цвет и индексы i и j не равны, 
	* сдвигаем оба индекса, если да.
	* Если нет переходим к шагу 3.
	* 3. Индекс j не изменяется, а i пробегает вектор до тех пор,
	* пока не совпадёт цвет из шаблона с цветом объекта.
	* 4. Меняем местами тем самым объект с нужным цветом встаёт на своё место.
	* 5. Сдвигаем j на один вправо, повторяем с шага 2.
	* 6. Как только заканчивается вектор берём следующий цвет из правила и возвращаемся к (1).
	*/
	// Сортировка:
	for (int k = 0; k < rule.size(); k++)
	{
		for (auto i = j; i < subjects.size(); i++)
		{
			if (subjects[i].getColor() == rule[k] && j == i) {
				j++;
			
			} else	{
				while (i < subjects.size())
				{
					if (subjects[i].getColor() != rule[k]) {
						i++;
					} else break;
				}

				if (i < subjects.size()) {
					std::swap(subjects[j], subjects[i]);
					j++;
				}
			}
		}
	}
	
	return true;
}