#include"data/student_data.hpp"
#include<iostream>
#include<vector>
#include<random>
#include<string>
namespace student_data {
	StudentInformation::StudentInformation() {
		// 使用随机数生成器
		std::default_random_engine generator(time(nullptr));
		std::uniform_real_distribution<float> scoreDistribution(0.0f, 100.0f);

		// 添加10条随机数据
		for (int i = 0; i < 10; ++i) {
			std::string name = "Student" + std::to_string(i + 1);
			std::string school_id = "ID" + std::to_string(i + 1);
			std::string school_grade = "Grade" + std::to_string(i + 1);
			std::string school_major = "Major" + std::to_string(i + 1);
			std::string school_class = "Class" + std::to_string(i + 1);

			addStudent(name, school_id, school_grade, school_major, school_class);

			// 添加随机的素养信息
			for (int j = 0; j < 3; ++j) {
				std::string behavior = "Behavior" + std::to_string(j + 1);
				bool isIncrease = (j % 2 == 0); // 随机选择是增加还是减少
				float score = scoreDistribution(generator);

				addAccomplishment(school_id, behavior, isIncrease, score);
			}
		}
	}

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