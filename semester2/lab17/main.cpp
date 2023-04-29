#include <iostream>
#include <vector>

std::vector<int> weights;
std::vector<std::vector<int>> containers;
std::vector<int> weightInContainer;
std::vector<bool> packed;

void packByBoxes(int weight)
{
    for (int i = 0; i < packed.size(); i++)
    {
        if (!packed[i])
        {
            if (containers.size() == 0) //Обработка первого контейнера
            {
                if(weights[i] <= weight)    //Если предмет вмещается в контейнер, то пакуем его 
                {
                    containers.push_back(std::vector<int> {i});
                    weightInContainer.push_back(weights[i]);
                    packed[i] = true;
                }
                else    //Иначе помечаем предмет как упакованный, но не пакуем
                {
                    packed[i] = true;
                }
            }
            else    //Если контейнер не первый
            {
                for (int j = 0; j < containers.size(); j++)   //Перебираем контейнеры, ищем первый, в который поместится
                {
                    if (weights[i] <= weight - weightInContainer[j])    //если предмет помещается, кладём его и прерываем цикл
                    {
                        containers[j].push_back(i);
                        weightInContainer[j] += weights[i];
                        packed[i] = true;
                        break;
                    }
                }
                if (!packed[i])  //если не нашлось ящика, способного вместить очередной предмет
                {
                    containers.push_back(std::vector<int> {i});
                    weightInContainer.push_back(weights[i]);
                    packed[i] = true;
                }

            }
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int weight, n = 0;
    std::cout << "Введите вес предмета(для прекращения введите отрицательное значение): " << std::endl;
    std::cout << ++n << ": ";
    std::cin >> weight;
    while (weight > 0)
    {
        weights.push_back(weight);
        std::cout << ++n << ": ";
        std::cin >> weight;
    }
    std::cout << "Введите вместимость контейнеров: ";
    std::cin >> weight; 
    std::cout << std::endl;

    n--;    //Заполняем векторы предварительными данными
    packed.resize(n, false);


    packByBoxes(weight);
    for (int i = 0; i < containers.size(); i++)
    {
        std::cout << "Контейнер №" << i << ": ";
        for (int item : containers[i])
        {
            std::cout << weights[item] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
