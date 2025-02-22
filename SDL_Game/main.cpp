#include "Game.h"

class NhanVien {
private:
	std::string ten;
	int age;
	std::string address;
	double salary;
	int hours;
public:
	NhanVien() {}
	NhanVien(std::string _ten, int _age, std::string _address, double _salary, int _hours) {
		ten = _ten;
		age = _age;
		address = _address;
		salary = _salary;
		hours = _hours;
	}

	std::string toString() {
		std::string str = ten + " " + std::to_string(age) + " " + address + " " + std::to_string(salary) + " " + std::to_string(hours);
		return str;
	}

	double tinhThuong() {
		double bonus = 0;
		if (hours >= 200) bonus = salary * 0.2;
		if (hours < 200 and hours >= 100) bonus = salary * 0.1;

		return bonus;
	}
};

int main(int argc, char* args[])
{
	Game game = Game();
	game.Run();
	
	

	return 0;
}