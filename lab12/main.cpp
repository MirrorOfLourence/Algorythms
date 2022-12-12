//внешняя многофазная

//подключение библиотеки для открытия файлов и записи
#include <fstream>
#include <iostream>
#include <random>

int main()
{
	srand(time(0));
	std::ifstream in, in1, in2; // создаем объекты класса ifstream (файлового ввода)
	std::ofstream out, out1, out2, first; //создаем объекты класса ofstream (файлового вывода)

	first.open("input.txt", std::ios::out || std::ios::trunc);
	for (int i = 0; i < 99; i++)
	{
		first << rand()%1000 << std::endl;
	}
	first << rand()%1000;

	first.close();

	int a, b = 0;
	//кол-во чисел в файле
	int size = 0;
	int countA, countB, count = 0;
	bool flag = true;
	bool Afull, Bfull = true;

	in.open("input.txt");
	out.open("output.txt");

	while (in >> a)
	{
		out << a << "\n";
		size++;
	}

	in.close();
	out.close();
	/*длина серий фиксируется на каждом шаге.
	В исходном файле все серии имеют длину 1,
	после первого шага она равна 2, после второго – 4,
	после третьего – 8, после k -го шага – 2k*/
	for (int partSize = 1; partSize < size; partSize *= 2)
	{
		//Исходный файл f разбивается на два вспомогательных файла 
		in.open("output.txt");
		out1.open("A.txt");
		out2.open("B.txt");
		count = 0;
		while (in >> a)
		{
			count++;
			if (flag) 
				out1 << a << "\n";
			else 
				out2 << a << "\n";

			if (count == partSize)
			{
				count = 0;
				flag = !flag;
			}
		}
		in.close();
		out1.close();
		out2.close();
		//remove("result.txt");

		in1.open("A.txt");
		in2.open("B.txt");
		out.open("output.txt");

		//вспомогательные файлы сливаются в файл 
		// при этом одиночные элементы образуют упорядоченные пары.
		if (in1 >> a) 
			Afull = true;
		else 
			Afull = false;
		if (in2 >> b) 
			Bfull = true;
		else 
			Bfull = false;
		//Полученный файл  вновь обрабатывается
		//При этом упорядоченные пары переходят в упорядоченные четверки.
		for (int i = 0; i < size; i += 2 * partSize)
		{
			countA = 0; countB = 0;
			while (countA < partSize && Afull && countB < partSize && Bfull)
				if (a < b)
				{
					out << a << "\n";
					if (in1 >> a) 
						Afull = true;
					else 
						Afull = false;
					countA++;
				}
				else
				{
					out << b << "\n";
					if (in2 >> b) 
						Bfull = true;
					else 
						Bfull = false;
					countB++;
				}
			//Повторяя шаги, сливаем четверки в восьмерки и т.д.,
			//каждый раз удваивая длину слитых последовательностей до тех пор, пока не будет упорядочен целиком весь файл
			while (countA < partSize && Afull)
			{
				out << a << "\n";
				if (in1 >> a) 
					Afull = true;
				else 
					Afull = false;
				countA++;
			}
			while (countB < partSize && Bfull)
			{
				out << b << "\n";
				if (in2 >> b) 
					Bfull = true;
				else 
					Bfull = false;
				countB++;
			}

		}

		in1.close();
		in2.close();
		out.close();
		remove("A.txt");
		remove("B.txt");
	}
	return 0;
}
