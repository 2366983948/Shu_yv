#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<map>
using namespace std;
map<char, int>getnum;
vector<char>getzf;
vector<string>proce(10);
vector<string>first(20);
vector<string>follow(20);
int table[100][100];      //预测分析表
int num;
int numv;						//终结符的数量-1
char j[2];
void  read()//读终结符、非终结符、产生式 
{
	int i = 0;
	int n = 0;
	cout << "输入产生式集合（空字用‘@’表示）,输入一条后换行,以'end'结束:" << endl;
	string ss;
	string dd;
	int j = 0;
	int y = 0;
	while (cin >> ss && ss != "end")
	{
		dd.clear();
		dd += ss[0];
		proce[j] += dd;
		for (i = 3; i < ss.length(); i++)
		{
			if (ss[i] != '|') {
				dd.clear();
				dd += ss[i];
				proce[j] += dd;
			}
			else
			{
				dd.clear();
				dd += ss[0];
				dd += ss[++i];
				proce[++j] += dd;
			}
		}
		j++;
	}

	getnum['#'] = 0;//#代表结束标志 
	//	getzf[0]='#';没有定义数组大小的时候这样输入是错误的 
	getzf.push_back('#');
	//终结符压栈 
	for (int i = 0; i < proce.size(); i++)
	{
		for (int k = 0; k < proce[i].length(); k++)
		{
			if (proce[i][k] != '-' && proce[i][k] != '|')
			{
				if (proce[i][k] < 64 || proce[i][k]>90)
				{
					for (y = 0; y < getzf.size(); y++)
					{
						if (proce[i][k] == getzf[y]) break;
					}
					if (y == getzf.size() && k != 2) {//这里让k!=2是不让第三位置的>进去 
						getnum[proce[i][k]] = ++n;
						getzf.push_back(proce[i][k]);
					}
				}
			}
		}
	}
	getnum['@'] = ++n;
	numv = n;//终结符的数量等于当前n的值 
	getzf.push_back('@');
	//非终结符压栈 
	for (int i = 0; i < proce.size(); i++)
	{
		for (int k = 0; k < proce[i].length(); k++)
		{
			if (proce[i][k] != '-' && proce[i][k] != '|' && proce[i][k] != '>')
			{
				if (proce[i][k] > 64 && proce[i][k] < 91)
				{
					for (y = 0; y < getzf.size(); y++)
					{
						if (proce[i][k] == getzf[y]) break;
					}
					if (y == getzf.size()) {
						getnum[proce[i][k]] = ++n;
						num = n;//终结符加非终结符的数量等于当前i的值 
						getzf.push_back(proce[i][k]);
					}
				}
			}
		}
	}
}

void get_firstT()//给终结符的first数组赋值
{
	int i;//不能在下面int 
	//先给终结符的first数组赋值
	for (i = 1; i <= numv; i++)
	{
		_itoa_s(i, j, 10);
		first[i] = j;//之前写的是first[i].push_back(j[0])是错的，字符串数组的输入不需要加下标,且如果是j[0]一个字符不能装到一个字符串当中去 
	}
}

string get_firstF(int* a)//给非终结符的first数组赋值
{//犯了一个错误，下面的a没有加* 
	for (int i = 0; i < proce.size(); i++)
	{
		if (getnum[proce[i][0]] == *a)
		{
			if (getnum[proce[i][1]] <= numv)
			{
				_itoa_s(getnum[proce[i][1]], j, 10);
				first[*a] += j;
			}
			else
			{
				//first[getnum[proce[i][0]]].clear();
				first[getnum[proce[i][0]]] = get_firstF(&getnum[proce[i][1]]);
			}
		}
	}
	return first[*a];
}

void  get_follow(int* a) {//得到follow集 
	//犯了一个错误，以stirng开头但是没有返回值 
	int i, j1;
	int flag = 0;
	for (i = 0; i < proce.size(); i++)
	{
		for (j1 = 1; j1 < proce[i].length(); j1++)
		{
			if (getnum[proce[i][j1]] == *a)//这地方应该是j1我写成了k 
			{
				if (j1 == proce[i].length() - 1)
				{
					if (getnum[proce[i][j1]] != getnum[proce[i][0]])
						follow[*a] += follow[getnum[proce[i][0]]];
				}
				else
				{
					if (getnum[proce[i][j1 + 1]] <= numv)
					{
						_itoa_s(getnum[proce[i][j1 + 1]], j, 10);
						follow[*a] += j;
					}
					else
					{
						for (int jj = 0; jj < first[getnum[proce[i][j1 + 1]]].size(); jj++)
						{
							if (atoi(&first[getnum[proce[i][j1 + 1]]][jj]) == numv)//等于空时
								follow[*a] += follow[getnum[proce[i][0]]];
							else
								follow[*a] += first[getnum[proce[i][j1 + 1]]][jj];
						}
						flag = 1;//标志位，如果已经找到*a后面的非终结符就可以停止了 
					}
				}
			}
		}

		if (flag == 1) break; //停止寻找 
	}
}

