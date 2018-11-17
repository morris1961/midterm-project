#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double Distance (double x1, double y1, double x2, double y2);
double findRiskPoint(double x, double y, int risk_x[], int risk_y[], int radius[], int risk[], int risk_num);
void putData(int x[], int num);
void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[]);

int main ()
{
	int n = 0, risk_num = 0, turn_weight = 0, dis_limit = 0, start_x = 0, start_y = 0, end_x = 0, end_y = 0;
	cin >> n >> risk_num >> turn_weight >> dis_limit;
	int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];

	putData (risk_x, risk_num);
	putData (risk_y, risk_num);
	putData (radius, risk_num);
	putData (risk, risk_num);
	cin >> start_x >> start_y >> end_x >> end_y;

	for (int i = n; i >= 0; i--)
	{
		for (int j = 0; j <= n; j++)
		{
			double a = findRiskPoint(j, i, risk_x, risk_y, radius, risk, risk_num);
			cout << fixed << setprecision(6) << a << '\t';
		}
		cout << endl;
	}
	
	releaseMemory(risk_x, risk_y, radius, risk);
	return 0;
}

double Distance (double x1, double y1, double x2, double y2)
{
	double d = sqrt( pow( (x1 - x2),2) + pow( (y1 - y2),2));
	return d;
}

void putData(int x[], int num)
{
	for (int i = 0; i < num; i++)
	{
		cin >> x[i];
	}
}

double findRiskPoint(double x, double y, int risk_x[], int risk_y[], int radius[], int risk[], int risk_num)
{
	double risk_sum = 0;
	for (int k = 0; k < risk_num; k++)
	{
		double temp = risk[k] * (radius[k] -Distance(risk_x[k], risk_y[k], x, y)) / radius[k];
		if (temp > 0)
			risk_sum += temp;
	}
	return risk_sum;
}

void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}

