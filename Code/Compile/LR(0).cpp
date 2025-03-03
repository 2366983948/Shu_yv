#include<iostream>
#include< stdlib.h >
#include<vector>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
using namespace std;			//ASCII A-Z:65-90   a-z:97-122 0-9:30-39
vector<char>getzf;				//对所有字符编个序号
map<char, int>getnum;		//查找每个字符的序号
vector<string>proce(8);		//产生式

vector<string>projects;		//项目集
vector<vector<string>>P;	//项目集规范族
map< vector<string>, int>Pnum;

int num;								//所有符号,带#
int numv;								//终结符,数量-1，去#
int n = 0;								//当前字符数
struct GO
{
	int befor;							//前状态
	char c;								//输入
	int last;								//后状态
};
vector<GO> go;					//go函数集合

//v表示终结符,扫描产生式，统计所有出现的字符
void Getzf(int numv, bool v) {
	bool condition;
	for (int i = 1; i < proce.size(); i++) {
		for (int k = 0; k < proce[i].length(); k++) {
			condition = v ? (proce[i][k] < 64 || proce[i][k]>90) && proce[i][k] != '|' : proce[i][k] > 64 && proce[i][k] < 91;
			if (condition) {
				int y;
				for (y = numv; y < getzf.size(); y++) {
					if (proce[i][k] == getzf[y]) break;
				}
				if (y == getzf.size()) {
					getnum[proce[i][k]] = ++n;
					getzf.push_back(proce[i][k]);
				}
			}
		}
	}
}
//得到产生式，同时识别终结符和非终结符
void  read()
{
	cout << "LR(0)分析程序，编制人：莫旭，20205020309，计算机3班" << endl;
	cout << "输入产生式集合（空字用‘@’表示）,输入一条后换行，以‘end’结束:" << endl;
	string ss;												//输入串
	int j = 0;
	while (cin >> ss && ss != "end")		//开始识别产生式
	{
		proce[j] += ss[0];
		for (int i = 3; i < ss.length(); i++)	//去除箭头，存储右部
		{
			if (ss[i] != '|') {								//有“|”，说明该产生式结束
				proce[j] += ss[i];
			}
			else {
				proce[++j] += ss[0];
				proce[j] += ss[++i];
			}
		}
		j++;
	}
	getnum['#'] = 0;					//#代表结束标志 
	getzf.push_back('#');
	Getzf(0, true);						//终结符压栈 
	numv = n;							//终结符的数量等于当前n的值 
	Getzf(numv + 1, false);		//非终结符压栈
	num = n;
}
//文法的项目project
void GetPro()
{
	for (auto p : proce) {
		if (p == "")break;
		for (int i = 1; i < p.size(); i++) {
			string _p = p;
			_p.insert(i, ".");
			projects.emplace_back(_p);
		}
		projects.emplace_back(p + ".");
	}
}
//求闭包
vector<string>Closure(vector<string>s) {
	vector<string>result;
	deque<string>de;
	for (auto _s : s) {
		de.emplace_back(_s);
	}
	while (!de.empty()) {
		string str = de.front();
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '.') {
				if (i == 1) {								//排除E->.E+的情况
					if (str[0] == str[2])break;
				}
				if (i + 1 <= str.size()) {
					if (str[i + 1] > 64 && str[i + 1] < 91) {
						for (auto p : projects) {
							if (p[0] == str[i + 1] && p[1] == '.')
								de.push_back(p);
						}
					}
					else break;
				}
				break;
			}
		}
		de.pop_front();
		result.push_back(str);
	}
	return result;
}
//项目集规范族,specification规范
void GetPro_s()
{
	vector<string>I0 = { projects[0] };
	P.emplace_back(Closure(I0));
	Pnum[P[0]] = 0;
	GO go1;
	queue<vector<string>>qu;
	qu.push(P[0]);
	while (!qu.empty()) {
		set<char>can_mov_c;					//可以移进字符
		vector<string>I = qu.front();		//I作为读取队列的参数
		int I_befor = Pnum[I];					//存放goto数据

		can_mov_c.clear();
		for (auto _I : I) {
			for (int i = 1; i < _I.size() - 1; i++) {
				if (_I[i] == '.') {
					can_mov_c.emplace(_I[i + 1]);
				}
			}
		}
		if (can_mov_c.size() == 0) {							//没有移进
			qu.pop();
			continue;
		}
		for (auto _c : can_mov_c) {							//将可以移进的字符移进
			vector<string>new_project;					//存放移进后的产生式
			for (auto _I : I) {
				for (int i = 1; i < _I.size() - 1; i++) {		//找到可以移进的产生式，移进后加入new_projrct
					if (_I[i] == '.' && _I[i + 1] == _c) {
						_I[i + 1] = '.'; _I[i] = _c;
						new_project.emplace_back(_I);
						break;
					}
				}
			}
			new_project = Closure(new_project);							//求闭包
			if (Pnum.find(new_project) == Pnum.end()) {				//闭包后，查看是否已拥有。没有则添加进P，和Pnum
				Pnum[new_project] = Pnum.size();
				P.push_back(new_project);
				qu.push(new_project);
			}
			//go函数赋值,存入go集合
			go1.befor = I_befor;
			go1.c = _c;
			go1.last = Pnum[new_project];
			go.emplace_back(go1);
		}
		qu.pop();
	}
}
//创建LR(0)分析表
vector<vector<string>> createTable() {
	vector<vector<string>>table(P.size(), vector<string>(getzf.size()));
	//表的第一行
	cout << endl << "          LR(0)分析表" << endl << "状态\t";
	for (int i = 1; i < getzf.size() + 1; i++) { cout << getzf[i - 1] << "\t"; }
	//移进和接受
	for (auto g : go) {														//在go函数里遍历，把所有移进写入表
		table[g.befor][getnum[g.c]] += "s";
		char last_s[3] = "";
		_itoa_s(g.last, last_s, 3, 10);
		table[g.befor][getnum[g.c]] += last_s;
	}
	//规约
	for (int i = 0; i < P.size(); i++) {								//遍历项目集规范族
		for (auto _p : P[i]) {												//遍历族里的每一条产生式
			if (_p[_p.size() - 1] == '.' && _p != "SE.") {		//产生式最后一个是“.”但不是接受，
				_p.pop_back();												//去除"."，找到产生式的序号，在表相应的位置写上操作
				for (int j = 0; j < proce.size(); j++) {
					if (proce[j] == _p) {
						char ch[3] = "";
						_itoa_s(j, ch, 3, 10);
						for (int k = 0; k < table[i].size(); k++) {
							table[i][k] += "r";
							table[i][k] += ch;
						}
					}
				}
			}
		}
	}
	//显示表
	table[1][getnum['#']] = "acc";
	for (int i = 0; i < table.size(); i++) {
		cout << endl << "--------------------------------------------------------------------" << endl;
		cout << i << "\t";
		for (int j = 0; j < table[0].size(); j++) { cout << table[i][j] << "\t"; }			//状态输出
	}
	return table;
}
//得到序号，例如 s2里的 2
int get_index(string s) {
	int index = 0;
	if (s.size() > 2) {
		index = s[1] - '0';
		index = index * 10 + (s[2] - '0');
	}
	else index = s[1] - '0';
	return index;
}
//LR分析器
void LR0(vector<vector<string>>tab) {
	string s_in;								//输入串
	string st = "#";							//符号栈
	vector<int> v(1, 0);					//状态栈
	int fh = 0, sr = 0, i = 1;			//指针，符号栈和状态栈公用同一个指针 fh
	cout << endl << endl << "输入字符串：";
	cin >> s_in;
	s_in += '#';
	cout << endl << "步骤\t状态\t符号\t输入串\t动作";
	int index = 0;
	while (1) {
		string str = tab[v[fh]][getnum[s_in[sr]]];
		//显示
		string dongzuo;
		switch (str[0]) {
		case 'r':dongzuo = "归约"; break;
		case 's':dongzuo = "移进"; break;
		case 'a':dongzuo = "acc"; break;
		default:dongzuo = "出错"; break;
		}
		cout << endl << "-----------------------------------------------" << endl;
		cout << i << "\t";
		for (auto _v : v) {
			cout << _v;
		}
		cout << "\t" << st << "\t" << s_in << "\t" << dongzuo;
		//判断
		if (str == "acc") {
			cout << endl << endl << "分析成功" << endl;
			break;
		}
		if (str == "") {
			cout << endl << endl << "分析出错" << endl;
			break;
		}
		//归约
		if (str[0] == 'r') {
			index = get_index(str);				//获得归约使用产生式序号
			string _proce = proce[index];		//得到该产生式
			//符号更新
			fh -= _proce.size() - 2;
			st.erase(fh);
			st += _proce[0];
			//状态更新
			for (int x = 0; x < _proce.size() - 2; x++) {
				v.pop_back();
			}
			string temp = tab[v[fh - 1]][getnum[_proce[0]]];
			v[fh] = get_index(temp);
			//输入串不变
			//把归约所用的产生式显示出来
			cout << _proce[0] << "->" << _proce.substr(1);
		}
		//移进
		else {
			v.emplace_back(get_index(str));		//状态更新
			st += s_in[sr];									//符号更新
			fh++;
			s_in[sr] = ' ';										//输入串更新
			sr++;
		}
		i++;
	}
}
int main()
{
	read();													//得到产生式，同时识别终结符和非终结符
	GetPro();												//求文法的项目project
	GetPro_s();											//求项目集规范族P
	vector<vector<string>>tab = createTable();
	LR0(tab);												//根据表去分析
	return 0;
}