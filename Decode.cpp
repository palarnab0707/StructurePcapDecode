#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <pcap.h>
#include <stdio.h>
#include <string.h>
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

int main()
{
    struct ORDER_MESSAGE M;
    struct TRADE_MESSAGE T;
    string file = "t.pcap";
    int hdrlen=42;
    char str;
    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_offline(file.c_str(), errbuff);
    struct pcap_pkthdr *header;
    const u_char *data;
    u_int packetCount = 0;
    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
        printf("Packet # %i\n", ++packetCount);
        printf("Packet size: %d bytes\n", header->len);
        memcpy(&str,data+hdrlen+sizeof(STREAM_HEADER), sizeof(char));
        cout<<str<<endl;
        if(str=='M' || str=='N' || str=='X')
        {
                memcpy(&M,data+hdrlen ,sizeof(M));
                cout<<"Order"<<endl;
                cout<<"Stream Header"<<endl;
                cout<<M.GHeader.msg_len<<" "<<M.GHeader.stream_id<<" "<<M.GHeader.seq_no<<endl;
                cout<<"Order Message"<<endl;
                cout<<M.MsgType<<" "<<M.TimeStamp<<" "<<M.OrderId<<" "<<M.Token<<" "<<M.OrderType<<" "<<M.Price<<" "<<M.Quantity<<endl;
        }
        if(str=='T')
        {
                memcpy(&T,data+hdrlen,sizeof(T));
                cout<<"Trade"<<endl;
                cout<<"Stream Header"<<endl;
                cout<<T.GHeader.msg_len<<" "<<T.GHeader.stream_id<<" "<<T.GHeader.seq_no<<endl;
                cout<<"Trade Message"<<endl;
                cout<<T.MsgType<<" "<<T.TimeStamp<<" "<<T.BuyOrderId<<" "<<T.SellOrderId<<" "<<T.token<<" "<<T.TradePrice<<" "<<T.TradeQuantity<<endl;
         }
    }
}
