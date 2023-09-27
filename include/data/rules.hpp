#pragma once
#include<vector>
#include<string>

class rules
{
public:
	struct item
	{
		std::string thing = "";       // 事件
		float minPoint = 0;             // 最低加分或最高扣分
		float maxPoint = 0;             // 最高加分或最高扣分
		// 备注:如果没有范围的分数,则统一为赋值到maxPointz中
	};


	std::vector<item> rule_increase;
	std::vector<item> rule_decrease;

	rules();
};

