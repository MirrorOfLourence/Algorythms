#include <iostream>

/*int main()
{
	int x;
	std::cout << "Enter x" << std::endl;
	std::cin >> x;
	for (int i = 1; i <= x; i++)
	{
		int value = i;
		while (value % 3 == 0)
			value /= 3;
		while (value % 5 == 0)
			value /= 5;
		while (value % 7 == 0)
			value /= 7;
		if (value == 1)
			std::cout << i << std::endl;
	}

	int a;
	std::cin >> a;
	return 0;
}*/

int main()
{
	long long int x;
	long long int a = 1;
	std::cout << "Enter x" << std::endl;
	std::cin >> x;
	while (a <=x)
	{
		long long int b = a;
		while (b<=x)
		{
			long long int c = b;
			while (c<=x)
			{
				std::cout << c << std::endl;
				c *= 7;
			}
			b *= 5;
		}
		a *= 3;
	}

	int ans;
	std::cin >> ans;

	return 0;
}