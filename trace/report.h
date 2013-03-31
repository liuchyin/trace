//
//  report.h
//  trace
//
//  Created by Cong on 13-3-9.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <iostream>
#include <fstream>
#include "reader.h"
#include "simulator.h"
#include <string>

using namespace std;

class Report{
private:
    int Message;
    int step;
    Report(){}
public:
    Report(int Message, int step) : Message(Message), step(step){};
    
    void runSimulator(Reader& reader, Simulator& simulator){
        string dir = "../../report/" + reader.getName();

        string path1 = dir + "-delay.txt";
        string path2 = dir + "-delivery.txt";
        string path3 = dir + "-forwarding.txt";
        
		ofstream outfile_delay(path1);
		ofstream outfile_delivery(path2);
		ofstream outfile_forwarding(path3);

		if(!outfile_delay || !outfile_delivery || !outfile_forwarding){
			cout<<"outfile error!";
			return;
		}
        
        long totalTime = reader.getMaxTime() - reader.getMinTime();
        Message::TTL = 0;
        long stepTTL = totalTime / step;
        
        //run statistics
        int protocols = simulator.getProtocols();
        double **delay = new double*[protocols];
        double **delivery = new double*[protocols];
        double **forwarding = new double*[protocols];
        for(int i = 0; i != protocols; ++i){
            delay[i] = new double[step];
            delivery[i] = new double[step];
            forwarding[i] = new double[step];
        }
        
        for(int i = 0; i != step; ++i){
            Message::TTL += stepTTL;
            simulator.start(reader, Message);

            double* delays = simulator.getDelay();
            double* deliveries = simulator.getDelivery();
            double* forwardings = simulator.getForwarding();
            for(int j = 0; j != protocols; j++){
                delay[j][i] = delays[j];
                delivery[j][i] = deliveries[j];
                forwarding[j][i] = forwardings[j];
                //outfile_delay<<delays[j]<<'\t';
                //outfile_delivery<<deliveries[j]<<'\t';
                //outfile_forwarding<<forwardings[j]<<'\t';
            }
            delete delays;
            delete deliveries;
            delete forwardings;
            //outfile_delay<<endl;
            //outfile_delivery<<endl;
            //outfile_forwarding<<endl;
        }
        
        for(int i = 0; i != protocols; ++i){
            for(int j = 0; j != step; ++j){
                outfile_delay<<delay[i][j]<<" ";
                outfile_delivery<<delivery[i][j]<<" ";
                outfile_forwarding<<forwarding[i][j]<<" ";
            }
            outfile_delay<<endl;
            outfile_delivery<<endl;
            outfile_forwarding<<endl;
        }
        delete []delay;
        delete []delivery;
        delete []forwarding;
        outfile_delay.close();
        outfile_delivery.close();
        outfile_forwarding.close();

        
    }

};