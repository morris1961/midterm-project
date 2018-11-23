#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
using namespace std;

double Distance (double x1, double y1, double x2, double y2);
double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num);
double RiskofLine(int startPoint[2],int changePoint[2],double lenResidual[],int risk_x[],int risk_y[],int radius[],int risk[],int risk_num);
//void findChange(start, endP, fuelResidual, changePoint);
void putData(int x[], int num);
void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[]);

bool countChange = false;
int turnCnt = 1;
const int CHANGE_LIMIT = 1;

int main ()
{
	clock_t a = clock();
    int n = 0, risk_num = 0, turn_weight = 0, start[2] = {0} , endP[2] = {0};
    double dis_limit, min = 99999;
    cin >> n >> risk_num >> turn_weight >> dis_limit;
    int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];
    double lenResidual[100] = {0}, turnmin[100] = {0}, lastResidual = 0, tempResidual = 0;
    int changePoint[2] = {0}, minChange[100][2] = {0}, answerCnt = 0;
    bool noFuel = false;
    
    putData (risk_x, risk_num);
    putData (risk_y, risk_num);
    putData (radius, risk_num);
    putData (risk, risk_num);
    putData (start, 2);
    //putData (changepoint, 2)
    putData (endP, 2);
    min = RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    answerCnt = 0;
    
    
	while(turnCnt <= CHANGE_LIMIT)
   {
   		countChange = false;
   		int min_x, min_y, max_x, max_y;
   		if (start[0] > endP[0])
   		{
   			max_x = start[0];
			min_x = endP[0];	
		}
		else
		{
			max_x = endP[0];
			min_x = start[0];
		}
		if (start[1] > endP[1])
   		{
   			max_y = start[1];
			min_y = endP[1];	
		}
		else
		{
			max_y = endP[1];
			min_y = start[1];
		}
		
    	noFuel = true;
		double cost = 0;
		turnmin[turnCnt] = 999999;	
	    for (int i = min_x; i <= max_x; i++)
		{
			for (int j = min_y; j <= max_y; j++)
			{
				if (i == start[0] && j == start[1])
					continue;
				double temp = Distance(start[0], start[1], i, j) + Distance(endP[0], endP[1], i, j);
				if (temp < dis_limit)
				{
					noFuel = false;
					lenResidual[turnCnt] = lastResidual;
					changePoint[0] = i;
					changePoint[1] = j;
					cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<changePoint[0] << "," << changePoint[1] << ") :";
					cost = RiskofLine(start, changePoint, lenResidual, risk_x, risk_y, radius, risk, risk_num);
				//	cout << cost <<" then residual is ";
					
					double LineDistance = Distance( start[0], start[1], changePoint[0], changePoint[1]);
					int PointCnt = (LineDistance + lenResidual[turnCnt]);
					if (lastResidual != 0 && i == endP[0] && j == endP[1])
				    	if(LineDistance + lenResidual[turnCnt] == static_cast<int>(LineDistance + lenResidual[turnCnt]))
				    	{
				    		countChange = true;
				    		PointCnt--;
						}
				        	
					lenResidual[turnCnt] = LineDistance - PointCnt;
				//	cout << lenResidual[turnCnt];
					if (changePoint[0] != endP[0] || changePoint[1] != endP[1])
						cost += RiskofLine(changePoint, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
					cout  << cost;
				
					if (turnmin[turnCnt] > cost)
					{
						minChange[turnCnt][0] = i;
						minChange[turnCnt][1] = j;
						turnmin[turnCnt] = cost;
						tempResidual = lenResidual[turnCnt];
					}
					cout << "\n";
					//cout << turnmin[turnCnt];
				}
			} 
					
		}
		cost = RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
		if (minChange[turnCnt][0] == endP[0] && minChange[turnCnt][1] == endP[1])
		{
			cout << "arrive !!" << endl;
			turnCnt--;
			break;
		}
		
		if(noFuel)
		{
			cout << "nofuel !!" << endl;
			turnCnt--;
			break;
		}
		
		if (turnmin[turnCnt] >= cost)
		{
			cout << "arrive !!" << endl;
			turnCnt--;
			break;
		} 
		lastResidual = tempResidual;
		dis_limit -= Distance(start[0], start[1], minChange[turnCnt][0], minChange[turnCnt][1]);
		start[0] = minChange[turnCnt][0];
		start[1] = minChange[turnCnt][1];
	    cout <<turnCnt<<" "<<minChange[turnCnt][0] <<" "<<minChange[turnCnt][1] <<" "<< turnmin[turnCnt] <<" residual distance" << dis_limit<< endl;
	    turnCnt++;
	}
	if (turnCnt > CHANGE_LIMIT)
		turnCnt -= 1;
	cout << "turncount = "<< 0 << ",cost = " << min << endl;
	double sum = 0;
	for(int i = 1; i <= turnCnt; i++ )
	{
		sum += turnmin[i];
		cout << "turncount = " << i << ",cost = " << sum + i*turn_weight << endl;
		double temp = sum + i*turn_weight;
		if (min > temp)
		{
			min = temp;
			answerCnt = i;
		}
	}
//	cout << endl;
	cout <<"answer : "<< answerCnt;
	if (answerCnt != 0)
		for (int i = 1; i <= answerCnt; i++)
			cout << " " << minChange[i][0] << " " << minChange[i][1];
//	cout<<RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
//    cout<<RiskofLine(start, changePoint, lenResidual, risk_x, risk_y, radius, risk, risk_num)<<"\n";
//    start[0] = 4;
//    start[1] = 5;
//    changePoint[0] = 4;
//    changePoint[1] = 5;
//    cout<<RiskofLine(start, changePoint, lenResidual, risk_x, risk_y, radius, risk, risk_num)<<"\n";
//    cout<<RiskofLine(changePoint, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    
    releaseMemory(risk_x, risk_y, radius, risk);
    
    clock_t b = clock();
    cout << "\nTime cost : " << static_cast<double>(b - a) / CLOCKS_PER_SEC;
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
//	cout <<"\n "<<"("<<startPoint[0]<<","<<startPoint[1]<<")"<<" to "<<"(" <<changePoint[0] << "," << changePoint[1] << ") :\n";
    double risk_sum = 0;
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    int PointCnt = (LineDistance + lenResidual[turnCnt]);
    if(countChange)
        PointCnt--;
   // if (PointCnt < 0)
    //	PointCnt = 0;
    
    double** RiskPointOfLine = new double* [PointCnt];
    for(int i = 0 ; i < PointCnt ; i++)
        RiskPointOfLine[i] = new double[2];
    
    for(int i = 0 ; i <= PointCnt - 1 ; i++)
    {
        RiskPointOfLine[i][0] = startPoint[0] + ( (i + 1 - lenResidual[turnCnt]) / LineDistance) * ( changePoint[0] - startPoint[0] );
        RiskPointOfLine[i][1] = startPoint[1] + ( (i + 1 - lenResidual[turnCnt]) / LineDistance) * ( changePoint[1] - startPoint[1] );
        //cout<<"  "<<RiskPointOfLine[i][0]<<" "<<RiskPointOfLine[i][1]<<"\n";
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
    
    //turnCnt++;
    //lenResidual[turnCnt] = LineDistance - PointCnt;
    
    return risk_sum;
}

//void findChange(start, endP, fuelResidual, changePoint)
//{
//	
//}

void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}
