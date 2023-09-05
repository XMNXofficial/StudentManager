#include<iostream>
#include<vector>
namespace students {

	//素养
	struct accomplishment {
		std::string behavior;//行为
		bool isIncrease;
		float scoure;
	};

	//学生信息
	struct student {
		std::string name;//姓名
		std::string school_id;//学号
		std::string school_grade;//年级
		std::string school_major;//专业
		std::string school_class;//班级
		std::vector <accomplishment> accomplishments;
	};

	class StudentInformation {
	private:
		//通过学号查找学生在vector中的位置
		int findStudent(std::string school_id) {
			for (int i = 0; i < students.size(); ++i) {
				if (students[i].school_id == school_id) {
					return i;
				}
			}
			return -1;
		}

	public:
		std::vector<student>students;

		//添加学生信息
		void addStudent(std::string name, std::string school_id, std::string school_grade, std::string school_major, std::string school_class);

		//修改学生信息
		void modifyStudent(std::string school_id, std::string name, std::string school_grade, std::string school_major, std::string school_class);

		//删除学生信息
		void deleteStudent(std::string school_id);

		//添加学生素养信息
		void addAccomplishment(std::string school_id, std::string behavior, bool isIncrease, float scoure);

		//修改学生素养信息
		void modifyAccomplishment(std::string school_id, int index, std::string behavior, bool isIncrease, float scoure);

		//删除学生素养信息
		void deleteAccomplishment(std::string school_id, int index);
	};
}