#include <iostream>
#include <string>
#include <vector>
//#include <stdilb.h>

using namespace std;

struct Exp 
{
	int xishu;
	int cishu;
};
vector<Exp>* fenXi(string);
string replace_space(string*);

// ��ȡ����ʽ��ϵ��������
vector<Exp>* fenXi(string exp)
{
	vector<Exp>* exp_list = new vector<Exp>;
	string last_exp;
	// ѭ�������ַ���
	for (int i = 0; i < exp.size(); i++) 
	{
		// �ж���һ���Ƿ�Ϊ��һ������ʽ�Ŀ�ʼ�����ʽ��ĩβ
		if (exp[i] == '+' || exp[i] == '-' || i == exp.size() - 1)
		{
			// ���Ϊ����ʽ�Ľ�β����Ҫ���������һ������
			if (i == exp.size() - 1) {
				last_exp += exp[i];
			}
			Exp a;

			// �ж��Ƿ�Ϊ������
			if (last_exp.find("x") == -1)
			{
				a.cishu = 0;
				a.xishu = atoi(last_exp.data());
			}
			else {
				// ��ȡ����ʽ�Ĵ���
				int up_pos = last_exp.find("^");
				// �ж��Ƿ�ʡ�Դ���
				if (up_pos == -1) {
					a.cishu = 1;
				}
				else {
					a.cishu = atoi(&last_exp[up_pos + 1]);
				}
				// ��ȡ����ʽ�Ĵ���
				string s;
				for (int index = 0; index < last_exp.size(); index++)
				{
					// �ж���һ���ַ��Ƿ������ֻ����
					if (!((last_exp[index] > 47 && last_exp[index] < 58) || last_exp[index] == '-' || last_exp[index] == '+'))
					{
						// �ж�ǰϵ���Ƿ�ʡ�ԣ���ʡ�����Զ���1
						if (s == "" || s == "+") {
							a.xishu = 1;
						}else if (s == "-") {
							a.xishu = -1;
						}else {
							a.xishu = atoi(s.data());
						}
						break;
					}
					// ��ϵ����ӵ�����
					s += last_exp[index];
				}
				// ���ǰ���Ǹ�����ϵ����Ϊǰ����෴��
				/*if (last_exp[0] == '-'){
					a.xishu -= 2 * a.xishu;
				}*/
			}
			// ��������ɵ����ݷ����б�
			exp_list->push_back(a);
			// ����һ���ķ�����ӵ������У������֮ǰ������
			last_exp = exp[i];
		}
		else {
			last_exp += exp[i];
		}
	}
	return exp_list;
}

// ɾ���ո�
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

// ���������
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

bool if_dividend_bigger_than_divisor(vector<Exp>* exp, vector<Exp>* main_exp) 
{
	for (int index = 0; index < exp->size(); index++)
	{
		if ((*main_exp)[index].xishu < (*exp)[index].xishu)
		{
			return false;
		}
	}
	return true;
}

// �����������
int big_divide(vector<Exp>* exp, vector<Exp>* main_exp) 
{
	if_dividend_bigger_than_divisor(exp, main_exp);


	return 0;
}

int main(void) 
{
	string exp, main_exp;
	cout << "��������֪ʽ(xx xx = 0,)��=0��ʡ�ԣ�";
	cin >> exp;
	vector<Exp>* exp_list = fenXi(replace_space(&exp));
	if_add_cishu(exp_list);

	cout << "���������ʽ��";
	cin >> main_exp;
	vector<Exp>* main_exp_list = fenXi(replace_space(&exp));
	if_add_cishu(exp_list);

	return 0;
}