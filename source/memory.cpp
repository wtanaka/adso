#include "memory.h"


Memory::Memory() { 

	verb_conjugation = 0;

	names	 	= new std::vector<std::string>;
	unlikely 	= new std::vector<std::string>;
	likely	 	= new std::vector<std::string>;
	complements 	= new std::vector<std::string>;
	tense	 	= new std::vector<std::string>;
	predecessors 	= new std::vector<std::string>;

	unlikely->push_back("之");
        unlikely->push_back("实");
	unlikely->push_back("有"); 
	unlikely->push_back("也");
	unlikely->push_back("上");
	unlikely->push_back("等");
	unlikely->push_back("起");
	unlikely->push_back("不");
	unlikely->push_back("说");
	unlikely->push_back("在");
	unlikely->push_back("过");
	unlikely->push_back("了");
	unlikely->push_back("看");
	unlikely->push_back("在");
	unlikely->push_back("那");
	unlikely->push_back("该");
	unlikely->push_back("里");
	unlikely->push_back("到");
	unlikely->push_back("这");
	unlikely->push_back("走");
	unlikely->push_back("内");
	unlikely->push_back("中");
	unlikely->push_back("对");
	unlikely->push_back("最");
	unlikely->push_back("的");
	unlikely->push_back("被");
	unlikely->push_back("骗");
	unlikely->push_back("韩");
	unlikely->push_back("时");
	unlikely->push_back("他");
	unlikely->push_back("她");
	unlikely->push_back("它");
	unlikely->push_back("我");
	unlikely->push_back("你");
	unlikely->push_back("网");
	unlikely->push_back("是");
	unlikely->push_back("像");
	unlikely->push_back("是");
	unlikely->push_back("第");
	unlikely->push_back("把");
	unlikely->push_back("着");
	unlikely->push_back("外");
	unlikely->push_back("与");
	unlikely->push_back("就");
	unlikely->push_back("于");


	likely->push_back("芙");
	likely->push_back("蓉");
	likely->push_back("建");
	likely->push_back("军");
	likely->push_back("红");
	likely->push_back("旗");
	likely->push_back("清");
	likely->push_back("新");
	likely->push_back("胜");
	likely->push_back("利");
	likely->push_back("春");
	likely->push_back("雨");
	likely->push_back("毅");
	likely->push_back("光");
	likely->push_back("明");
	likely->push_back("民");
	likely->push_back("桂");
	likely->push_back("勤");
	likely->push_back("宝");
	likely->push_back("保");
	likely->push_back("志");
	likely->push_back("勇");
	likely->push_back("平");
	likely->push_back("玉");
	likely->push_back("金");
	likely->push_back("菊");
	likely->push_back("花");
	likely->push_back("金");
	likely->push_back("元");
	likely->push_back("山");
	likely->push_back("卫");
	likely->push_back("兵");
	likely->push_back("阳");
	likely->push_back("平");
	likely->push_back("海");
	likely->push_back("国");
	likely->push_back("燕");
	likely->push_back("曙");
	likely->push_back("忠");
	likely->push_back("宏");
	likely->push_back("伟");
	likely->push_back("兰");
	likely->push_back("吉");
	likely->push_back("祥");

	complements->push_back("上");
	complements->push_back("下");
	complements->push_back("好");
	complements->push_back("来");
	complements->push_back("到");
	complements->push_back("遍");
	complements->push_back("往");
	complements->push_back("道");
	complements->push_back("完");
	complements->push_back("断");
	complements->push_back("出");
	complements->push_back("去");

	complements->push_back("不过");
	complements->push_back("出来");
	complements->push_back("出去");
	complements->push_back("得起");
	complements->push_back("不起");
	complements->push_back("下来");
	complements->push_back("上来");
	complements->push_back("下去");
	complements->push_back("上去");
	complements->push_back("起来");
	complements->push_back("一下");
	complements->push_back("下来");
	complements->push_back("不了");
	complements->push_back("得了");
	complements->push_back("不到");
	complements->push_back("得到");

	tense->push_back("了");
	tense->push_back("过");
	tense->push_back("着");
	tense->push_back("著");

	predecessors->push_back("被");
	predecessors->push_back("正在");

};
Memory::~Memory() {
 likely->clear();
 unlikely->clear();
 complements->clear();
 tense->clear();
 names->clear();
 predecessors->clear();
 delete likely;
 delete unlikely;
 delete names;
}


