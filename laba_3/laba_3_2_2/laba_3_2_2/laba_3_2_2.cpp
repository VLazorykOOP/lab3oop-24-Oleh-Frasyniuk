#include <iostream>
//використання state дозволяє контролювати стан об'єкта та виявляти можливі проблеми при його використанні. size - виділення памяті

class Vector {
private:
    float* ptr;
    int size;
    int& state;

public:
    //конструктори
    Vector() : ptr(new float[1]), size(1), state(size) {
        if (!ptr)
            state = -1; //помилка, не вистачає пам'яті
        else
            *ptr = 0.0f; //ініціалізуємо перший елемент вектора нулем
    }

    Vector(int s) : ptr(new float[s]), size(s), state(size) {
        if (!ptr)
            state = -1; //помилка, не вистачає пам'яті
        else {
            for (int i = 0; i < size; ++i)
                ptr[i] = 0.0f; //ініціалізуємо всі елементи вектора нулями
        }
    }

    Vector(int s, float value) : ptr(new float[s]), size(s), state(size) {
        if (!ptr)
            state = -1; //помилка, не вистачає пам'яті
        else {
            for (int i = 0; i < size; ++i)
                ptr[i] = value; //ініціалізуємо всі елементи вектора значенням value
        }
    }

    //конструктор копіювання
    Vector(const Vector& other) : ptr(new float[other.size]), size(other.size), state(other.state) {
        if (!ptr)
            state = -1; //помилка, не вистачає пам'яті
        else {
            for (int i = 0; i < size; ++i)
                ptr[i] = other.ptr[i]; //копіюємо значення з іншого вектора
        }
    }

    //оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this != &other) { //перевірка на самоприсвоєння
            delete[] ptr; //видаляємо стару пам'ять
            ptr = new float[other.size]; //виділяємо нову пам'ять
            size = other.size;
            state = other.state;
            if (!ptr)
                state = -1; // Помилка: не вистачає пам'яті
            else {
                for (int i = 0; i < size; ++i)
                    ptr[i] = other.ptr[i]; // Копіюємо значення з іншого вектора
            }
        }
        return *this;
    }

    //деструктор, який відповідає за вивільнення пам'яті, яка була виділена для масиву ptr
    ~Vector() {
        delete[] ptr;
    }

    //функції для отримання та встановлення елементів
    float& at(int index) {
        if (index >= 0 && index < size)
            return ptr[index];
        state = -2; //помилка: вихід за межі масиву
        return ptr[0]; //повертаємо перший елемент
    }

    //функції для арифметичних операцій
    Vector add(const Vector& other) const {
        if (size != other.size) {
            state = -3; //помилка: неподібні розміри векторів
            return Vector(); //повертаємо порожній вектор
        }
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] + other.ptr[i];
        return result;
    }

    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            state = -3; //помилка: неподібні розміри векторів
            return Vector(); //повертаємо порожній вектор
        }
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] - other.ptr[i];
        return result;
    }

    //множення на ціло
    Vector multiply(long value) const {
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] * value;
        return result;
    }

    //функції порівняння
    bool greaterThan(const Vector& other) const {
        if (size != other.size)
            return false; //вектори не можна порівнювати, якщо розміри відмінні
        for (int i = 0; i < size; ++i) {
            if (ptr[i] <= other.ptr[i])
                return false; //хоча б один елемент менше або рівний
        }
        return true;
    }

    bool lessThan(const Vector& other) const {
        if (size != other.size)
            return false; //вектори не можна порівнювати, якщо розміри відмінні
        for (int i = 0; i < size; ++i) {
            if (ptr[i] >= other.ptr[i])
                return false; //хоча б один елемент більше або рівний
        }
        return true;
    }

    bool equalTo(const Vector& other) const {
        if (size != other.size)
            return false; //вектори не можна порівнювати, якщо розміри відмінні
        for (int i = 0; i < size; ++i) {
            if (ptr[i] != other.ptr[i])
                return false; //хоча б один елемент відмінний
        }
        return true;
    }

    //функція друку
    void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << ptr[i] << " ";
        std::cout << std::endl;
    }

    //функція для отримання стану
    int getState() const {
        return state;
    }

    //статична функція для підрахунку числа об'єктів даного типу
    static int getCount() {
        //локальна статична змінна для збереження числа об'єктів
        static int count = 0;
        return count;
    }
};

int main() {
    // Приклад тестування
    Vector v1; // Конструктор за замовчуванням
    v1.print(); 

    Vector v2(5); // Конструктор з одним параметром
    v2.print(); 

    Vector v3(3, 2.5); // Конструктор із двома параметрами
    v3.print();
    Vector v4 = v3; // Конструктор копіювання
    v4.print();

    Vector v5;
    v5 = v3; // Оператор присвоєння
    v5.print();

    Vector v6(2);
    v6.at(0) = 1.5; // Встановлюємо значення для елементу за індексом 0
    std::cout << v6.at(0) << std::endl; // Виведе: 1.5

    Vector v7(2);
    v7.at(2) = 2.0; // Вихід за межі масиву
    std::cout << "State: " << v7.getState() << std::endl; //-2 (помилка)

    Vector v8(3), v9(3);
    v8.at(0) = 1.0;
    v9.at(0) = 2.0;
    Vector v10 = v8.add(v9); // Додавання
    v10.print(); //3 0 0

    Vector v11(3), v12(3);
    v11.at(0) = 5.0;
    v12.at(0) = 2.0;
    Vector v13 = v11.subtract(v12); // Віднімання
    v13.print(); //3 0 0

    Vector v14(3);
    v14.at(0) = 2.0;
    Vector v15 = v14.multiply(3); // Множення на ціле число
    v15.print(); //6 0 0

    Vector v16(3), v17(3);
    v16.at(0) = 2.0;
    v17.at(0) = 1.0;
    std::cout << v16.greaterThan(v17) << std::endl; // 1 (true)

    std::cout << Vector::getCount() << std::endl; //17 (кількість об'єктів Vector)

    return 0;
}
