
#include "state.h"
#include <iomanip>  //need to use formatting manipulators
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

state_class::state_class()
{
	count = 0;
	capacity = 5;
	pop_DB = new population_record[capacity];
	ifstream in;
	in.open("census2020_data.txt");
	while (!in.eof()) {
		if (Is_Full() == true) {
			double_size();
		}
		int space_loc;
		string s;
		getline(in, s);
		for (int i = s.length(); i >= 0; i--) {
			if (s[i] == ' ') {
				space_loc = i;
				break;
			}
		}
		pop_DB[count].state_name = s.substr(0, space_loc);
		pop_DB[count].population = stod(s.substr(space_loc+1, s.length() - space_loc));
		count++;
	}
	in.close();
	return;
}

state_class::state_class(const state_class & org)
{
	count = org.count;
	capacity = org.capacity;
	pop_DB = new population_record[capacity];
	for (int i = 0; i < count; i++) {
		pop_DB[i] = org.pop_DB[i];
	}
	return;
}

state_class::~state_class()
{
	count = 0;
	capacity = 1;
	delete[] pop_DB;
}

void state_class::double_size()
{
	capacity *= 2;
	population_record* temp = new population_record[capacity];
	for (int i = 0; i < count; i++) {
		temp[i] = pop_DB[i];
	}
	delete[]pop_DB;
	pop_DB = temp;
}

void state_class::operator+(const population_record& r)
{
	if (Is_Full() == true) {
		double_size();
	}
	pop_DB[count].state_name = r.state_name;
	pop_DB[count].population = r.population;
	count++;
}

int state_class::Search(const string& state)
{
	for (int i = 0; i < count; i++) {
		if (pop_DB[i].state_name == state) {
			return i;
		}
	}
	return -1;
}

void state_class::Remove(const string& state)
{
	int loc = Search(state);
	if (loc != -1) {
		for (int i = loc; i < count - 1; i++) {
			pop_DB[i] = pop_DB[i + 1];
		}
	}
	count--;
}

void state_class::Print_ALL_To_File(const string& datafile)
{
	ofstream filename;
	filename.open(datafile);
	filename.setf(ios::fixed);
	filename.precision(0);
	for (int i = 0; i < count; i++) {
		filename << pop_DB[i].state_name;
		filename << " ";
		filename << pop_DB[i].population;
		filename << endl;
	}
	filename.close();
}

void state_class::Print_ALL()
{
	for (int i = 0; i < count; i++) {
		cout << pop_DB[i].state_name << " " << pop_DB[i].population << endl;
	}
}

void state_class::Print_Range(const int min, const int max)
{
	for (int i = 0; i < count; i++) {
		if (pop_DB[i].population >= min && pop_DB[i].population <= max)
			cout << pop_DB[i].state_name << " " << pop_DB[i].population << endl;
	}
}

int state_class::State_Count(const int min, const int max)
{
	int num_of_states = 0;
	for (int i = 0; i < count; i++) {
		if (pop_DB[i].population >= min && pop_DB[i].population <= max)
			num_of_states++;
	}
	return num_of_states;
}

void state_class::Sort()
{
	for (int i = 0; i < count; i++) {
		int j = i;
		for (int c = i + 1; c < count; c++) {
			if (pop_DB[c].state_name < pop_DB[j].state_name) {
				j = c;
			}
		}
		swap(pop_DB[i].state_name, pop_DB[j].state_name);
	}
}
