#pragma once
#include <thread>

//  Класс для реализации принципа RAII при работе с потоками.
class rThread
{
public:
	rThread(std::thread&& thread) : _thread(std::move(thread))
	{ }
	~rThread() { _thread.join(); }
private:
	std::thread _thread;
};