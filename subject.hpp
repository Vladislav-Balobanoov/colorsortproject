#pragma once
#include <iostream>
#include <string>
/*
* Описание класса объектов имеющих цвет.
*/

// Шаблонный класс:
template <class T>
class subject 
{
public:
	subject();			// Конструктор по умолчанию.
	subject(char, T);	// Конструктор с 2-мя параметрами.
	subject(char);		// Конструктор с параметром 'цвет'.

	// Геттеры:
	void setColor(char);
	void setData(T);
	// Сеттеры:	
	char getColor() const;	
	T getData() const;		
private:
	T data{};		// Некоторое данное.
	char color;		// Цвет.
};
// Конструктор по умолчанию:
template<typename T> 
subject<T>::subject() : color('r')
{
}
// Конструктор с параметрами:
template<typename T> 
subject<T>::subject(char m_color, T m_data) : color(m_color),
	data(m_data)	
{	
}
// Конструктор с параметром 'цвет':
template<typename T> 
subject<T>::subject(char m_color) : color(m_color)
{
}
// Установить цвет:
template<typename T> 
void subject<T>::setColor(char m_color)
{ 
	color = m_color;
}
// Установить данное:
template<typename T>
void subject<T>::setData(T m_data)
{
	data = m_data;
}
// Получить цвет:
template<typename T> 
char subject<T>::getColor() const
{
	return color;
}
// Получить данное:
template<class T>
T subject<T>::getData() const
{
	return data;	// ���������� ��������.
}