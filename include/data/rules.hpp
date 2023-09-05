#pragma once
#include<vector>
#include<string>

class rules
{
public:
	struct item
	{
		std::string thing = "";       // 事件
		bool isBonus = false;// 是否加分,加分:true,扣分:false
		float minPoint = 0;             // 最低加分或最高扣分
		float maxPoint = 0;             // 最高加分或最高扣分
		// 备注:如果没有范围的分数,则统一为赋值到maxPointz中
	};

	struct rule
	{
		std::string belong;                     // 所属规则
		std::vector<item> items;                 // 详细个规则
	};

	std::vector<rule> SchoolRule;

	rules();
};

