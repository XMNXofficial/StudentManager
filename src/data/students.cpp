#include"data/students.hpp"
#include<iostream>
#include<vector>
namespace students {


	//添加学生信息
	void StudentInformation::addStudent(std::string name, std::string school_id, std::string school_grade, std::string school_major, std::string school_class) {
		student s;
		s.name = name;
		s.school_id = school_id;
		s.school_grade = school_grade;
		s.school_major = school_major;
		s.school_class = school_class;
		students.push_back(s);
	}

	//修改学生信息
	void StudentInformation::modifyStudent(std::string school_id, std::string name, std::string school_grade, std::string school_major, std::string school_class) {
		int index = findStudent(school_id);
		if (index >= 0) {
			students[index].name = name;
			students[index].school_grade = school_grade;
			students[index].school_major = school_major;
			students[index].school_class = school_class;
		}
	}

	//删除学生信息
	void StudentInformation::deleteStudent(std::string school_id) {
		int index = findStudent(school_id);
		if (index >= 0) {
			students.erase(students.begin() + index);//删除指定位置的容器
		}
	}

	//添加学生素养信息
	void StudentInformation::addAccomplishment(std::string school_id, std::string behavior, bool isIncrease, float scoure) {
		int index = findStudent(school_id);
		if (index >= 0) {
			accomplishment a;
			a.behavior = behavior;
			a.isIncrease = isIncrease;
			a.scoure = scoure;
			students[index].accomplishments.push_back(a);
		}
	}

	//修改学生素养信息
	void StudentInformation::modifyAccomplishment(std::string school_id, int index, std::string behavior, bool isIncrease, float scoure) {
		int studentIndex = findStudent(school_id);
		if (studentIndex >= 0 && index < students[studentIndex].accomplishments.size()) {
			students[studentIndex].accomplishments[index].behavior = behavior;
			students[studentIndex].accomplishments[index].isIncrease = isIncrease;
			students[studentIndex].accomplishments[index].scoure = scoure;
		}
	}

	//删除学生素养信息
	void StudentInformation::deleteAccomplishment(std::string school_id, int index) {
		//index:第n条信息,从0开始
		int studentIndex = findStudent(school_id);
		if (studentIndex >= 0 && index < students[studentIndex].accomplishments.size()) {
			students[studentIndex].accomplishments.erase(students[studentIndex].accomplishments.begin() + index);
		}
	}

}