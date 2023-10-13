#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <functional>
using namespace std;

auto baseSalaryForPosition = [](const string& position){
	int baseSalary;
	if(position == "Tester") baseSalary = 1500;
	if(position == "Analyst") baseSalary = 1600;
	if(position == "Developer") baseSalary = 2000;
	if(position == "Team Leader") baseSalary = 3000;
	if(position == "Manager") baseSalary = 4000;
	return baseSalary;
};

auto factorForSeniority = [](const string& seniority_level){
    double factor;
    if(seniority_level == "Entry") factor = 1;
    if(seniority_level == "Junior") factor = 1.2;
    if(seniority_level == "Senior") factor = 1.5;
    return factor;
};

auto factorForContinuity = [](const string& years_worked_continuously){
    double continuityFactor;
    int continuity = stoi(years_worked_continuously);
    if(continuity < 3) continuityFactor = 1;
    if(continuity >= 3 && continuity < 5) continuityFactor = 1.2;
    if(continuity >= 5 && continuity < 10) continuityFactor = 1.5;
    if(continuity >=10 && continuity <= 20) continuityFactor = 1.7;
    if(continuity > 20) continuityFactor = 2;
    return continuityFactor;
};

auto bonusLevel = [](const string& special_bonus_level){
    return stoi(special_bonus_level);
};

auto computeSalary = [](auto baseSalaryForPosition, auto factorForSeniority, auto factorForContinuity, auto bonusLevel){
		int baseSalary = baseSalaryForPosition();
		double factor = factorForSeniority();
		double continuityFactor = factorForContinuity();
		int specialBonusLevel = bonusLevel();
		double specialBonusFactor = specialBonusLevel * 0.03;
		double currentSalary = baseSalary * factor * continuityFactor;
		double salary = currentSalary + specialBonusFactor * currentSalary;
		int roundedSalary = ceil(salary);
		return roundedSalary;
};

int main(){
    string id;
    string employee_id;
    string first_name;
    string last_name;
    string seniority_level;
    string position;
    string years_worked_continuously;
    string special_bonus_level;

    ifstream employeesFile("./Employees.csv");
    while (getline(employeesFile, id, ',')) {
        getline(employeesFile, employee_id, ',') ;
        getline(employeesFile, first_name, ',') ;
        getline(employeesFile, last_name, ',') ;
        getline(employeesFile, seniority_level, ',') ;
        getline(employeesFile, position, ',') ;
        getline(employeesFile, years_worked_continuously, ',') ;
        getline(employeesFile, special_bonus_level);
        if(id == "id") continue;

        auto roundedSalary = computeSalary( 
        		bind(baseSalaryForPosition, position),
        		bind(factorForSeniority, seniority_level),
						bind(factorForContinuity, years_worked_continuously),
						bind(bonusLevel, special_bonus_level)
				);

        cout  << seniority_level << " " << position << " " << first_name << " " << last_name << " (" 
        << years_worked_continuously << "yrs)" <<  ", " << employee_id << ", has salary (bonus level  " 
        << special_bonus_level << ") " << roundedSalary << endl;
    }
}