#include <iostream>
#include <locale>
#include <set>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

int CheckedInput(int, int);

struct ArrayElem
{
    int key;
    ArrayElem* next;
};

void PrintArray(ArrayElem* array, int volume)
{
    for (int i = 0; i < volume; i++)
    {
        cout << array[i].key << " ";
    }
}

void PrintArray(ArrayElem** array, int volume)
{
    for (int i = 0; i < volume; i++)
    {
        cout << array[i]->key << " ";
    }
}

int GetVol()
{
    cout << "Введите объём массива (до 10000): "; 
    int volume = CheckedInput(1, 10000);
    return volume;
}

ArrayElem* CreateArrayWithUniques(int volume)
{
    
    ArrayElem* newArr = new ArrayElem[volume];
    ArrayElem temp;
    for (int i = 0; i < volume; i++)
    {
        newArr[i].key = i;
        newArr[i].next = nullptr;
    }

    for (int i = 0; i < volume; i++)
    {
        int index = rand() % volume;
        temp = newArr[index];
        newArr[index] = newArr[i];
        newArr[i] = temp;
    }


    cout << "Исходный массив: \n";
    PrintArray(newArr, volume);
    
    return newArr;
}

ArrayElem** CreateRandomArray(int volume, int maxKey)
{
    ArrayElem** array = new ArrayElem*[volume];
    for (int i = 0; i < volume; i++)
    {
        array[i] = new ArrayElem;
        array[i]->key = rand() % maxKey + 1;
        array[i]->next = nullptr;
    }
    cout << "Исходный массив:\n";
    PrintArray(array, volume);
    return array;
}

ArrayElem** CreateConstDigitArray(int volume, int k)
{
    ArrayElem** array = new ArrayElem * [volume];
    for (int i = 0; i < volume; i++)
    {
        array[i] = new ArrayElem;
        array[i]->key = rand() % (int)pow(10,k);
        array[i]->next = nullptr;
    }
    cout << "Исходный массив:\n";
    PrintArray(array, volume);
    return array;
}

void PocketSortWith2nd(ArrayElem* mas, int volume, int &countCompares, int &countExchanges)
{
    countCompares = countExchanges = 0;
    ArrayElem* _mas = new ArrayElem[volume];
    for (int i = 0; i < volume; i++)
    {
        _mas[mas[i].key] = mas[i];
        countExchanges++;
    }

    mas = _mas;
    PrintArray(mas, volume);

    delete[] _mas;
}

void PocketSortWithout2nd(ArrayElem* mas, int volume, int& countCompares, int& countExchanges)
{
    countCompares = countExchanges = 0;
    ArrayElem temp;
    int j;
    for (int i = 0; i < volume; i++)
    {
        while (mas[i].key != i)
        {
            countCompares++;
            temp = mas[i];
            j = mas[i].key;
            mas[i] = mas[mas[i].key];
            mas[j] = temp;
            countExchanges++;
        }
        countCompares++;
    }

    PrintArray(mas, volume);
}

void GeneralPocket(ArrayElem** mas, int volume, int maxKey, int& countCompares, int& countExchanges)
{
    countCompares = countExchanges = 0;
    ArrayElem** _mas = new ArrayElem * [maxKey + 1];
    ArrayElem* temp;

    for (int i = 0; i < maxKey + 1; i++)
    {
        _mas[i] = nullptr;
    }

    for (int i = 0; i < volume; i++)
    {
        if (_mas[mas[i]->key] == nullptr)
        {
            _mas[mas[i]->key] = mas[i];
        }

        else
        {
            temp = _mas[mas[i]->key];
            mas[i]->next = temp;
            _mas[mas[i]->key] = mas[i];
        }
    }

    temp = _mas[0];
    int j = 0;
    for (int i = 0; i < volume; i++)
    {
        while (temp == nullptr)
        {
            j++; temp = _mas[j];
        }
        mas[i] = temp;
        temp = temp->next;
    }

    delete[] _mas;
    PrintArray(mas, volume);
}

