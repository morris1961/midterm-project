//
//  main.cpp
//  彥錞版本
//
//  Created by 張宇承 on 2018/11/30.
//  Copyright © 2018 張宇承. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

void putData(int x[], int num);
void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[]);

double Distance (double x1, double y1, double x2, double y2);
double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num);
double RiskofLine(int startPoint[2],int changePoint[2],double lenResidual[],int risk_x[],int risk_y[],int radius[],int risk[],int risk_num);
void FindResidual( int startPoint[] , int changePoint[] , double residual[] );
int turnCnt = 1;
int main()
{
    //clock_t a = clock();
    int n = 0, risk_num = 0, turn_weight = 0, start[2] = {0} , endP[2] = {0};
    double dis_limit, min = 99999;
    double lenResidual[100] = {0};
    int turnPoints[2][2] = {0};
    
    cin >> n >> risk_num >> turn_weight >> dis_limit;
    
    if (risk_num > 5000) // 10
        n = 10;
    else if(risk_num > 2500) //8
        n = 10;
    else if(risk_num > 1250) //2
        n = 50;
    else if(risk_num > 625) //1
        n = 1000;
    else if(risk_num > 313) //1
        n = 2000;
    
    
    
    int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];
    putData (risk_x, risk_num);
    putData (risk_y, risk_num);
    putData (radius, risk_num);
    putData (risk, risk_num);
    putData (start, 2);
    putData (endP, 2);
    
    min = RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    
    int mid[2];
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
    
    mid[0] = (max_x + min_x) / 2;
    mid[1] = (max_y + min_y) / 2;
    int sToMid_xDis = (max_x - min_x) / 2;
    int sToMid_yDis = (max_y - min_y) / 2;
    
    srand(time(nullptr));
    int** random1 = new int*[n];
    for(int i = 0; i < n; i++)
        random1[i] = new int[2];
    for(int i = 0; i < n; i++)
    {
        random1[i][0] = (rand() % sToMid_xDis) + min_x;
        random1[i][1] = (rand() % sToMid_yDis) + min_y;
        // cout << random1[i][0] << " " << random1[i][1] << endl;
    }
    //cout << endl;
    
    //    for(int i = 0 ; i < risk_num ; i++)
    //        for(int j = 0 ; j < n ; j++)
    //            if(Distance(random1[j][0], random1[j][1], risk_x[i], risk_y[i]) < radius[i] )
    //            {
    //
    //            }
    
    int changex = 0, changey = 0;
    double minCost = min;
    for(int i = 0; i < n; i++)
    {
        
        if(Distance(random1[i][0], random1[i][1], start[0], start[1]) +  Distance(random1[i][0], random1[i][1], endP[0], endP[1])< dis_limit)
        {
            double tmpCost = RiskofLine(start, random1[i], lenResidual, risk_x, risk_y, radius, risk, risk_num);
            tmpCost += RiskofLine(random1[i], endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
            if(tmpCost + turn_weight  < minCost)
            {
                minCost = tmpCost;
                changex = random1[i][0];
                changey = random1[i][1];
            }
        }
    }
    bool first = 0;
    if(minCost == min)
        turnCnt = 0;
    else
    {
        turnPoints[0][0] = changex;
        turnPoints[0][1] = changey;
        first = 1;
        FindResidual( start , turnPoints[0] , lenResidual );
        dis_limit -= Distance(turnPoints[0][0], turnPoints[0][1], start[0], start[1]);
        start[0] = turnPoints[0][0];
        start[1] = turnPoints[0][1];
        //  cout << turnPoints[0][0] << " " << turnPoints[0][1] << " " << minCost << endl;
    }
    
    
    //cout << min;
    
    
    srand(time(nullptr));
    int** random2 = new int*[n];
    for(int i = 0; i < n; i++)
        random2[i] = new int[2];
    for(int i = 0; i < n; i++)
    {
        random2[i][0] = (rand() % sToMid_xDis) + mid[0]; //修正
        random2[i][1] = (rand() % sToMid_yDis) + mid[1]; //修正
        // cout << random2[i][0] << " " << random2[i][1] << endl;
    }
    // cout << endl;
    
    /*if(first == 1)
     turnCnt = 2;
     else
     turnCnt = 1;*/
    
    minCost = RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    for(int i = 0; i < n; i++)
    {
        
        // cout << "tmp" << tmpCost << " " << minCost;
        if(Distance(random2[i][0], random2[i][1], start[0], start[1]) +  Distance(random2[i][0], random2[i][1], endP[0], endP[1]) < dis_limit)
        {
            
            double tmpCost = RiskofLine(start, random2[i], lenResidual, risk_x, risk_y, radius, risk, risk_num);
            tmpCost += RiskofLine(random2[i], endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
            
            if(tmpCost + turn_weight < minCost)
            {
                minCost = tmpCost;
                changex = random2[i][0];
                changey = random2[i][1];
                if(first == 1)
                    turnCnt = 2;
                else
                    turnCnt = 1;
            }
        }
    }
    
    //  cout << turnCnt << ":";
    if(minCost == min)
        turnCnt = 0;
    else if(turnCnt == 1)
    {
        turnPoints[0][0] = changex;
        turnPoints[0][1] = changey;
        // cout << turnPoints[turnCnt - 1][0] << " " << turnPoints[turnCnt - 1][1] << endl;
    }
    else
    {
        turnPoints[1][0] = changex;
        turnPoints[1][1] = changey;
    }
    
    
    //cout << turnPoints[0][0] << " " << turnPoints[0][1] << endl;
    // cout << turnPoints[1][0] << " " << turnPoints[1][1] << " " << minCost << endl;
    
    cout << turnCnt;
    
    if(turnCnt != 0)
        for(int i = 0; i < turnCnt; i++)
            cout << " " << turnPoints[i][0] << " " << turnPoints[i][1] ;
    // cout << " " << minCost;
    
    // clock_t b = clock();
    //cout << "\nTime cost : " << static_cast<double>(b - a) / CLOCKS_PER_SEC;
    for(int i = 0; i < n; i++)
        delete[] random1[i], random2[i];
    delete [] random1, random2;
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

void FindResidual( int startPoint[] , int changePoint[] , double residual[] )
{
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    
    int PointCnt = 0;
    PointCnt = (LineDistance + residual[turnCnt]);
    
    turnCnt++;
    residual[turnCnt] = LineDistance - PointCnt;
    
}



double RiskofPoint(double point[], int risk_x[], int risk_y[], int radius[], int risk[], int risk_num)
{
    double risk_sum = 0;
    for (int k = 0; k < risk_num; k++)
    {
        if(Distance(point[0], point[1], risk_x[k], risk_y[k]) < radius[k] )
        {
            double temp = risk[k] * (radius[k] -Distance(risk_x[k], risk_y[k], point[0], point[1])) / radius[k];
            risk_sum += temp;
        }
    }
    return risk_sum;
}

double RiskofLine(int startPoint[], int changePoint[] ,double lenResidual[] ,int risk_x[] , int risk_y[] , int radius[] , int risk[] , int risk_num )
{
    //    cout <<"\n "<<"("<<startPoint[0]<<","<<startPoint[1]<<")"<<" to "<<"(" <<changePoint[0] << "," << changePoint[1] << ") :\n";
    double risk_sum = 0;
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    int PointCnt = (LineDistance + lenResidual[turnCnt]);
    //if(countChange)
    //PointCnt--;
    // if (PointCnt < 0)
    //    PointCnt = 0;
    
    double** RiskPointOfLine = new double* [PointCnt];
    for(int i = 0 ; i < PointCnt ; i++)
        RiskPointOfLine[i] = new double[2];
    
    for(int i = 0 ; i <= PointCnt - 1 ; i++)
    {
        RiskPointOfLine[i][0] = startPoint[0] + ( (i + 1 - lenResidual[turnCnt]) / (LineDistance ) * ( changePoint[0] - startPoint[0] ));
        RiskPointOfLine[i][1] = startPoint[1] + ( (i + 1 - lenResidual[turnCnt]) / (LineDistance ) * ( changePoint[1] - startPoint[1] ));
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
    
    return risk_sum;
}

void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}
