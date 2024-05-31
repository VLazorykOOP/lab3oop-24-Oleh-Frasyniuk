#include <iostream>
#include <iomanip> // Для std::setw

class Time {
private:
    int hour;
    int minute;
    int second;

public:
    //конструктор за замовчуванням
    Time() : hour(0), minute(0), second(0) {}

    //конструктор з параметрами
    Time(int h, int m, int s) {
        setHour(h);
        setMinute(m);
        setSecond(s);
    }

    //функції-члени встановлення години, хвилини та секунди
    void setHour(int h) {
        if (h >= 0 && h <= 23)
            hour = h;
    }

    void setMinute(int m) {
        if (m >= 0 && m <= 59)
            minute = m;
    }

    void setSecond(int s) {
        if (s >= 0 && s <= 59)
            second = s;
    }

    //функції-члени одержання години, хвилини та секунди
    int getHour() const {
        return hour;
    }

    int getMinute() const {
        return minute;
    }

    int getSecond() const {
        return second;
    }

    //функції-члени друку
    void printStandard() const {
        std::cout << std::setw(2) << std::setfill('0') << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":" << std::setw(2) << std::setfill('0') << minute << ":" << std::setw(2) << std::setfill('0') << second << ((hour < 12) ? " a.m." : " p.m.") << std::endl;
    }
    //serw - вирівнення цифр пробілами, setfill - заповнення пропусків тим що в дужках

    void printAlternative() const {
        std::cout << hour << " h " << minute << " m " << second << " s" << std::endl; //endl - \n
    }
};

int main() {
    
    Time t1; //конструктор за замовчуванням
    Time t2(16, 18, 3); //конструктор з параметрами

    //встановлення значень годин, хвилин та секунд
    t1.setHour(9);
    t1.setMinute(45);
    t1.setSecond(30);

    //виведення значень годин, хвилин та секунд
    std::cout << "time t1: " << t1.getHour() << " h " << t1.getMinute() << " m " << t1.getSecond() << " s" << std::endl;
    std::cout << "time t2: " << t2.getHour() << " h " << t2.getMinute() << " m " << t2.getSecond() << " s" << std::endl;

    //виведення за шаблоном
    std::cout << "template:" << std::endl;
    t1.printStandard();
    t2.printStandard();
    t1.printAlternative();
    t2.printAlternative();

    return 0;
}
