#include <iostream>
#include <vector>

std::vector<std::vector<int>> A;
std::vector<int> answer;
std::vector<int> weights;
std::vector<int> prices;

void findComplect(int k, int s)
{
    if(A[k][s] == 0)
        return;
    if(A[k-1][s] == A[k][s])
        findComplect(k-1, s);
    else
    {
        findComplect(k-1, s - weights[k]);
        answer.push_back(k);
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int weight, price, n = 0;
    std::cout << "Введите вес и стоимость предмета(для прекращения введите отрицательные значения): " << std::endl;
    std::cout << ++n << ": ";
    std::cin >> weight >> price;
    while (weight > 0 && price > 0)
    {
        weights.push_back(weight);
        prices.push_back(price);
        std::cout << ++n << ": ";
        std::cin >> weight >> price;
    }
    std::cout << "Введите максимальный вес: ";
    std::cin >> weight; 
    std::cout << std::endl;

    A.resize(weights.size(), std::vector<int>(weight, 0));
    for (int i = 0; i < weights.size(); i++)
    {
        for (int j = 0; j < weight; j++)
        {
            if(weights[i] <= j+1) 
            {
                if(i == 0)
                    A[i][j] = prices[i];
                else
                { 
                    if(j == 0) 
                        A[i][j] = prices[i];
                    else
                        A[i][j] = (A[i-1][j] > A[i-1][j-1]+prices[i]) ? A[i-1][j] : A[i-1][j-1]+prices[i];
                }
            }
        }
    }
    std::cout << "Максимальная стоимость: " << A[weights.size()-1][weight-1] << std::endl;
    /*for (int i = 0; i < answer.size(); i++)
    {
        std::cout << "Предмет: " << answer[i] << "\tСтоимость: " << prices[answer[i]] << std::endl;
    }*/
    return 0;
}
