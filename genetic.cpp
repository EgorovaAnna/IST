#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

class Genetic
{
	int gen[104][6];
	float signal[80];
	int interval[6][2];
	int flag;
public:
	Genetic(int param[6], int in[6][2]);
	float fit(int num);
	void mutation();
	void generation();
	int getFlag();
	void show();
	float best();
};
float Genetic::best()
{
	float best[2], s;
	best[0] = 0;
	best[1] = fit(0);
	for(int i = 1; i < 100; i++)
	{
		s = fit(i);
		if(s < best[1])
		{
			best[0] = i;
			best[1] = s;
		}
	}
	return best[1];
}
void Genetic::show()
{
	for(int j = 0; j < 6; j++)
	{
		for(int i = 0; i < 50; i++)
			cout << gen[i][j] << ' ';
		cout << '\n';
	}
	for(int j = 0; j < 6; j++)
	{
		for(int i = 50; i < 100; i++)
			cout << gen[i][j] << ' ';
		cout << '\n';
	}
};
Genetic::Genetic(int param[6], int in[6][2])
{
	int i, j;
	for(i = 0; i < 80; i++)
	{
		signal[i] = param[0]*(exp(-pow(float(i - param[1])/param[2], 2))) + param[3]*(exp(-pow(float(i - param[4])/param[5], 2)));
		//cout << signal[i] << " " ;
		//cout << (-pow(float(i - param[1])/(float(param[2])), 2)) << "  ";
	}
	cout << '\n';
	for(i = 0; i < 6; i++)
	{
		interval[i][0] = in[i][0];
		interval[i][1] = in[i][1];
		for(j = 0; j < 104; j++)
			gen[j][i] = in[i][0] + rand()%(in[i][1] - in[i][0]);
	}
	flag = 0;
};
int Genetic::getFlag()
{
	return flag;
};
float Genetic::fit(int num)
{
	float sum = 0;
	for(int i = 0; i < 80; i++)
		sum += pow(float(signal[i]) - gen[num][0]*(exp(-pow(float(i - gen[num][1])/gen[num][2], 2))) - gen[num][3]*(exp(-pow(float(i - gen[num][4])/gen[num][5], 2))), 2);
	return pow(sum, 0.5);
};
void Genetic::mutation()
{
	int mut[2];
	for(int i = 0; i < 10; i++)
	{
		mut[0] = rand()%100;
		mut[1] = rand()%6;
		//cout << mut[0] << ' ' << mut[1] << '\n';
		gen[mut[0]][mut[1]] = interval[mut[1]][0] + rand()%(interval[mut[1]][1] - interval[mut[1]][0]);
	}
	//show();
};
void Genetic::generation()
{
	//cout << "point1" << '\n'; 
	int su[4] = {100, 101, 102, 103};
	int s;
	int j1 = rand()%100, j2;
	j2 = j1;
	while(j2 == j1)
		j2 = rand()%100;
	for(int i = 0; i < 6; i++)
	{
		gen[100][i] = gen[j1][i];
		gen[101][i] = gen[j2][i];
		//cout << "point2 " << i << '\n'; 
		if(rand()%2 == 1)
		{
			gen[102][i] = gen[j1][i];
			gen[103][i] = gen[j2][i];
		}
		else
		{
			gen[102][i] = gen[j2][i];
			gen[103][i] = gen[j1][i];
		}
	}
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (fit(su[j]) > fit(su[j + 1]))
			{
				s = su[j];
				su[j] = su[j + 1];
				su[j + 1] = s;
			}
	//cout << su[0] << ' ' << su[1] << ' ' << su[2] << ' ' << su[3] << '\n';
	if (fit(su[0]) == 0)
		flag = 1;
	for(int i = 0; i < 6; i++)
	{
		gen[j1][i] = gen[su[0]][i];
		gen[j2][i] = gen[su[1]][i];
		cout << gen[j1][i] << ", ";
	}
	//cout << fit(su[0]) << " " << fit(su[1]) << " " << fit(su[2]) << " " << fit(su[3]) << '\n';
	cout << "\n";
};
int main()
{
	srand(time(NULL));
	int g[6] = {1300, 30, 3, 2300, 45, 6};
	int in[6][2] = {{800, 2000}, {25, 35}, {2, 5}, {1500, 2500}, {35, 55}, {4, 7}};
	Genetic gen(g, in);
	gen.show();
	float best1 = gen.best();
	//cout << in[0][0] << ' ' << in[0][1]<< ' '  << in[1][0] << ' ' << in[1][1] << '\n';
	for(int i = 0; i < 1000000; i++)
	{
		if (gen.getFlag() != 1)
		{
			cout << i << "    ";
			gen.mutation();
			gen.generation();
		}
	}
	//gen.show();
	cout << best1 << "; " << gen.best() << '\n';
}