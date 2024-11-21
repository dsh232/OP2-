#include <iostream>
#include <math.h>
#include <string>
#include <iomanip> //для использования setw (устанавливает ширину поля для следующего вывода.)

// Корректный ввод дробного значения. Проверка на ввод.

//Методы. 
//cin.clear() - меняет состояние потока на good
//cin.peek() - смотрит следующий символ в потоке, но не извлекает.
//cin.get() - извлекает символ из потока (кушает)
std::string doubleInput() {
	std::string input;
	std::cin >> input;
	return input;
}

// Корректный ввод на продолжить/остановить программу. Проверка на ввод.
char charAnswer1()
{
	char input;
	while (!(std::cin >> input) || std::cin.peek() != '\n')
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Некорректный ввод. Повторите снова. " << std::endl;
		std::cout << "Хотите продолжить? (Y/N):  ";
	}
	return input;
}

// Подсчёт всех нужных значений
void calculation(int& n, double x, double& a, double& a_next, double& Sn, double& alpha_n) {

	a = a_next;	// Обновляем значение a
	Sn += a;	// Прибавляем значение a к частичной сумме Sn
	n++;
	a_next = a * (-x * x * (2 * (n)) * (2 * n - 1)) / ((2 * n + 2) * (2 * n + 1));		// Вычисляем следующее значение 
	alpha_n = std::abs(a_next / Sn);      // Вычисляем альфа_n как отношение |a_next| к |Sn|
}
bool IfDouble(std::string str) { // Преобразование double в string
	bool hasDecimalPoint = false; // Флаг для проверки наличия десятичной точки
	bool hasDigits = false; // Флаг для проверки наличия цифр

	for (size_t i = 0; i < str.size(); ++i) {
		// Проверка на знак числа
		if (i == 0 && (str[i] == '-' || str[i] == '+')) {
			continue; // Пропускаем знак в начале строки
		}

		if (std::isdigit(str[i])) {
			hasDigits = true; // Найдена цифра
		}
		else if (str[i] == '.') {
			if (hasDecimalPoint) {
				return false; // Найдена вторая точка
			}
			hasDecimalPoint = true; // Устанавливаем флаг для первой точки
		}
		else {
			return false; // Найден недопустимый символ
		}
	}

	return hasDigits && hasDecimalPoint; // Возвращаем true, если есть цифры и одна точка
}

int main()
{
	setlocale(LC_ALL, "ru");	// установка русской локализации вывода в консоли
	bool flag = false; //создание флага для повторного запуска программы
	while (!flag) { //цикл для повторного использования программы
		double x, alpha, alpha_n, a, a_next, Sn = 0, sum = 1;

		// Ввод параметра x запрашивается до тех пор, пока пользователь не введёт число соответсвующее требованиям.
		do
		{
			std::cout << "Введите параметр -1 < x < 1 : ";
			std::string str = doubleInput();
			x = std::stod(str);

		} while ((x > 1 || x < -1));

		a_next = x * x / 2;
		std::string str_alpha;

		// Ввод параметра alpha запрашивается до тех пор, пока пользователь не введёт положительное число.
		do
		{
			std::cout << "Введите параметр alpha (Положительное число):" << std::endl;
			str_alpha = doubleInput();
			alpha = std::stod(str_alpha);

		} while (alpha <= 0);


		int n = 0;
		//Для красоты вывода
		std::cout << std::setw(5) << "n"
			<< std::setw(15) << "a"
			<< std::setw(15) << "Sn"
			<< std::setw(15) << "alpha_n" << "\n\n";

		do {
			calculation(n, x, a, a_next, Sn, alpha_n); // Считаем данные
			// Выводим данные с установленной шириной

			std::cout << std::setw(5) << n
				<< std::setw(15) << a
				<< std::setw(15) << Sn
				<< std::setw(15) << alpha_n << std::endl;

		} while ((!IfDouble(str_alpha) && n < alpha) || (IfDouble(str_alpha) && alpha_n > alpha));

		bool flag2 = false;
		do {
			std::cout << "Хотите продолжить? (Y/N):  ";
			char answer;
			answer = charAnswer1();
			if (answer == 'N') {
				std::cout << "Пока!" << std::endl;
				flag = true;
				flag2 = true;
			}
			else if (answer == 'Y') {
				std::cout << "Продолжить? конечно!" << std::endl;
				flag2 = true;
			}

		} while (!flag2);
	}
}