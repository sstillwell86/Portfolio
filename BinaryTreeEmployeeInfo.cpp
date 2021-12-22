#include "BinaryTreeEmployeeInfo.h"

EmployeeInfo::EmployeeInfo()
{
}

EmployeeInfo::EmployeeInfo(int employeeId, std::string employeeName)
{
	this->EmployeeId = employeeId;
	this->EmployeeName = employeeName;
}

EmployeeInfo::~EmployeeInfo()
{
}

int EmployeeInfo::getEmployeeId()
{
	return EmployeeId;
}

std::string EmployeeInfo::getEmployeeName()
{
	return EmployeeName;
}

void EmployeeInfo::setEmployeeId(int EmployeeId)
{
	this->EmployeeId = EmployeeId;
}

void EmployeeInfo::setEmployeeName(std::string EmployeeName)
{
	this->EmployeeName = EmployeeName;
}

bool EmployeeInfo::operator>(const EmployeeInfo &right)
{
	bool status;
	if (EmployeeId > right.EmployeeId)
		status = true;
	else
		status = false;

	return status;
}

bool EmployeeInfo::operator<(const EmployeeInfo &right)
{
	bool status;
	if (EmployeeId < right.EmployeeId)
		status = true;
	else
		status = false;
	return status;
}

bool EmployeeInfo::operator==(const EmployeeInfo &right)
{
	bool status;
	if (EmployeeId == right.EmployeeId)
		status = true;
	else
		status = false;
	return status;
}

std::ostream &operator << (std::ostream &strm, const EmployeeInfo &obj)
{
	strm << obj.EmployeeName << std::endl;

	return strm;
}