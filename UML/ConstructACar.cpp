#include<iostream>
#include<conio.h>
#include<thread>
using namespace std;

#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 100

class Tank
{
	const int VOLUME;		//характеристика бака
	double fuel_level;		// состояние бака
public:
	int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(int fuel)
	{
		if (fuel < 0)return;
		if (fuel_level + fuel > VOLUME)fuel_level = VOLUME;
		else fuel_level += fuel;
	}

	Tank(int volume) :VOLUME(
		volume<MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
		volume>MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
		volume), fuel_level(0)
	{
		//if (volume >= 20 && volume <= 100)this->VOLUME = volume;
		//this->fuel_level = 0;
		cout << "Tank ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	void info()const
	{
		cout << "Tank volume:\t" << get_VOLUME() << "liters.\n";
		cout << "Tank level:\t" << get_fuel_level() << "liters.\n";
	}
};

#define MIN_ENGINE_CUNSUMPTION 3
#define MAX_ENGINE_CUNSUMPTION 25

class Engine
{
	int consumption;				//расход топлива на 100км
	double consumption_per_second;		// расход топлива за 1 сек. на холостом ходу
	bool is_started;
public:
	int get_consumption()const
	{
		return consumption;
	}

	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}

	Engine(int consumption) :consumption(
		consumption<MIN_ENGINE_CUNSUMPTION ? MIN_ENGINE_CUNSUMPTION :
		consumption>MAX_ENGINE_CUNSUMPTION ? MAX_ENGINE_CUNSUMPTION :
		consumption
	)
	{
		consumption_per_second = consumption * 3e-5;
		is_started = false;
		cout << "Engine ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
	void info()const
	{
		cout << "Consumption per 100 km:\t" << consumption << "liters.\n";
		cout << "Consumption per second:\t" << consumption_per_second << "liters.\n";

	}

	void stop()
	{
		is_started = false;
	}

	void start()
	{
		is_started = true;
	}

};

#define max_spide_low_limit 50
#define max_spide_high_limit 400

#define Enter 13
#define Esc	27

class Car
{
	Engine engine;
	Tank tank;
	int speed;
	bool driver_inside = false;
	const int MAX_SPEED;
	struct
	{
		std::thread panel_thread;
	}threads;

public:
	Car(int engine_consuption, int tank_volume, int max_speed):
		engine(engine_consuption),
		tank(tank_volume),
		MAX_SPEED(
		max_speed<max_spide_low_limit?max_spide_low_limit:
		max_speed>max_spide_high_limit?max_spide_high_limit:
		max_speed)
	{
		speed = 0;
		driver_inside = false;
		cout << "Your car is ready" << endl;
	}

	~Car()
	{
		cout<<"Your car is over" << endl;;
	}

	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Speed: \t" << speed << "km/hour.\n";
			cout << "Fuel level: \t" << tank.get_fuel_level() << "liters.\n";
			std::this_thread::sleep_for(1s);
		}

	}

	void get_in()
	{
		driver_inside = true;
		threads.panel_thread = std::thread(&Car::panel, this);
	}

	void get_out()
	{
		driver_inside = false;
		if (threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "You are out of your car" << endl;
	}

	void control()
	{
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				if (driver_inside)get_out();
				else get_in();
				break;

			case 'F':case 'f':
				if (driver_inside)
				{
					cout << "Для начала выйдете из машины" << endl;
					break;
				}
				double fuel;
				cout << "Введите объем топлива: "; cin >> fuel;
				tank.fill(fuel);
				break;

			case 'I':case'i':	//ignition


				break;

			case Esc:get_out();

			}
		} while (key != Esc);
	}

	void info()const
	{
	
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK


void main()
{
	setlocale(LC_ALL, "");

#ifdef TANK_CHECK

		Tank tank(40);
		tank.info();
		int fuel;
		do
		{
			cout << "Введите уровень топлива: "; cin >> fuel;
			tank.fill(fuel);
			tank.info();

		} while (fuel);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
		Engine engine(10);
		engine.info();
#endif // ENGINE_CHECK

	Car mustang(10, 80, 250);
	mustang.control();

}
