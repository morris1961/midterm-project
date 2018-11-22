#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double Distance (double x1, double y1, double x2, double y2);
double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num);
double RiskofLine(int startPoint[2],int changePoint[2],double lenResidual[],int risk_x[],int risk_y[],int radius[],int risk[],int risk_num);
//void findChange(start, end, fuelResidual, changePoint);
void putData(int x[], int num);
void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[]);

int turnCnt = 0;

int main ()
{
    int n = 0, risk_num = 0, turn_weight = 0, dis_limit = 0, start[2] = {0} , end[2] = {0};
    cin >> n >> risk_num >> turn_weight >> dis_limit;
    int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];
    double lenResidual[100] = {0}, fuelResidual[100] = {0};
    int changePoint[2] = {0};
    double cost = 0, min = 999999;
    
    putData (risk_x, risk_num);
    putData (risk_y, risk_num);
    putData (radius, risk_num);
    putData (risk, risk_num);
    putData (start, 2);
    //putData (changepoint, 2)
    putData (end, 2);
    
    
    int distance_y = abs (start[1] - end[1]), distance_x = abs (start[0] - end[0]);
	for (int i = 0; i <= distance_x; i++)
	{
			for (int j = 0; j <= distance_y; j++)
			{
				double temp = Distance(start[0] + i, start[1] + j, end[0], end[1]);
				if (temp < dis_limit)
				{
					changePoint[0] = start[0] + i;
					changePoint[1] = start[1] + j;
					cost = RiskofLine(start, changePoint, lenResidual, risk_x, risk_y, radius, risk, risk_num) + RiskofLine(start, changePoint, lenResidual, risk_x, risk_y, radius, risk, risk_num);
					if (min > cost)
						min = cost;
				}
			} 
	} 
    cout << min;
    //cout<<RiskofLine(start, end, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    //cout<<RiskofLine(start, changepoint, lenResidual, risk_x, risk_y, radius, risk, risk_num)<<"\n";
    //cout<<RiskofLine(changepoint, end, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    
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

double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num)
{
    double risk_sum = 0;
    for (int k = 0; k < risk_num; k++)
    {
        double temp = risk[k] * (radius[k] -Distance(risk_x[k], risk_y[k], point[0], point[1])) / radius[k];
        if (temp > 0)
            risk_sum += temp;
    }
    return risk_sum;
}

double RiskofLine(int startPoint[], int changePoint[] ,double lenResidual[] ,int risk_x[] , int risk_y[] , int radius[] , int risk[] , int risk_num )
{
    double risk_sum = 0;
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    int PointCnt = (LineDistance + lenResidual[turnCnt]);
    if(LineDistance + lenResidual[turnCnt] == static_cast<int>(LineDistance + lenResidual[turnCnt]))
        PointCnt--;
    
    double** RiskPointOfLine = new double* [PointCnt];
    for(int i = 0 ; i < PointCnt ; i++)
        RiskPointOfLine[i] = new double[2];
    
    for(int i = 0 ; i <= PointCnt - 1 ; i++)
    {
        RiskPointOfLine[i][0] = startPoint[0] + ( (i + 1 - lenResidual[turnCnt]) / LineDistance) * ( changePoint[0] - startPoint[0] );
        RiskPointOfLine[i][1] = startPoint[1] + ( (i + 1 - lenResidual[turnCnt]) / LineDistance) * ( changePoint[1] - startPoint[1] );
        //cout<<RiskPointOfLine[i][0]<<" "<<RiskPointOfLine[i][1]<<"\n";
    }
    
    for(int i = 0 ; i < PointCnt ; i++)
    {
        risk_sum += RiskofPoint( RiskPointOfLine[i] , risk_x , risk_y , radius,  risk , risk_num);
        //cout<<risk_sum<<"\n";
    }
    
    for(int i = 0 ; i < PointCnt ; i++)
    {
        delete [] RiskPointOfLine[i];
    }
    delete [] RiskPointOfLine;
    
    turnCnt++;
    lenResidual[turnCnt] = LineDistance - PointCnt;
    
    return risk_sum;
}

//void findChange(start, end, fuelResidual, changePoint)
//{
//	
//}

void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}
