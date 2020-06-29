//============================================================================
// Name        : database.cpp
// Author      : ArlenMor
// Version     : 0.1
// Copyright   : Your copyright notice
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
	//write constructor
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

class Database {
public:
	void add_event (const Date& date, const string& event);
	bool delete_event (const Date& date, const string& event);
	int delete_date (const Date& date);
	vector<string> Find (const Date& date) const;
private:
	map<Date, vector<string>> date_events;
};

void Database::add_event(const Date& date, const string& event)
{
	date_events[date].push_back(event);
}

bool Database::delete_event(const Date& date, const string& event)
{
	for(auto it_map = date_events.begin(); it_map != date_events.end(); ++it_map) //rewrite, rework
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

int main() {
	return 0;
}
