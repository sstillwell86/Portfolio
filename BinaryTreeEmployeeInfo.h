#pragma once
#include <string>

class EmployeeInfo
{
private:
	int EmployeeId;
	std::string EmployeeName;
public:
	EmployeeInfo();
	EmployeeInfo(int employeeId, std::string employeeName);
	~EmployeeInfo();

	// Accessors and Mutators
	int getEmployeeId();
	std::string getEmployeeName();
	void setEmployeeId(int);
	void setEmployeeName(std::string);

	// operators
	bool operator > (const EmployeeInfo &);
	bool operator < (const EmployeeInfo &);
	bool operator == (const EmployeeInfo &);
	friend std::ostream &operator << (std::ostream &, const EmployeeInfo &);
};