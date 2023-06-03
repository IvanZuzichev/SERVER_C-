#include <iostream>
#include <thread>
#include <string>

#include "CServer_UDP.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	CServer_UDP server_UDP;

	thread recProc(&CServer_UDP::RecMsg, &server_UDP);

	while (1)
	{
		cout << "Введите контент: " << endl;
		string content;
		cin >> content;
		server_UDP.SendMsg(content.c_str());
	}

	recProc.join();
	cout << "Пример!" << endl;
	system("pause");
	return 0;
}