#include"data/rules.hpp"
#include<vector>
#include<string>

rules::rules()
{
	rule_increase =
	{
		{"班长等班委", 2, 5},
		{"宣传委员", 2, 5},
		{"学生会组织部部长", 2, 5},
		{"当月升旗服装统一", 4, 4},
		{"月全勤", 5, 5},
		{"文明宿舍", 2, 2},
		{"标杆宿舍", 3, 3},
		{"建议勇为", 3, 5},
		{"反应或制止不良行为",  3,3},
		{"向学校刊物或广播站投稿被采纳",  2,2},
		{"当月全勤", 5, 5},
		{"国家级科技制作发明竞赛", 6, 15},
		{"省级科技制作发明竞赛", 5, 10},
		{"区级科技制作发明竞赛", 4, 9 },
		{"校级科技制作发明竞赛", 3, 8},
		{"院级科技制作发明竞赛", 2, 6},
		{"国家级知识技能文艺竞赛", 5, 10},
		{"省级知识技能文艺竞赛", 4, 8},
		{"区级知识技能文艺竞赛", 3, 7},
		{"校级知识技能文艺竞赛", 2.5, 6},
		{"院级知识技能文艺竞赛", 2, 5},
		{"积极报名参加XX讲座", 2, 2},
		{"其它学校或辅导员安排的临时性活动", 2, 3},
		{"较上月进步15分", 2, 3},
		{"勤工俭学(工作）", 2, 5},
		{"班会回答问题正确", 1, 1},
		{"寝室长", 2, 5},
		{"参加学习辅导", 2, 2},
		{"拾金不昧（捡手机,银行卡,饭卡）", 2, 2},
		{"班级集体荣誉（写具体名称）", 2, 5},
		{"积极参加竞赛/运动会项目", 2, 2},
		{"优秀学生", 4, 4},
		{"优秀团员", 4, 4},
		{"义务劳动（公益活动）", 2, 3},
		{"优秀团支部（仅团员加分）", 2, 3},
		{"青年志愿者活动", 2, 3},
		{"十佳歌手（校）", 2, 10},
		{"英语A/B级证书", 8, 8},
		{"计算机一级证书", 8, 8},
		{"保护国家集体财产或处置突发事件突出", 3,5}
	};


	rule_decrease =
	{
		{"迟到",  5, 5},
		{"早退",  5, 5},
		{"旷课",  20, 20},
		{"第5节课旷课",  10, 10},
		{"无故不参加升旗",  10, 10},
		{"无故不参加集体活动",  10, 10},
		{"周最差宿舍",  2, 16},
		{"月最差宿舍",  5, 5},
		{"班会回答问题错误",  1, 1},
		{"座牌损坏/污损不及时补办",  2, 2},
		{"上课无座牌/不摆放座牌",  2, 2},
		{"晚归（22：30以后归）",  10, 10},
		{"不按时打卡/不打卡",  5, 5},
		{"上课迟到督促不动",  5, 5},
		{"升旗服装不统一",  2, 2},
		{"辅导员课请假",  0.5, 0.5},
		{"放假返校当晚20：00未归亦未主动说明",  10, 10},
		{"学生干部不按时（量,质）完成任务",  2, 2},
		{"染发被查处",  3, 3},
		{"公众场合抽烟,穿拖鞋、乱扔垃圾",  3, 3},
		{"顶撞教职工/学生干部",  10, 10},
		{"夜晚影响他人休息",  3, 3},
		{"欺骗他人",  5, 5},
		{"强冲门岗",  5, 5},
		{"教室或寝室使用大功率用电器",  5, 5},
		{"报名竞赛/运动会无故不参加",  5, 5},
		{"受到纪律处分",  15, 30},
		{"考试作弊、夹带、违纪",  10, 10},
		{"辱骂教职工或学生干部",  10, 20},
		{"损坏公物或他人财物",  5, 5},
		{"盗用公章或签名",  10, 10},
		{"恐吓、诽谤他人",  10, 10},
		{"欺骗他人或不诚实行为",  5, 5},
		{"损坏他人/学校公务未照价赔偿",  5, 10},
		{"伪造/盗用他人证件",  10, 10},
		{"从事有损学生形象/学校声誉/社会功德的活动",  10, 10},
		{"熄灯后擅自开灯/喧哗",  3, 3},
		{"22：30以后使用音响",  5, 5}
	};

}