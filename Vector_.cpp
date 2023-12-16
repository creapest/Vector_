#include <iostream>

template <typename T>
class Vector_
{
public:
    Vector_(int size, T fill = 2147483647)
    {
        vector = new T[size];
        for (int i = 0; i < size; i++)
        {
            vector[i] = fill;
        }
        _fill = fill;
        len = size;
    }

    Vector_()
    {
        vector = new T[0];
        len = 0;
    }

    template <std::size_t N>
    Vector_(T (&arr)[N])
    {
        len = (sizeof(arr) / sizeof(*arr));
        vector = new T[len];
        for (int i = 0; i < len; i++)
        {
            vector[i] = arr[i];
        }
    }

    Vector_(std::initializer_list<T> list)
    {
        const T *list_ptr = list.begin();
        vector = new T[list.size()];
        len = list.size();
        for (int i = 0; i < list.size(); i++)
        {
            vector[i] = *(list_ptr + i);
        }
    }
    ~Vector_()
    {
        delete[] vector;
    }

    // @brief возвращает количество элементов вектора
    // @return длинна массива
    template <typename cap_t>
    int capacity()
    {
        return len;
    }

    // @brief расширяет вектор до введеного кол-ва мест, незаполненные места заполняются fill
    // @param new_len длинна нового массива
    void reserve(int new_len)
    {
        T *temp_vector = new T[new_len];
        for (int i = 0; i < new_len; i++)
        {
            if (i < len)
            {
                temp_vector[i] = vector[i];
            }
            else
            {
                temp_vector[i] = _fill;
            }
        }
        delete[] vector;
        vector = temp_vector;
    }

    // @brief убирает из вектора незаполненные эллементы
    void shrink_to_fit()
    {
        int index = 0;
        int real_len = 0;
        for (int i = 0; i < len; i++)
        {
            if ((vector[i] != 2147483647) and (vector[i] != _fill))
            {
                real_len++;
            }
        }
        T *temp_vector = new T[real_len];
        for (int i = 0; i < len; i++)
        {
            if ((vector[i] != 2147483647) or (vector[i] != _fill))
            {
                temp_vector[index] = vector[i];
                index++;
            }
        }
        len = real_len;
        delete[] vector;
        vector = temp_vector;
    }

    // @brief добавляет элемент в конец вектора
    // @param item новый элемент
    void push_back(T item)
    {
        T *temp_vector = new T[len + 1];
        for (int i = 0; i < len; i++)
        {
            temp_vector[i] = vector[i];
        }
        temp_vector[len] = item;
        delete[] vector;
        vector = temp_vector;
        len++;
    }

    // @brief удаляет последний элемент вектора
    void pop_back()
    {
        T *temp_vector = new T[len - 1];
        for (int i = 0; i < len - 1; i++)
        {
            temp_vector[i] = vector[i];
        }
        delete[] vector;
        vector = temp_vector;
        len--;
    }

    // @brief выводит на экран значения из вектора
    void print()
    {
        for (int i = 0; i < len; i++)
        {
            std::cout << vector[i] << "\t";
        }
        std::cout << std::endl;
    }

    // @brief возвращает неизменяемый указатель на первый эллемент вектора
    // @return const type *arr
    const T *cbegin()
    {
        const T *temp = vector;
        return temp;
    }

    // @brief возвращает неизменяемый указатель на  позицию, следующую за концом вектора
    // @return const type *arr
    const T *cend()
    {
        const T *temp = vector + len - 1;
        return temp;
    }

    // @brief удаляет все элементы вектора
    void clear()
    {
        T *temp_vector = new T[0];
        delete[] vector;
        vector = temp_vector;
        len = 0;
    }

    // @brief возвращает изменямый указатель на первый эллемент вектора
    T *data()
    {
        return vector;
    }

    // @brief проверяет есть ли в векторе заполненные значения
    // @return true/false
    bool empty()
    {
        int k = 0;
        for (int i = 0; i < len; i++)
        {
            if (*(vector + i) == _fill)
            {
                k++;
            }
        }
        if (k == len)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // @brief Удаляет элемент вектора на заданной позиции.
    // @param pos_to_remove индекс удаляемого элемента
    void erase(int pos_to_remove)
    {
        int index = 0;
        T *temp_vector = new T[len - 1];
        for (int i = 0; i < len; i++)
        {
            if (i != pos_to_remove)
            {
                temp_vector[index] = vector[i];
                index += 1;
            }
        }
        len -= 1;
        delete[] vector;
        vector = temp_vector;
    }

    // @brief Удаляет диапазон элементов в векторе из заданных позиций.
    // @param pos_to_remove_begin Положение первого элемента, удаляемого из вектора
    // @param pos_to_remove_end Положение последнего элемента, удаляемого из вектора
    void erase(int pos_to_remove_begin, int pos_to_remove_end)
    {
        int index = 0;
        int temp_iter = pos_to_remove_begin;
        T *temp_vector = new T[len - (pos_to_remove_end - pos_to_remove_begin) + 1];
        for (int i = 0; i < len; i++)
        {
            if (i != temp_iter)
            {
                temp_vector[index] = vector[i];
            }
            else
            {
                if (temp_iter != pos_to_remove_end)
                {
                    temp_iter++;
                    index--;
                }
            }
        }
        len -= (pos_to_remove_end - pos_to_remove_begin + 1);
        delete[] vector;
        vector = temp_vector;
    }

    // @brief вставляет элемент по заданной позиции
    // @param pos_to_fill индекс, на который
    void insert(int pos_to_fill, T fill)
    {
        int index = 0;
        T *temp_vector = new T[len + 1];
        for (int i = 0; i < len + 1; i++)
        {
            if (i != pos_to_fill)
            {
                temp_vector[i] = vector[index];
                index++;
            }
            else
            {
                temp_vector[i] = fill;
            }
        }
        delete[] vector;
        vector = temp_vector;
        len++;
    }

    template <std::size_t N>
    void operator=(T (&arr)[N])
    {
        this->len = (sizeof(arr) / sizeof(*arr));
        T *temp_vector = new T[len];
        delete[] vector;
        for (int i = 0; i < len; i++)
        {
            this->temp_vector[i] = arr[i];
        }
        vector = temp_vector;
    }

    auto operator[](int pos) const -> T &
    {
        return *(this->vector + pos);
    }

private:
    T *vector = vector;
    int len;
    T _fill = 2147483647;
};

int main()
{

    Vector_<int> arr1(2);
    Vector_<int> arr2;
    int arr[7] = {1, 2, 123, 123, 32, 52, 653};
    Vector_<int> arr3(arr);
    Vector_<int> arr4 = {1, 2, 3, 4, 5};
    Vector_<int> arr5(5, 10);

    return 0;
}