void SortBitwase(ArrayElem** mas, int volume, int k, int& countCompares, int& countExchanges)
{
    ArrayElem** subMas = new ArrayElem * [10];
    int div, mod, curr; 
    ArrayElem* temp;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            subMas[j] = nullptr;
        }

        mod = pow(10, i + 1); 
        div = pow(10, i);
        
        for (int j = 0; j < volume; j++)
        {
            curr = ((mas[j]->key) % mod) / div;
            if (subMas[curr] == nullptr)
            {
                mas[j]->next = nullptr;
                subMas[curr] = mas[j];
            }
            else
            {
                temp = subMas[curr];
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = mas[j];
                mas[j]->next = nullptr;
            }
        }
        
        temp = subMas[0];
        int k = 0;
        for (int j = 0; j < volume; j++)
        {
            while (temp == nullptr)
            {
                k++; temp = subMas[k];
            }
            mas[j] = temp;
            temp = temp->next;
        }
    }

    delete[] subMas;
    PrintArray(mas, volume);
}

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    bool work = true;
    int choice, maxKey, digCount;;
    int volume{ 0 };
    ArrayElem* arrCopy;
    ArrayElem* array;
    ArrayElem** mainArr, **mainArrCopy;
    while (work)
    {
        cout << "\nВыбор метода сортировки:\n1 - Карманная сортировка\n2 - Обобщённая карманная сортировка с повторяющими ключами и доп. списками\n3 - Подразрядная сортировка\n4 - Завершение работы\n";
        cout << "Действие: "; choice = CheckedInput(1, 4);
        int countCompares{ 0 }, countExchanges{ 0 };
        switch (choice)
        {
        case 1:
            volume = GetVol();
            
            array = CreateArrayWithUniques(volume);
            arrCopy = new ArrayElem[volume];
            memcpy(arrCopy, array, sizeof(ArrayElem) * volume);
            cout << "\nОтсортированный (с помощью второго массива) массив: \n";
            PocketSortWith2nd(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges << "\n\n";           

            memcpy(arrCopy, array, sizeof(ArrayElem) * volume);
            cout << "Отсортированный (без второго массива) массив: \n";
            PocketSortWithout2nd(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            
            delete[] array; array = nullptr;
            delete[] arrCopy; arrCopy = nullptr;
            
            break;
        
        case 2:
            cout << "Введите максимальное значение, которое могут принимать ключи (>= 0): "; maxKey = CheckedInput(0, 9999);
            cout << "Введите размер массива (оно должно быть строго больше макс. значения ключа, но не более 10000): "; volume = CheckedInput(maxKey + 1, 10000);
            mainArr = CreateRandomArray(volume,maxKey);
            mainArrCopy = new ArrayElem*[volume];
            memcpy(mainArrCopy, mainArr, sizeof(ArrayElem*) * volume);
            cout << "\nОтсортированный массив : \n";
            GeneralPocket(mainArrCopy,volume,maxKey,countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;

            for (int i = 0; i < volume; i++)
            {
                delete mainArr[i];
            }
            delete[] mainArr; mainArr = nullptr;
            delete[] mainArrCopy; mainArrCopy = nullptr;
            
            cout << "\n\n";
            break;
        
        case 3:
            cout << "Скольки разрядные числа будут в массиве (от 1 до 5): "; digCount = CheckedInput(1, 5);
            volume = GetVol();
            mainArr = CreateConstDigitArray(volume, digCount);
            mainArrCopy = new ArrayElem * [volume];
            memcpy(mainArrCopy, mainArr, sizeof(ArrayElem*) * volume);
            cout << "\nОтсортированный массив : \n";
            SortBitwase(mainArrCopy, volume, digCount, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            
            for (int i = 0; i < volume; i++)
            {
                delete mainArr[i];
            }
            delete[] mainArr; mainArr = nullptr;
            delete[] mainArrCopy; mainArrCopy = nullptr;
            
            cout << "\n\n";
            break;
        
        case 4:
            work = false;
            break;
       
        default:
            break;
        }
    }

    _CrtDumpMemoryLeaks();
}
