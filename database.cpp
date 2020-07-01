//============================================================================
// Name        : database.cpp
// Author      : ArlenMor
// Version     : 0.2
// Description : Database. The database stores pairs of the form: date - event
// Description : We define the date as a string of the form Year-Month-Day, where Year, Month and Day are integers.
// Operation   : 1. Add event								: 	Add date event
// Operation   : 2. Delete event							:	Del date event
// Operation   : 3. Delete all events for a specific date	:	Del date
// Operation   : 4. Search for events for a specific date	:	Find date
// Operation   : 5. Print all events for all dates			:	Print
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Date{
public:
	Date()
	{
		year = 0;
		month = 1;
		day = 1;
	}
	Date(int new_year, int new_month, int new_day)
	{
		//check date
		year = new_year;
		month = new_month;
		day = new_day;
	}
	int get_year() const;
	int get_month() const;
	int get_day() const;
private:
	int year;
	int month;
	int day;
};

int Date::get_year() const
{
	return year;
}

int Date::get_month() const
{
	if(month <= 0 && month > 12)
		return -1; //handle the error
	return month;
}

int Date::get_day() const
{
	if(day <= 0 && day > 31)
		return -1; //handle the error
	return day;
}

bool operator < (const Date& lhs, const Date& rhs)
{
	if(lhs.get_year() == rhs.get_year())
	{
		if(lhs.get_month() == rhs.get_month())
			return lhs.get_day() < rhs.get_day();
		else
			return lhs.get_month() < rhs.get_month();
	}
	return lhs.get_year() < rhs.get_year();
}

bool operator == (const Date& lhs, const Date& rhs)
{
	return (lhs.get_year() == rhs.get_year() &&
			lhs.get_month() == rhs.get_month() &&
			lhs.get_day() == rhs.get_day());
}

ostream& operator << (ostream& stream, const Date& date)
{
	return stream << date.get_year() << "-" << date.get_month() << "-" << date.get_day();
}

class Database {
public:
	void add_event (const Date& date, const string& event);
	bool delete_event (const Date& date, const string& event);
	int delete_date (const Date& date);
	vector<string> Find (const Date& date) const;

	void print_database();
private:
	map<Date, vector<string>> date_events;
};

void Database::add_event(const Date& date, const string& event)
{
	date_events[date].push_back(event);
}

bool Database::delete_event(const Date& date, const string& event)
{
	//rewrite, rework!!!!!!
	for(auto it_map = date_events.begin(); it_map != date_events.end(); ++it_map)
	{
		if((*it_map).first == date)
		{
			for(auto it_v = (*it_map).second.begin(); it_v != (*it_map).second.end(); ++it_v)
			{
				if((*it_v) == event)
				{
					(*it_map).second.erase(it_v);
					return true;
				}
			}
		}
	}
	return false;
}

int Database::delete_date(const Date& date)
{
	//add check
	int count_event = date_events[date].size();
	date_events.erase(date);
	return count_event;
}

void Database::print_database()
{
	for(const auto& item : date_events)
	{
		cout << "Date: " << item.first << " Events: ";
		for(const auto& event : item.second)
		{
			cout << event << " ";
		}
		cout << endl;
	}
}

int main() {
	Database database;
	string command;
	while (getline(cin, command)) {
		if(command == "Add")
		{
			cout << "I here" << endl;
			int year, month, day;
			cin >> year; cin.ignore(1);
			cin >> month; cin.ignore(1);
			cin >> day;
			string event;
			cin >> event;
			Date date = {year, month, day};
			database.add_event(date, event);
			database.print_database();
		}else if (command == "Del")
		{

		}
	}
	return 0;
}
