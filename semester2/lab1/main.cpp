#include <iostream>
#include <vector>

class Point	//класс точки
{
public:
	Point();
	Point(int x, int y)
		:x(x), y(y)
	{
	}
	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
};

float getAngleFirst(Point& A, Point& B)
{
	if ((A.getX() == B.getX()))	//если точки A и B совпадают или составляют вертикальный вектор
		return 0;
	if ((A.getY() == B.getY()))	//если точки A и B составляют горизонтальный вектор
		return 1;
	Point v1(1, 0);		//точками задаём векторы: горизонтальный
	Point v2(A.getX() - B.getX(), A.getY() - B.getY());	//и из данных точек
	return ((v1.getX() * v2.getX() + v1.getY() * v2.getY())	//вычисляем cos угла между v1 и v2
		/ (sqrt(v1.getX() * v1.getX() + v1.getY() * v1.getY()) * sqrt(v2.getX() * v2.getX() + v2.getY() * v2.getY())));
}

float getAngle(Point& A, Point& B, Point& C)
{
	Point v1(C.getX() - A.getX(), C.getY() - A.getY());		//точками задаём векторы: 1 из данных точек (AC)
	Point v2(A.getX() - B.getX(), A.getY() - B.getY());	//и из данных точек (BA)
	return ((v1.getX() * v2.getX() + v1.getY() * v2.getY())	//вычисляем cos угла между v1 и v2
		/ (sqrt(v1.getX() * v1.getX() + v1.getY() * v1.getY()) * sqrt(v2.getX() * v2.getX() + v2.getY() * v2.getY())));
}

void show(std::vector<Point>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << "(" << v[i].getX() << ", " << v[i].getY() << ")" << std::endl;
	}
}

void checkShell(std::vector<Point>& v)	//ф-ия проверки существования выпуклой оболочки
{
	int yMin = INT_MAX, current = 0, numOperated = 0, length = v.size();
	//numOperated - число включённых в оболочку точек; current - текущая точка(в 1 for - нижняя точка)
	std::vector<Point> answ;
	for (int i = 0; i < v.size(); i++)	//ищем нижнюю точку из заданных
	{
		if (v[i].getY() < yMin)
		{
			yMin = v[i].getY();
			current = i;
		}
		else if ((v[i].getY() == yMin) && (v[i].getX() < v[current].getX()))	//если нашли нижнюю, но более левую точку
			current = i;
	}
	if (yMin == INT_MAX)	//если нижней не нашлось, выходим из функции
	{
		std::cout << "Нельзя построить выпуклую оболочку!" << std::endl;
		return;
	}
	else	//иначе продолжаем проверку
	{
		answ.push_back(v[current]);		//добавим в ответ найденную вершину
		std::swap(v[current], v[length - 1]);	//переносим нижнюю точку в конец вектора
		numOperated++;
		
		bool firstAngle = true;
		current = length - numOperated;

		while (true)
		{
			float maxPr = 0;	//maxPr - максимальное значение при cos(a) 
			if (firstAngle)	//если обрабатываем первый угол, сравниваем с горизонталью
			{
				for (int i = 0; i < length - numOperated; i++)
				{
					float value = getAngleFirst(v[i], v[length - numOperated]);
					if (value > maxPr)
					{
						maxPr = value;
						current = i;
					}
				}
				answ.push_back(v[current]);		//добавим в ответ найденную вершину
				numOperated++;	//инкремент количества обработанных точек
				std::swap(v[current], v[length - numOperated]);	//переносим нижнюю точку в конец вектора

				firstAngle = false;	//снимает флаг первого угла
			}
			else	//иначе сравниваем с новой прямой, составленной из двух предыдущих добавленных точек
			{
				for (int i = 0; i < length - numOperated; i++)
				{
					float value = getAngle(v[length - numOperated], v[length - numOperated + 1], v[i]);
			
					if ((value < 0) && (maxPr == 0))
					{ 
						maxPr = -1;	//если maxPr = 0, то это первый угол с отрицательным косинусом, нужно новое сравнение
					}

					if (value > maxPr)
					{
						maxPr = value;
						current = i;
					}
					else if (value == maxPr)
					{
						if (v[i].getX() > v[current].getX())
						{
							maxPr = value;
							current = i;
						}
					}
				}
				
				float value = getAngle(v[length - numOperated], v[length - numOperated + 1], v[length-1]);
				if (value > maxPr)
				{
					std::cout << "Выпуклая оболочка состоит из точек: " << std::endl;
					show(answ);
					return; 
				}
				if (numOperated < length)
				{
					answ.push_back(v[current]);		//добавим в ответ найденную вершину
					numOperated++;	//инкремент количества обработанных точек
					std::swap(v[current], v[length - numOperated]);	//переносим нижнюю точку в конец вектора
					maxPr = 0;
				}
				else
				{ 
					std::cout << "Выпуклая оболочка состоит из точек: " << std::endl;
					show(answ);
					return; 
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::vector<Point> vertexes;

	int counter;
	std::cout << "Сколько точек хотите ввести?" << std::endl;
	std::cin >> counter;

	for (int i = 0; i < counter; i++)
	{
		int x = 0, y = 0;
		std::cout << "Введите координату X: ";
		std::cin >> x;
		std::cout << "Введите координату Y: ";
		std::cin >> y;
		std::cout << std::endl;

		vertexes.push_back(Point(x, y));
	}
	if (vertexes.size() > 2)
	{
		checkShell(vertexes);
	}
	else
	{
		std::cout << "Нельзя построить выпуклую оболочку!" << std::endl;
	}
	return 0;
}
