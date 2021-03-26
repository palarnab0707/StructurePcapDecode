# StructurePcapDecode
Problem Statement:

Generate string interpretation of tick data in a text file from a source pcap file. usage:
tcp2txt <source> <target>

pcap file contains date packets received from exchange. Only the following types of messages, should be written to text file:
MsgType = "M", "N", "X" for ORDER_MESSAGE
MsgType = "T" for TRADE_MESSAGE

        #pragma pack(push)
        #pragma pack(1)
        typedef struct STREAM_HEADER
        {
                short msg_len __attribute__((packed));
                short stream_id __attribute__((packed));
                int seq_no __attribute__((packed));
        }STREAM_HEADER;
        #pragma pack(pop)


        #pragma pack(push)
        #pragma pack(1)
        typedef struct ORDER_MESSAGE
        {
                STREAM_HEADER GHeader;
                char MsgType __attribute__((packed));
                int64_t TimeStamp __attribute__((packed));
                double OrderId __attribute__((packed));
                int Token __attribute__((packed));
                char OrderType __attribute__((packed));
                int Price __attribute__((packed));
                int Quantity __attribute__((packed));

                void   ToString(stringstream& buff);

        }ORDER_MESSAGE;
        #pragma pack(pop)

        #pragma pack(push)
        #pragma pack(1)
        typedef struct TRADE_MESSAGE
        {
                STREAM_HEADER GHeader;
                char MsgType __attribute__((packed));
                int64_t TimeStamp __attribute__((packed));
                double BuyOrderId __attribute__((packed));
                double SellOrderId __attribute__((packed));
                int Token __attribute__((packed));
                int TradePrice __attribute__((packed));
                int TradeQuantity __attribute__((packed));

                void ToString( stringstream& buff);


        }TRADE_MESSAGE;
        #pragma pack(pop)
        
        So i send the packets taking the values from a file in the manner of given structure. Then i decode the pcap file and save the tick datas in a text file.
