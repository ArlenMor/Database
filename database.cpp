//============================================================================
// Name        : database.cpp
// Author      : ArlenMor
// Version     : 1.0 release
// Description : Database. The database stores pairs of the form: date - event
// Description : We define the date as a string of the form Year-Month-Day, where Year, Month and Day are integers.
// Operation   : 1. Add event					: 	Add date event
// Operation   : 2. Delete event				:	Del date event
// Operation   : 3. Delete all events for a specific date	:	Del date
// Operation   : 4. Search for events for a specific date	:	Find date
// Operation   : 5. Print all events for all dates		:	Print
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <stdexcept>
#include <sstream>
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
		year = new_year;
		if(new_month > 12 || new_month < 1)
			throw logic_error("Month value is invalid: " + to_string(new_month));
		month = new_month;
		if(new_day > 31 || new_day < 1)
			throw logic_error("Day value is invalid: " + to_string(new_day));
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
	return month;
}

int Date::get_day() const
{
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

ostream& operator << (ostream& stream, const Date& date)
{
	return stream << setw(4) << setfill('0') << date.get_year() <<
			"-" << setw(2) << setfill('0') << date.get_month() <<
			"-" << setw(2) << setfill('0') << date.get_day();
}

class Database {
public:
	void add_event (const Date& date, const string& event);
	bool delete_event (const Date& date, const string& event);
	int delete_date (const Date& date);
	set<string> find (const Date& date) const;

	void print() const;
private:
	map<Date, set<string>> storage;
};

void Database::add_event(const Date& date, const string& event)
{
	storage[date].insert(event);
}

bool Database::delete_event(const Date& date, const string& event)
{
	if(storage.count(date) > 0 && storage[date].count(event) > 0)
	{
		storage[date].erase(event);
		return true;
	}
	return false;
}

int Database::delete_date(const Date& date)
{
	if(storage.count(date) == 0)
		return 0;
	else{
		int count_event = storage[date].size();
		storage.erase(date);
		return count_event;
	}
}

set<string> Database::find(const Date& date) const
{
	if(storage.count(date) > 0)
		return storage.at(date);
	else
		return {};
}

void Database::print() const
{
	for(const auto& item : storage)
	{
		for(const auto& event : item.second)
		{
			cout << item.first << " " << event << endl;
		}
	}
}

Date parse_date(const string& date)
{
	stringstream date_stream(date);
	int year;
	date_stream >> year;
	if(date_stream.peek() != '-')
		throw logic_error ("Wrong date format: " + date);
	date_stream.ignore();

	if(date_stream.peek() == EOF)
		throw logic_error("Wrong date format: " + date);

	int month;
	date_stream >> month;
	if(date_stream.peek() != '-')
		throw logic_error("Wrong date format: " + date);
	date_stream.ignore();

	if(date_stream.peek() == EOF)
		throw logic_error("Wrong date format: " + date);

	int day;
	date_stream >> day;
	if(!date_stream.eof())
		throw logic_error("Wrong date format: " + date);

	return Date(year, month, day);
}

int main() {
	try{
		Database database;
		string command_line;
		while (getline(cin, command_line)) {
			stringstream ss(command_line);
			string command;
			ss >> command;
			if(command == "Add")
			{
				string date_str, event;
				ss >> date_str >> event;
				Date date = parse_date(date_str);
				database.add_event(date, event);
			}else if(command == "Del")
			{
				string date_str;
				ss >> date_str;
				string event;
				if(!ss.eof())
					ss >> event;
				Date date = parse_date(date_str);
				if(event.empty())
				{
					const int count = database.delete_date(date);
					cout << "Deleted " << count << " events" << endl;
				}else{
					if(database.delete_event(date, event))
					{
						cout << "Deleted successfully" << endl;
					}else{
						cout << "Event not found" << endl;
					}
				}
			}else if(command == "Find")
			{
				string date_str;
				ss >> date_str;
				Date date = parse_date(date_str);
				for(const string& event : database.find(date))
				{
					cout << event << endl;
				}
			}else if (command == "Print")
			{
				database.print();
			}else if (command.empty())
				continue;
			else
				throw logic_error("Unknown command: " + command);
		}
	}catch (exception& ex){
		cout << ex.what() << endl;
	}

	return 0;
}
