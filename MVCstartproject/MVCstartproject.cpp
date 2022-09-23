// MVCstartproject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


// Связующие элементы
class Observer
{
public:
    virtual void update() = 0;
};

class Observable
{
public:
    void addObserver(Observer* observer)
    {
        _observers.push_back(observer);
    }
    void notifyUpdate()
    {
        int size = _observers.size();
        for (int i = 0; i < size; i++)
        {
            _observers[i]->update();
        }
    }
private:
    std::vector<Observer*> _observers;
};

// Модель
class TemperatureModel : public Observable
{
public:
    float getF()
    {
        return _temperatureF;
    }
    float getC()
    {
        return (_temperatureF - 32.0) * 5.0 / 9.0;
    }
    void setF(float tempF)
    {
        _temperatureF = tempF;
        notifyUpdate();
    }
    void setC(float tempC)
    {
        _temperatureF = tempC * 9.0 / 5.0 + 32.0;
        notifyUpdate();
    }
private:
    float _temperatureF;
};

// Вьюшка
class ConsoleView : public Observer
{
public:
    ConsoleView(TemperatureModel* model)
    {
        _model = model;
        _model->addObserver(this);
    }
    virtual void update()
    {
        system("cls");
        printf("Temperature in Celsius: %.2f\n", _model->getC());
        printf("Temperature in Farenheit: %.2f\n", _model->getF());
        printf("Input temperature in Celsius: ");
    }
private:
    TemperatureModel* _model;
};

// Контроллер
class Controller
{
public:
    Controller(TemperatureModel* model)
    {
        _model = model;
    }
    void start()
    {
        _model->setC(0);

        float temp;
        do
        {
            scanf_s("%f", &temp);
            _model->setC(temp);
        } while (temp != 0);
    }
private:
    TemperatureModel* _model;
};

int main()
{
    TemperatureModel model;
    ConsoleView view(&model);
    Controller controller(&model);
    controller.start();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
