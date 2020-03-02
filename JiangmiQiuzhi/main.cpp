#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Exp
{
	int xishu;
	int cishu;
};
vector<Exp>* fenXi(string);
string replace_space(string*);

// 提取多项式的系数及次数
vector<Exp>* fenXi(string exp)
{
	vector<Exp>* exp_list = new vector<Exp>;
	string last_exp;
	// 循环遍历字符串
	for (int i = 0; i < exp.size(); i++)
	{
		// 判断下一个是否为下一个单项式的开始或多项式的末尾
		if (exp[i] == '+' || exp[i] == '-' || i == exp.size() - 1)
		{
			// 如果为多项式的结尾，则要补充上最后一个数据
			if (i == exp.size() - 1) {
				last_exp += exp[i];
			}
			Exp a;

			// 判断是否为常数项
			if (last_exp.find("x") == -1)
			{
				a.cishu = 0;
				a.xishu = atoi(last_exp.data());
			}
			else {
				// 获取单项式的次数
				int up_pos = last_exp.find("^");
				// 判断是否省略次数
				if (up_pos == -1) {
					a.cishu = 1;
				}
				else {
					a.cishu = atoi(&last_exp[up_pos + 1]);
				}
				// 获取单项式的次数
				string s;
				for (int index = 0; index < last_exp.size(); index++)
				{
					// 判断下一个字符是否不是数字或符号
					if (!((last_exp[index] > 47 && last_exp[index] < 58) || last_exp[index] == '-' || last_exp[index] == '+'))
					{
						// 判断前系数是否省略，如省略则自动设1
						if (s == "" || s == "+") {
							a.xishu = 1;
						}
						else if (s == "-") {
							a.xishu = -1;
						}
						else {
							a.xishu = atoi(s.data());
						}
						break;
					}
					// 将系数添加到队列
					s += last_exp[index];
				}
				// 如果前面是负数，系数则为前面的相反数
				/*if (last_exp[0] == '-'){
					a.xishu -= 2 * a.xishu;
				}*/
			}
			// 将分析完成的数据放入列表
			exp_list->push_back(a);
			// 将下一个的符号添加到队列中，并清除之前的数据
			last_exp = exp[i];
		}
		else {
			last_exp += exp[i];
		}
	}
	return exp_list;
}

// 删除空格
string replace_space(string* exp) {
	string str;
	for (int index = 0; index < exp->size(); index++)
	{
		if ((*exp)[index] != ' ') {
			str += (*exp)[index];
		}
	}
	return str;
}

// 补齐次数项
void if_add_cishu(vector<Exp>* exp)
{
	int last_cishu = (*exp)[0].cishu + 1;
	for (vector<Exp>::iterator it = exp->begin(); it < exp->end(); ++it)
	{
		if (it->cishu != last_cishu - 1)
		{
			Exp _ = { 0, last_cishu - 1 };
			it = exp->insert(it, _);
		}
		last_cishu = it->cishu;
	}
}

// 删除首位出现的零
void remove_zero(vector<Exp>* exp)
{
	for (vector<Exp>::iterator it = exp->begin(); it < exp->end(); ++it)
	{
		if (it->xishu == 0)
		{
			it = exp->erase(it);
		}
		else
		{
			break;
		}
	}
}

// 判断被除数是否大于除数
bool if_dividend_bigger_than_divisor(vector<Exp>* exp, vector<int>* main_exp)
{
	// 判断位数
	if (exp->size() > main_exp->size())
	{
		return false;
	}
	else if (exp->size() > main_exp->size())
	{
		return true;
	}
	// 位数相同时判断每一位的大小
	for (int index = 0; index < exp->size(); index++)
	{
		if ((*main_exp)[index] < (*exp)[index].xishu)
		{
			return false;
		}
	}
	return true;
}

vector<int>* cheng(vector<Exp>* exp, int bei) 
{
	vector<int>* result = new vector<int>;
	for (vector<Exp>::iterator it = exp->begin(); it < exp->end(); ++it) 
	{
		result->push_back((it->xishu) * bei);
	}
	return result;
}

int beishu(vector<Exp>* exp, vector<int>* main_exp) 
{
	int bei = 2;
	while (true)
	{
		vector<int>* result = cheng(exp, bei);
		if (if_dividend_bigger_than_divisor(exp, main_exp)) 
		{
			bei += 1;
			delete result;
		}
		else {
			delete result;
			return bei - 1;
		}
	}
}

// 数组转换整数
int zhuanhuan(vector<int>* exp) 
{
	string str;
	vector<int> daijian;
	for (int index = 0; index < exp->size(); index++)
	{
		if ((*exp)[index] < 0) 
		{
			str += "0";
			string shu = to_string((*exp)[index]);
			// 截掉负号
			shu = shu.substr(1, shu.size());
			// 该数后补充0
			shu = shu + string("0", (exp->size() - index + 1));
			// 转换为整数，添加到待减列表
			daijian.push_back(atoi(shu.data()));
		}
		else 
		{
			str += to_string((*exp)[index]);
		}
	}
	int result = atoi(str.data());
	for (vector<int>::iterator it = daijian.begin(); it < daijian.end(); it++) 
	{
		result -= *it;
	}
	return result;
}

// 被除数的每一项减去除数的每一项
vector<int>* sub(vector<Exp>* exp, vector<int>* main_exp) 
{
}


// 大除法！！！
int big_divide(vector<Exp>* exp, vector<Exp>* main_exp)
{
	// 删除首位出现的0
	remove_zero(exp);
	remove_zero(main_exp);
	// 从总被除数中取出与除数相同个数的数，添加到当前被除数
	int beichuNextCount = exp->size();
	vector<int> dangqian(exp->size());
	for (int i = 0; i < dangqian.size(); i++) {
		dangqian[i] = (*exp)[i].xishu;
	}
	int bei;
	while (true) 
	{
		// 判断被除数是否大于除数
		if (if_dividend_bigger_than_divisor(exp, &dangqian)) 
		{
			// 遍历测试被除数是除数的多少倍(取整)(也就是商)
			bei = beishu(exp, &dangqian);

			// 除数的每一项乘以倍数
			vector<int>* result = cheng(exp, bei);

			// 被除数的每一项减去除数的每一项


			// 将他们的差设为新一轮的被除数
		}
		else
		{
			// 判断总被除数内是否还有未添加到当前被除数的数
			if (beichuNextCount != main_exp->size())
			{
				// 将总被除数的下一位添加到当前被除数
				dangqian.push_back((*main_exp)[beichuNextCount].xishu);
			}
			else
			{
				// 已没有要除的数，大除法完成，程序返回余数
				return;
			}
		}
	}

	return 0;
}

int main(void)
{
	string exp, main_exp;
	cout << "请输入已知式(xx xx = 0,)‘=0’省略：";
	cin >> exp;
	vector<Exp>* exp_list = fenXi(replace_space(&exp));
	if_add_cishu(exp_list);

	cout << "请输入待求式：";
	cin >> main_exp;
	vector<Exp>* main_exp_list = fenXi(replace_space(&exp));
	if_add_cishu(exp_list);

	return 0;
}