void get_table()          //得预测分析表
{
	//memset(table, -1, sizeof(table));//刚开始tableM没有初始化，导致本该是空格的地方出现E->TA 
	for (int i = 0; i < proce.size(); i++)   //扫所有产生式
	{
		if (proce[i].size() == 0)break;
		if (proce[i][1] == '@')     //直接推出空字的，特判下（follow集=产生式左边的vn中元素填）
		{
			string flw = follow[getnum[proce[i][0]]];
			for (int k = 0; k < flw.size(); k++)
			{
				table[getnum[proce[i][0]]][flw[k] - '0'] = i;
			}
		}
		string temps = first[getnum[proce[i][1]]];
		for (int j = 0; j < temps.size(); j++)               //考察first集
		{
			if (atoi(&temps[j]) != numv)
			{
				// table[getnum[proce[i][0]]][atoi(&temps[j])]=i;//atoi不能这么用，他表示的是从当前位一直到末位 
				table[getnum[proce[i][0]]][temps[j] - '0'] = i;
			}
			else                                     //有空字的，考察follw集
			{
				string flw = follow[getnum[proce[i][1]]];
				for (int k = 0; k < flw.size(); k++)
				{
					table[getnum[proce[i][0]]][flw[k] - '0'] = i;
				}
			}
		}
	}
}

string get_proce(int i)  //由对应下标获得对应产生式
{
	if (i < 0)return " ";    //无该产生式
	string ss;
	ss += proce[i][0];
	ss += "->";		//把->要加上 
	for (int j = 1; j < proce[i].size(); j++)
		ss += proce[i][j];
	return ss;
}

void print_table()//输出预测分析表 
{
	cout << "预测分析表：" << endl;
	for (int i = 0; i < numv; i++)
		cout << '\t' << getzf[i];
	//cout << endl;
	for (int i = numv + 1; i <= num; i++)
	{
		cout << endl << "________________________________________________________" << endl;
		cout << getzf[i];
		for (int j = 0; j < numv; j++)
		{
			cout << '\t' << get_proce(table[i][j]) << "";
		}
	}
	cout << endl << "________________________________________________________" << endl;
	cout << endl;
}

string word;
bool analyze()       //分析word的合法性，若合法，输出所有产生式
{
	stack<char>sta;
	sta.push('#');  //#最先进栈 
	sta.push(proce[0][0]);
	int i = 0;
	while (!sta.empty())
	{
		int cur = sta.top();
		sta.pop();
		if (cur == word[i])       //是终结符的话找下一个 
		{
			i++;
		}
		else  if (cur == '#')   //遇到#结束
		{
			return 1;
		}
		else  if (table[getnum[cur]][getnum[word[i]]] != -1) //查表
		{

			int k = table[getnum[cur]][getnum[word[i]]];
			cout << proce[k][0] << "->";
			for (int j = 1; j < proce[k].size(); j++)
				cout << proce[k][j];
			cout << endl;
			for (int j = proce[k].size() - 1; j > 0; j--)  //逆序入栈
			{
				if (proce[k][j] != '@')
					sta.push(proce[k][j]);
			}
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void scanf()   //输入字
{
	cout << "请输入字：" << endl;
	cin >> word;
	if (analyze())
		cout << "该字有效，所用产生式如上!" << endl;
	else
		cout << "出错了!" << endl;
}

int main()
{
	int k;
	read();
	//终结符的first集 
	get_firstT();
	//非终结符的first集 
	for (k = numv + 1; k <= num; k++)			//犯了一个错误，numv的位置写成7 
	{
		get_firstF(&k);
	}

	follow[numv + 1] += '0';							//这地方加的是0而不是# 
	for (k = numv + 1; k <= num; k++)		//犯了一个错误，numv的位置写成7 
	{
		get_follow(&k);
	}
	cout << endl;
	get_table();
	print_table();
	scanf();
	return 0;
}