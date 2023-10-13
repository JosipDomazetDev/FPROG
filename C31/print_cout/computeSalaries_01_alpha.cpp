#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
struct Employee {
  string id;
  string employee_id;
  string first_name;
  string last_name;
  string seniority_level;
  string position;
  string years_worked_continuously;
  string special_bonus_level;
};

void printEmployee (const Employee & employee, ostream & stream, int roundedSalary)
{
  stream << employee.seniority_level << employee.position << " " << employee.first_name 
  << " " << employee.last_name << " (" << employee.years_worked_continuously << "yrs)" 
  << "," << employee.employee_id << ", has salary (bonus level " << employee.special_bonus_level << ") " 
  << roundedSalary << endl;
}

int
main ()
{
  Employee employee;

  ifstream employeesFile ("./Employees.csv");
  while (getline (employeesFile, employee.id, ','))
    {
      getline (employeesFile, employee.employee_id, ',');
      getline (employeesFile, employee.first_name, ',');
      getline (employeesFile, employee.last_name, ',');
      getline (employeesFile, employee.seniority_level, ',');
      getline (employeesFile, employee.position, ',');
      getline (employeesFile, employee.years_worked_continuously, ',');
      getline (employeesFile, employee.special_bonus_level);
      if (employee.id == "id")
	continue;

      int baseSalary;
      if (employee.position == "Tester") baseSalary = 1500;
      if (employee.position == "Analyst") baseSalary = 1600;
      if (employee.position == "Developer") baseSalary = 2000;
      if (employee.position == "Team Leader") baseSalary = 3000;
      if (employee.position == "Manager")	baseSalary = 4000;

      double factor;
      if (employee.seniority_level == "Entry")
				factor = 1;
      if (employee.seniority_level == "Junior")
				factor = 1.2;
      if (employee.seniority_level == "Senior")
				factor = 1.5;

      double continuityFactor;
      int continuity = stoi (employee.years_worked_continuously);
      if (continuity < 3)
				continuityFactor = 1;
      if (continuity >= 3 && continuity < 5)
				continuityFactor = 1.2;
      if (continuity >= 5 && continuity < 10)
				continuityFactor = 1.5;
      if (continuity >= 10 && continuity <= 20)
				continuityFactor = 1.7;
      if (continuity > 20)
				continuityFactor = 2;

      int specialBonusLevel = stoi (employee.special_bonus_level);
      double specialBonusFactor = specialBonusLevel * 0.03;

      double currentSalary = baseSalary * factor * continuityFactor;
      double salary = currentSalary + specialBonusFactor * currentSalary;

      int roundedSalary = ceil (salary);

      printEmployee (employee, cout, roundedSalary);
    }
}
