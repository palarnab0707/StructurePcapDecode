#include<iostream>
#include<time.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <vector>
#include <sstream>
#include<netinet/in.h>
#include<string.h>
#include<fstream>
#include<cstdio>
using namespace std;
struct STREAM_HEADER{
        short int msg_len;
        short int stream_id;
        int seq_no;
        }__attribute__((packed));
struct ORDER_MESSAGE{
        STREAM_HEADER GHeader;
        char MsgType;
        int64_t TimeStamp;
        double OrderId;
        int Token;
        char OrderType;
        int Price;
        int Quantity;
        }__attribute__((packed));
struct TRADE_MESSAGE{
        STREAM_HEADER GHeader;
        char MsgType;
        int64_t TimeStamp;
        double BuyOrderId;
        double SellOrderId;
        int token;
        int TradePrice;
        int TradeQuantity;
}__attribute__((packed));
void token(string const &str, const char delim,vector<string> &tokens)
{
   int i=0;
    stringstream ss(str);

    string s;

    while (getline(ss, s, delim)) {
        tokens.push_back(s);
        i++;

    }
}

int main()
{

        int server,port2,n,n1;
        socklen_t len;
        string str;
        ifstream File("input.txt");
        char *send;
        cout<<"Enter the port"<<endl;
        cin>>port2;
        server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(server<0)
        {
                cout<<"Socket creation error";
        }
        struct sockaddr_in serv_addr;
        struct sockaddr_in client;
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_port=htons(port2);
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        int c=bind(server,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        if(c<0)
        {
                cout<<"Binding failed";
        }
        len=sizeof(serv_addr);

        struct STREAM_HEADER S;
        struct ORDER_MESSAGE O;
        struct TRADE_MESSAGE T;
        string line;
        while( getline(File,line))
        {
                vector<string> word;
                token(line , ',' ,word);

                if(word[0].compare("M")==0 || word[0].compare("X")==0 || word[0].compare("N")==0 )
                {
                        O.GHeader.msg_len=atoi(word[1].c_str());
                        O.GHeader.stream_id=atoi(word[2].c_str());
                        O.GHeader.seq_no=atoi(word[3].c_str());
                        O.MsgType=word[0][0];
                        O.TimeStamp=atoi(word[4].c_str());
                        O.OrderId=atof(word[5].c_str());
                        O.Token=atoi(word[6].c_str());
                        O.OrderType=word[7][0];
                        O.Price=atoi(word[8].c_str());
                        O.Quantity=atoi(word[9].c_str());
                        send=new char[sizeof(ORDER_MESSAGE)];
                        memcpy(send , &O , sizeof(O));
                        sendto(server,send,sizeof(O),0,(struct sockaddr *)&serv_addr,len);

                }
                if(word[0].compare("T")==0)
                {
                        T.GHeader.msg_len=atoi(word[1].c_str());
                        T.GHeader.stream_id=atoi(word[2].c_str());
                        T.GHeader.seq_no=atoi(word[3].c_str());
                        T.MsgType=word[0][0];
                        T.TimeStamp=atoi(word[4].c_str());
                        T.BuyOrderId=atof(word[5].c_str());
                        T.SellOrderId=atof(word[6].c_str());
                        T.token=atoi(word[7].c_str());
                        T.TradePrice=atoi(word[8].c_str());
                        T.TradeQuantity=atoi(word[9].c_str());
                        send=new char[sizeof(T)];
                        memcpy(send , &T , sizeof(T));
                        sendto(server,send,sizeof(T),0,(struct sockaddr *)&serv_addr,len);
                }
                word.empty();
        }
        close(server);
        return 0;
}
