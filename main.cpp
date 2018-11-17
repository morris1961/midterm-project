//
//  main.cpp
//  Midtern
//
//  Created by 張宇承 on 2018/11/17.
//  Copyright © 2018年 張宇承. All rights reserved.


#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double Distance (double x1, double y1, double x2, double y2);
double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num); //尋找風險點並計算風險
double RiskofLine(int startPoint[2],int changePoint[2],double residual[],int risk_x[],int risk_y[],int radius[],int risk[],int risk_num);
//將風險點的風險加起來成一條風險線
double RiskofRoute;//將風險線的風險加起來成一個路徑

void putData(int x[], int num);
void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[]);

int turnCnt = 0;
int main ()
{
    int n = 0, risk_num = 0, turn_weight = 0, dis_limit = 0, start[2] = {0} , end[2] = {0};
    cin >> n >> risk_num >> turn_weight >> dis_limit;
    int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];
    double residual[100] = {0};
    int changepoint[2] = {0};
    putData (risk_x, risk_num);
    putData (risk_y, risk_num);
    putData (radius, risk_num);
    putData (risk, risk_num);
    for(int i = 0 ; i < 2 ; i++)
    {
        cin>>start[i];
    }
    for(int i = 0 ; i < 2 ; i++)
    {
        cin>>changepoint[i];
    }
    for(int i = 0 ; i < 2 ; i++)
    {
        cin>>end[i];
    }
    
    cout<<RiskofLine(start, changepoint, residual, risk_x, risk_y, radius, risk, risk_num)<<"\n";
    cout<<RiskofLine(changepoint, end, residual, risk_x, risk_y, radius, risk, risk_num);
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

double RiskofLine(int startPoint[], int changePoint[] ,double residual[] ,int risk_x[] , int risk_y[] , int radius[] , int risk[] , int risk_num )
{
    double risk_sum = 0;
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    //尋找線段上要判斷風險的風險點：
    int PointCnt = 0;
    PointCnt = (LineDistance + residual[turnCnt]);
    if(LineDistance + residual[turnCnt] == static_cast<int>(LineDistance + residual[turnCnt]))
        PointCnt-- ;
    
    double** RiskPointOfLine = new double* [PointCnt]; //建立PointCnt個風險點二維陣列
    for(int i = 0 ; i < PointCnt ; i++)
        RiskPointOfLine[i] = new double[2]; //存x,y座標
    
    RiskPointOfLine[0][0] = startPoint[0] + ((1-residual[turnCnt])/LineDistance) * ( changePoint[0] - startPoint[0] );
    RiskPointOfLine[0][1] = startPoint[1] + ((1-residual[turnCnt])/LineDistance) * ( changePoint[1] - startPoint[1] );
    cout<<RiskPointOfLine[0][0]<<" "<<RiskPointOfLine[0][1]<<"\n";
    for(int i = 1 ; i <= PointCnt - 1 ; i++)
    {
        RiskPointOfLine[i][0] = startPoint[0] + ((i+1-residual[turnCnt])/LineDistance) * ( changePoint[0] - startPoint[0] );
        RiskPointOfLine[i][1] = startPoint[1] + ((i+1-residual[turnCnt])/LineDistance) * ( changePoint[1] - startPoint[1] );
        cout<<RiskPointOfLine[i][0]<<" "<<RiskPointOfLine[i][1]<<"\n";
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
    residual[turnCnt] = LineDistance - PointCnt;
    return risk_sum;
}




void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}
