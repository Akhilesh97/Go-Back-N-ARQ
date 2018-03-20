/*Program :

Write a C/C++/Java/Python program to implement Go Back N ARQ in noisy channel. The sender should send more than one
data frames(within window size) and start a timer for it. If it receives acknowledgment, then it should move its sending
window, reset timer to the first outstanding frame and send next set of frame/frames. If it does not receive acknowledgment
before the timer times out, it should retransmit all the outstanding frames. (i.e frames which have not yet received
acknowledgment). The receiver should send acknowledgment only if it receives the expected frame successfully. It should
discard all other packets which are out of order.

Date: 23-03-2017
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

int globalTime = 0;
int receiverAck;
float percentageEff;
int numberPacketsLost;
int sender[10][4];
int SWPToSend = 0;
int SWPToReceive = 0;
int transmitTime;
int generationTime;
int timeOut;

void generate(int genTime,int packetNo)
{
    if(packetNo<11)cout<<"Packet number "<<packetNo<<" is generated at time = "<<genTime<<endl;

    sender[SWPToSend][0] = packetNo;
    sender[SWPToSend][1] = genTime;
    sender[SWPToSend][2] = 0;
    sender[SWPToSend][3] = 0;

    int randTemp = rand()%100;
    if(randTemp<numberPacketsLost)
    {
        if(packetNo<11)cout<<"This packet will be lost in transit"<<endl<<endl;
        sender[SWPToSend][3] = genTime+timeOut;
    }
    else
    {
        if(packetNo<11)cout<<"This packet will reach safely"<<endl<<endl;
        sender[SWPToSend][2] = genTime+2*transmitTime;
    }

}

void goBack()
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<4; j++)
        {
            sender[i][j] = 0;
        }
    }

    int packetNumber = 1;
    while(true)
    {
        bool timeOutOcc = false;
        if(sender[SWPToReceive][2]<=globalTime+generationTime&&sender[SWPToReceive][2]!=0)
        {
            cout<<"Packet Number "<<sender[SWPToReceive][0]<<" has been acknowledged at time = "<<sender[SWPToReceive][2]<<endl;
            if(sender[SWPToReceive][0]==10)break;
            SWPToReceive = (SWPToReceive+1)%10;

        }
        else if(sender[SWPToReceive][3]<=globalTime+generationTime&&sender[SWPToReceive][3]!=0)
        {
            cout<<"!!!Time out in packet number "<<sender[SWPToReceive][0]<<" has occured at time = "<<sender[SWPToReceive][3]<<"!!!"<<endl;
            SWPToSend = SWPToReceive;
            packetNumber = sender[SWPToReceive][0];
            timeOutOcc = true;
        }

        globalTime = globalTime+generationTime;
        if(timeOutOcc)
        {
            globalTime = sender[SWPToReceive][3];
        }
        if(sender[SWPToReceive][0]==0)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }
        else if(sender[(SWPToSend-1+10)%10][0]<11)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }
    }
}

int main()
{
    cout<<"Enter the times for different network parameters:"<<endl;
    cout<<"Generation Time (ms):";cin>>generationTime;
    cout<<"Transmission Time (ms):";cin>>transmitTime;
    cout<<"TimeOut Time (ms):";cin>>timeOut;cout<<endl;
    cout<<"Enter The percentage efficiency:";cin>>percentageEff;
    numberPacketsLost = 100 -(int)percentageEff;
    cout<<endl<<"Running Go back N"<<endl;
    for(int i = 0; i<30;i++)cout<<"_";
    cout<<endl<<endl;
    goBack();
    system("pause");
    return 0;
}
