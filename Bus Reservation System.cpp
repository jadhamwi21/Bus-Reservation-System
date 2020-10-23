#include <algorithm>
#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
void Differentiation()
{
	cout << "--------------------------------" << endl;
}
//A Structure For The Buses That's Gonna Be Installed to The Bus System
struct Resturaunt
{
	string Name;
	string Location;
	std::map<string, string> Menu;
};
struct Bus
{
	long BusNo;
	string Drivername;
	string ArrivalTime;
	string DepartureTime;
	std::vector<Resturaunt> Resturaunts;
	string Destination;
	string Seats[32];
};
//Class For Bus_System Including Function To Represent GUI into the User
class Bus_System
{
private:
	//Vector For Storing Buses for a certain Bus_System(ex: Bus_System BTest)
	std::vector<Bus> Buses;

public:
	//Here I Did Make A Function To Make The Bus System Interface Shows Up On The Screen And Ask
	//The User For Inputing An Option(1 -> 5)
	void
		Bus_System_run()
	{
		while (true)
		{
			cout << "1.Install Bus" << endl;
			cout << "2.Reservation" << endl;
			cout << "3.Show Reservation Infos" << endl;
			cout << "4.Buses Available" << endl;
			cout << "5.Exit" << endl;
			cout << "Enter Your Choice Sir : ";
			int n;
			//User's Choice
			cin >> n;
			system("cls");
			//This Switch Is Written To Apply The Function That Makes The Purpose Of The User
			switch (n)
			{
			case 1:
				InstallBusInformation();
				Differentiation();
				break;
			case 2:
				Reservation();
				Differentiation();
				break;
			case 3:
				showReservationInfos();
				Differentiation();
				break;
			case 4:
				ShowAvailableBuses();
				Differentiation();
				break;
			case 5:
				cout << "Program Terminated" << endl;
				exit(1);
			default:
				cout << "Error With The Input" << endl;
				break;
			}
		}
	}
	//Start Of BusInstallation
	void InstallBusInformation()
	{
		Bus Temp;
		cout << "Bus Number : ";
		cin >> Temp.BusNo;
		while (std::find_if(Buses.begin(), Buses.end(), [=](Bus temp) {
			return Temp.BusNo == temp.BusNo;
			}) != Buses.end())
		{
			cout << "Sorry , Please Enter An Unused Bus Number" << endl;
			cin >> Temp.BusNo;
		}
			cout << "Driver's Name : ";
			cin >> Temp.Drivername;
			cout << "Arrival Time : ";
			cin >> Temp.ArrivalTime;
			cout << "Departure Time : ";
			cin >> Temp.DepartureTime;
			cout << "From : ";
			cin >> Temp.Destination;
			string s;
			cout << "To : ";
			cin >> s;
			Temp.Destination += " " + s;
			std::fill_n(Temp.Seats, 32, "Empty");
			Buses.push_back(Temp);
	}
	//End Of BusInstallation
	//Start Of Reservation
	void Reservation()
	{
		if (Buses.empty())
		{
			cout << "No Installed Buses Yet" << endl;
			return;
		}
		long BusNumber;
		while (true)
		{
			if (Buses.empty())
			{
				cout << "No Installed Buses Yet" << endl;
				break;
			}
			bool flag = false;
			cout << "Enter Bus Number : ";
			cin >> BusNumber;
			std::vector<Bus>::iterator it = Buses.begin();
			for (it; it != Buses.end(); it++)
			{
				if (it->BusNo == BusNumber)
				{
					flag = true;
					int BusSeat;
					while (true)
					{
						cout << "Enter Seats Number : ";
						cin >> BusSeat;
						if (BusSeat <= 0 || BusSeat > 32)
						{
							cout << "Enter A Valid Number Please ! " << endl;
							continue;
						}
						else if (it->Seats[BusSeat - 1] != "Empty")
						{
							cout << "It's Reserved by " + it->Seats[BusSeat - 1] << endl;
							continue;
						}
						else
						{
							string name;
							cout << "Enter Your Name : ";
							cin.ignore();
							getline(cin, name);
							it->Seats[BusSeat - 1] = name;
							break;
						}
					}
				}
			}
			if (flag == false)
			{
				cout << "Wrong Number" << endl;
			}
			else
			{
				break;
			}
		}
	};
	//End Of Reservation
	void showReservationInfos()
	{
		if (Buses.empty())
		{
			cout << "No Installed Buses Yet" << endl;
		}
		cout << "Enter Bus Number : ";
		long BusNumber;
		cin >> BusNumber;
		std::vector<Bus>::iterator it = Buses.begin();
		bool flag = false;
		for (it; it != Buses.end(); it++)
		{
			if (it->BusNo == BusNumber)
			{
				flag = true;

				cout << "Bus Number : " << it->BusNo << " | ";
				cout << "Driver : " << it->Drivername << endl;
				cout << "Arrival Time : " << it->ArrivalTime << " | ";
				cout << "Deprature Time : " << it->DepartureTime << endl;
				string From = it->Destination.substr(0, it->Destination.find(" "));
				cout << "From : " << From << " || ";
				string To = it->Destination.substr(it->Destination.rfind(" ")+1);
				cout << "To : " << To << endl;

				int count = 0;
				std::map<int, string> Connections;
				for (int i = 0; i < 32; i++)
				{
					if (it->Seats[i] == "Empty")
					{
						count++;
					}
					else
					{
						Connections.insert(pair<int, string>(i + 1, it->Seats[i]));
					}
					cout << setw(5) << to_string(i + 1) << ".  " << setw(9) << it->Seats[i];
					if ((i + 1) % 4 == 0)
					{
						cout << endl;
					}
				}
				cout << endl;
				cout << "There Are " + to_string(count) + " Seats Remaining Empty " << endl;
				std::map<int, string>::iterator it = Connections.begin();
				for (it; it != Connections.end(); it++)
				{
					cout << "The Seat Number " + to_string(it->first) + " Is Reserved For " + it->second << endl;
				}
			}
		}
		if (flag == false)
		{
			cout << "Number Isn't Right Please Try Again" << endl;
			showReservationInfos();
		}
	}
	void ShowAvailableBuses()
	{
		std::vector<Bus>::iterator it = Buses.begin();
		for (it; it != Buses.end(); it++)
		{
			cout << "Bus Number : " << it->BusNo << " | ";
			cout << "Driver : " << it->Drivername << endl;
			cout << "Arrival Time : " << it->ArrivalTime << " | ";
			cout << "Deprature Time : " << it->DepartureTime << endl;
			string From = it->Destination.substr(0, it->Destination.find(" "));
			cout << "From : " << From << " || ";
			string To = it->Destination.substr(it->Destination.rfind(" ")+1);
			cout << "To : " << To << endl;
		}
	}
};
int main()
{
	Bus_System Test;
	Test.Bus_System_run();
	return 0;
}
