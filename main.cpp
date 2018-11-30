//
//  main.cpp
//  MidtermA+
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

const int k_limit = 30, e_limit = 175;
int turnCnt = 1;
int main()
{
    //    clock_t a = clock();
    int n = 0, risk_num = 0, turn_weight = 0, start[2] = {0} , endP[2] = {0}, range = 0;
    double dis_limit;
    double lenResidual[2] = {0}, minCost = 0;
    int turnPoints[100][2] = {0};
    
    cin >> n >> risk_num >> turn_weight >> dis_limit;
    
    int *risk_x = new int[risk_num], *risk_y = new int[risk_num] , *radius = new int [risk_num], *risk = new int [risk_num];
    putData (risk_x, risk_num);
    putData (risk_y, risk_num);
    putData (radius, risk_num);
    putData (risk, risk_num);
    putData (start, 2);
    putData (endP, 2);
    
    minCost = RiskofLine(start, endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
    //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ") :" << minCost << "\n";
    srand(time(nullptr));
    int k = 0, turnCnt = 1;
    for (int k = 0; k < k_limit; k++)
    {
        int e = 0, mode = 0;
        if (turnCnt == 1)
            mode = 1;
        else if (turnCnt == 2)
            mode = (rand() % 2) + 1;
        else
            mode = (rand() % 3) + 1;
        //cout << mode << " :\n";
        
        if (mode == 1)
        {
            int TP[2]; // temp point
            double temp = minCost;
            while (e < e_limit)
            {
                turnPoints[turnCnt][0] = static_cast <double>(rand()) / RAND_MAX * n;
                turnPoints[turnCnt][1] = static_cast <double>(rand()) / RAND_MAX * n;
                //cout<<turnPoints[turnCnt][0]<<" "<<turnPoints[turnCnt][1]<<"\n";
                double Dis = Distance (turnPoints[1][0], turnPoints[1][1], start[0], start[1]);
                for (int i = 1; i < turnCnt; i++)
                {
                    Dis += Distance (turnPoints[i][0], turnPoints[i][1], turnPoints[i+1][0], turnPoints[i+1][1]);
                }
                Dis += Distance (turnPoints[turnCnt][0], turnPoints[turnCnt][1], endP[0], endP[1]);
                //cout << Dis <<"\n";
                if (Dis > dis_limit)
                {
                    e++;
                    continue;
                }
                
                //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") + ";
                lenResidual[0] = 0;
                double tempCost = RiskofLine(start, turnPoints[1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                for (int i = 1; i < turnCnt; i++)
                {
                    //cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") + ";
                    tempCost += RiskofLine(turnPoints[i], turnPoints[i + 1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                }
                //cout << "(" <<turnPoints[turnCnt][0] << "," << turnPoints[turnCnt][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ") : ";
                tempCost += RiskofLine(turnPoints[turnCnt], endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
                tempCost += turnCnt * turn_weight;
                //cout << tempCost << endl;
                
                if(minCost > tempCost)
                {
                    minCost = tempCost;
                    TP[0] = turnPoints[turnCnt][0];
                    TP[1] = turnPoints[turnCnt][1];
                }
                e++;
            }
            //cout << minCost << "\n";
            if (minCost != temp)
            {
                turnPoints[turnCnt][0] = TP[0];
                turnPoints[turnCnt][1] = TP[1];
                turnCnt++;
            }
            
            //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") +";
            //            for (int i = 1; i < turnCnt-1; i++)
            //            {
            //                //cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") +";
            //            }
            //cout << "(" <<turnPoints[turnCnt-1][0] << "," << turnPoints[turnCnt-1][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ")\n";
        }
        
        else if (mode == 2)
        {
            int CTP = (rand() % (turnCnt - 1)) + 1; //change turn point
            int TP[2][2]; // temp point
            double temp = minCost;
            TP[1][0] = turnPoints[CTP][0];
            TP[1][1] = turnPoints[CTP][1];
            while (e < e_limit)
            {
                turnPoints[CTP][0] = static_cast <double>(rand()) / RAND_MAX * n;
                turnPoints[CTP][1] = static_cast <double>(rand()) / RAND_MAX * n;
                double Dis = Distance (turnPoints[1][0], turnPoints[1][1], start[0], start[1]);
                for (int i = 1; i < turnCnt-1; i++)
                {
                    Dis += Distance (turnPoints[i][0], turnPoints[i][1], turnPoints[i+1][0], turnPoints[i+1][1]);
                }
                Dis += Distance (turnPoints[turnCnt-1][0], turnPoints[turnCnt-1][1], endP[0], endP[1]);
                //cout << Dis <<"\n";
                if (Dis > dis_limit)
                {
                    e++;
                    continue;
                }
                
                //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") + ";
                lenResidual[0] = 0;
                double tempCost = RiskofLine(start, turnPoints[1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                for (int i = 1; i < turnCnt-1; i++)
                {
                    //cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") + ";
                    tempCost += RiskofLine(turnPoints[i], turnPoints[i + 1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                }
                //cout << "(" <<turnPoints[turnCnt-1][0] << "," << turnPoints[turnCnt-1][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ") : ";
                tempCost += RiskofLine(turnPoints[turnCnt-1], endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
                tempCost += (turnCnt-1) * turn_weight;
                //cout << tempCost << endl;
                
                if(minCost > tempCost)
                {
                    minCost = tempCost;
                    TP[0][0] = turnPoints[CTP][0];
                    TP[0][1] = turnPoints[CTP][1];
                }
                e++;
            }
            
            //cout << minCost << "\n";
            if (minCost != temp)
            {
                turnPoints[CTP][0] = TP[0][0];
                turnPoints[CTP][1] = TP[0][1];
            }
            else
            {
                turnPoints[CTP][0] = TP[1][0];
                turnPoints[CTP][1] = TP[1][1];
            }
            
            //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") + ";
            //            for (int i = 1; i < turnCnt-1; i++)
            //            {
            //                //cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") + ";
            //            }
            //cout << "(" <<turnPoints[turnCnt-1][0] << "," << turnPoints[turnCnt-1][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ")\n";
        }
        
                else if (mode == 3)
                {
                    while (e < e_limit)
                    {
                        if (turnCnt <= 2)
                            break;
                        int ETP = (rand() % (turnCnt - 2)) + 1; //eliminate turn point
                        double tempCost = 0, SP = 0;
                        lenResidual[0] = 0;
                        if (ETP == 1)
                        {
//                            cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[2][0] << "," << turnPoints[2][1] << ") + ";
                            tempCost = RiskofLine(start, turnPoints[2], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                            SP = 2;
                        }
                        else
                        {
//                            cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") + ";
                            tempCost = RiskofLine(start, turnPoints[1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                            SP = 1;
                        }
        
        
                        for (int i = SP; i < turnCnt-1; i++)
                        {
                            if (i == ETP)
                            {
                                tempCost += RiskofLine(turnPoints[i-1], turnPoints[i + 1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                                continue;
                            }
//                            cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") + " ;
                            tempCost += RiskofLine(turnPoints[i], turnPoints[i + 1], lenResidual, risk_x, risk_y, radius, risk, risk_num);
                        }
//                        cout << "(" <<turnPoints[turnCnt-1][0] << "," << turnPoints[turnCnt-1][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ") : ";
                        tempCost += RiskofLine(turnPoints[turnCnt-1], endP, lenResidual, risk_x, risk_y, radius, risk, risk_num);
                        tempCost += (turnCnt-2) * turn_weight;
//                        cout << tempCost << endl;
        
                        if(minCost > tempCost)
                        {
                            minCost = tempCost;
                            for (int i = ETP; i < turnCnt-1; i++)
                            {
                                turnPoints[i][0] = turnPoints[i+1][0];
                                turnPoints[i][1] = turnPoints[i+1][1];
                            }
                            turnCnt--;
                        }
                        e++;
                    }
        
                    //cout <<"("<<start[0]<<","<<start[1]<<")"<<" to "<<"(" <<turnPoints[1][0] << "," << turnPoints[1][1] << ") + ";
//                    for (int i = 1; i < turnCnt-1; i++)
//                    {
////                        cout <<"("<<turnPoints[i][0] << "," << turnPoints[i][1]<<")"<<" to "<<"(" <<turnPoints[i+1][0] << "," << turnPoints[i+1][1] << ") + ";
//                    }
//                    cout << "(" <<turnPoints[turnCnt-1][0] << "," << turnPoints[turnCnt-1][1] << ")"<<" to "<<"(" <<endP[0] << "," << endP[1] << ")\n";
//                    cout << minCost << "\n";
                }
    }
    
    cout << turnCnt-1;
    for (int i = 1; i < turnCnt; i++)
    {
        cout << " " << turnPoints[i][0] << " " << turnPoints[i][1];
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
    if (changePoint[0] == startPoint[0] && changePoint[1] == startPoint[1])
        return 0 ;
    //cout << lenResidual[0] << " " << lenResidual[1] <<"\n";
    //cout <<"("<<startPoint[0]<<","<<startPoint[1]<<")"<<" to "<<"(" <<changePoint[0] << "," << changePoint[1] << ") :\n";
    double risk_sum = 0;
    double LineDistance = Distance( startPoint[0], startPoint[1], changePoint[0], changePoint[1]);
    double tempResidual = 0;
    int PointCnt = 0;
    
    PointCnt = LineDistance;
    tempResidual = LineDistance - PointCnt;
    if (lenResidual[0] + tempResidual > 1)
        PointCnt++;
    //cout << lenResidual[0]<<" " << tempResidual <<endl;
    
    double** RiskPointOfLine = new double* [PointCnt];
    for(int i = 0 ; i < PointCnt ; i++)
        RiskPointOfLine[i] = new double[2];
    
    if (changePoint[0] > startPoint[0])
        RiskPointOfLine[0][0] = startPoint[0] + abs( (1 - lenResidual[0]) / (LineDistance ) * ( changePoint[0] - startPoint[0] ));
    else
        RiskPointOfLine[0][0] = startPoint[0] - abs( (1 - lenResidual[0]) / (LineDistance ) * ( changePoint[0] - startPoint[0] ));
    
    if ( changePoint[1] > startPoint[1])
        RiskPointOfLine[0][1] = startPoint[1] + abs( (1 - lenResidual[0]) / (LineDistance ) * ( changePoint[1] - startPoint[1] ));
    else
        RiskPointOfLine[0][1] = startPoint[1] - abs( (1 - lenResidual[0]) / (LineDistance ) * ( changePoint[1] - startPoint[1] ));
    // cout<<RiskPointOfLine[0][0]<<" "<<RiskPointOfLine[0][1]<<"\n";
    for(int i = 1 ; i <= PointCnt - 1 ; i++)
    {
        RiskPointOfLine[i][0] = RiskPointOfLine[0][0] + ( (i) / (LineDistance ) * ( changePoint[0] - startPoint[0] ));
        RiskPointOfLine[i][1] = RiskPointOfLine[0][1] + ( (i) / (LineDistance ) * ( changePoint[1] - startPoint[1] ));
        // cout<<RiskPointOfLine[i][0]<<" "<<RiskPointOfLine[i][1]<<"\n";
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
    
    
    //    lenResidual[0] = lenResidual[1];
    lenResidual[0] += tempResidual;
    if (lenResidual[0] > 1)
        lenResidual[0]--;
    return risk_sum;
}

void releaseMemory(int risk_x[], int risk_y[], int radius[], int risk[])
{
    delete [] risk_x, risk_y, radius, risk;
}

