#include <iostream>
#include <vector>
#include <string>

using namespace std;

int get_digit(char sim)
{
    if (sim == 'I')
        return 1;

    if (sim == 'V')
        return 5;

    if (sim == 'X')
        return 10;

    if (sim == 'L')
        return 50;

    return -1;
}

int rome2arabic(string number)
{
    int num = 0;
    int prev_digit = get_digit(number[number.size() - 1]);
    num += prev_digit;

    for (int i = number.size() - 2; i >= 0; --i)
    {
        int digit = get_digit(number[i]);
        if (digit < prev_digit)
            num -= digit;
        else
            num += digit;

        prev_digit = digit;
    }

    return num;
}

struct King
{
    string name;
    string number_rome;
    int number;

    bool operator>(King b)
    {
        if (this->name > b.name)
            return true;
        else if (this->name == b.name)
            return this->number > b.number;
        return false;
    }

    void operator=(King b)
    {
        this->name = b.name;
        this->number = b.number;
        this->number_rome = b.number_rome;
    }
};

void quadratic_sort(vector<King> &array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if ((array[j - 1] > array[j]))
            {
                King tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
        }
    }
}

/*

2
Louis IX
Louis VIII

*/

int main()
{
    vector<King> kings;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string name;
        string number_rome;
        King king;
        cin >> name >> number_rome;

        king.name = name;
        king.number_rome = number_rome;
        king.number = rome2arabic(number_rome);
        kings.push_back(king);
    }

    quadratic_sort(kings);

    for (size_t i = 0; i < kings.size(); ++i)
    {
        cout << kings[i].name << " " << kings[i].number_rome << endl;
    }

    return 0;
}