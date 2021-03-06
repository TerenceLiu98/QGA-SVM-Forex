//+------------------------------------------------------------------+
//|                                                   ZMQ Server.mq4 |
//|                                      Copyright 2020, Terence Lau |
//|                                   https://github.com/TerenceLiu98|
//|                              reference:https://github.com/koswag |
//+------------------------------------------------------------------+
#property copyright   "2020, Terence Lau"
#property link        "https://github.com/TerenceLiu98"
#property description "ZMQ server for MT4(EA)"
#property version     "0.0.1"

#include <Zmq/Zmq.mqh>

extern string  PROJECT_NAME = "MetaTrader 4 ZMQ Server";
extern string  ZEROMQ_PROTOCOL = "tcp";
extern string  HOSTNAME  = "*";
extern int     IN_PORT = 1111;
extern int     OUT_PORT = 2222;
extern int     MILLISECOND_TIMER = 100;

extern string  t0                = "--- Trading Parameters ---";
extern int     MagicNumber       = 123456;
extern int     MaximumOrders     = 1;
extern double  MaximumLotSize    = 0.01;
extern bool    Blocking          = false;
extern int     Slippage          = 3;

Context  context     (PROJECT_NAME);
Socket   PullSocket  (context, ZMQ_PULL);
Socket   PushSocket  (context, ZMQ_PUSH);

int      Ticket;
double   StopLossLevel, TakeProfitLevel;

ZmqMsg   request;
string   operation;

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
{
    EventSetMillisecondTimer(MILLISECOND_TIMER);
      
    Print(StringFormat("[REP] Binding MT4 Server to Socket on Port %d..", IN_PORT));   
    PullSocket.bind(StringFormat("%s://%s:%d", ZEROMQ_PROTOCOL, HOSTNAME, IN_PORT));

    Print(StringFormat("[PUSH] Binding MT4 Server to Socket on Port %d..", OUT_PORT));
    PushSocket.bind(StringFormat("%s://%s:%d", ZEROMQ_PROTOCOL, HOSTNAME, OUT_PORT));
      
    //How long the thread will try to send messages after its socket has been closed
    PullSocket.setLinger(1000);  // 1000 milliseconds

    //How many messages do we want to buffer before closing the socket:
    PullSocket.setSendHighWaterMark(5);     // Up to 5 messages.
      
    return(INIT_SUCCEEDED);
}
  
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
{
  Print(StringFormat("[REP] Unbinding MT4 Server from Socket on Port %d..", IN_PORT));
  PullSocket.unbind(StringFormat("%s://%s:%d", ZEROMQ_PROTOCOL, HOSTNAME, IN_PORT));

  Print(StringFormat("[PUSH] Unbinding MT4 Server from Socket on Port %d..", OUT_PORT));
  PushSocket.unbind(StringFormat("%s://%s:%d", ZEROMQ_PROTOCOL, HOSTNAME, OUT_PORT));
}

//+------------------------------------------------------------------+
//| Expert timer function                                            |
//+------------------------------------------------------------------+
void OnTimer()
{
  PullSocket.recv(request, true);
  
  if(request.size() > 0)
    MessageHandler(request);
}

//+------------------------------------------------------------------+

void MessageHandler(ZmqMsg &req) 
{
  string msg, components[];
  
  msg = GetMessage(req);

  Print(StringFormat("Message received : %s", msg));

  ParseZmqMessage(msg, components);
  InterpretZmqMessage(PushSocket, components);
}


string GetMessage(ZmqMsg& message)
{
  uchar bytes[];

  ArrayResize(bytes, message.size());
  message.getData(bytes);
  return CharArrayToString(bytes);
}

// Interpret Zmq Message and perform actions
void InterpretZmqMessage(Socket& pSocket, string& compArray[])
{
/*   
      compArray[0] = TRADE or RATES
      If RATES -> compArray[1] = Symbol

      If TRADE ->
         compArray[0] = TRADE
         compArray[1] = ACTION (e.g. OPEN, MODIFY, CLOSE)
         compArray[2] = Order_type (e.g. OP_BUY, OP_SELL, etc - only used when ACTION=OPEN)

         // ORDER TYPES: 
         // https://docs.mql4.com/constants/tradingconstants/orderproperties

         // OP_BUY = 0
         // OP_SELL = 1
         // OP_BUYLIMIT = 2
         // OP_SELLLIMIT = 3
         // OP_BUYSTOP = 4
         // OP_SELLSTOP = 5

         compArray[3] = Symbol (e.g. EURUSD, etc.)
         compArray[4] = Open/Close Price (ignored if ACTION = MODIFY)
         compArray[5] = SL
         compArray[6] = TP
         compArray[7] = Trade Comment
*/
  Print("ZMQ: Interpreting Message..");
   
  int switch_action = 0;
  
  if(compArray[0] == "TRADE" && compArray[1] == "OPEN")
      switch_action = 1;
  if(compArray[0] == "RATES")
      switch_action = 2;
  if(compArray[0] == "TRADE" && compArray[1] == "CLOSE")
      switch_action = 3;
  if(compArray[0] == "DATA")
      switch_action = 4;
  if(compArray[0] == "GetDATA")
      switch_action == 5;
   
  string response = "";

  double barData[4], value = NULL;
  bool orderClosed = false;
  int OP, clr = clrNONE;
  
  switch(switch_action)
  {
    case 1: 
      Send("OPEN TRADE Instruction Received");

      OP = StrToInteger(compArray[2]);
         
      if(OP == 0)
      {
        operation = "BUY";
        StopLossLevel = Ask - StrToDouble(compArray[5]) * Point;
        TakeProfitLevel = Ask + StrToDouble(compArray[6]) * Point;
        value = Ask;
        clr = clrGreen;
        
      }
      else if(OP == 1)
      {
        operation = "SELL";
        StopLossLevel = Bid + StrToDouble(compArray[5]) * Point;
        TakeProfitLevel = Bid - StrToDouble(compArray[6]) * Point;
        value = Bid;
        clr = clrDarkCyan;
      }

      Ticket = OrderSend(Symbol(), StrToInteger(compArray[2]), 0.1, 
                                    StrToDouble(compArray[4]), StrToInteger(compArray[5]), StrToInteger(compArray[6]), 
                                    123456); 

    case 2: 
      response = "N/A";

      if(ArraySize(compArray) > 1) 
        response = GetBidAsk(compArray[1]); 

      break;

    case 3:
      Send("CLOSE TRADE Instruction Received");
         
      OP = StrToInteger(compArray[2]);
      Ticket = StrToInteger(compArray[8]);
         
      if(OP == 0)
      {
        value = Bid;
        clr = clrRed;
      } 
      else if(OP == 1)
      {
        value = Ask;
        clr = clrOrange;
      }

      if(OrderSelect(Ticket, SELECT_BY_TICKET, MODE_TRADES))
        orderClosed = OrderClose(OrderTicket(), OrderLots(), value, Slippage, clr);  

      if(orderClosed)
        response = StringFormat("Trade Closed (Ticket: %d)", Ticket);
      else
        response = StringFormat("Error : %s", GetLastError());

      break;

    case 4:
      Send("DATA Instruction Received");      
      FillBarData(barData, compArray[1]);   
      response = StringFormat("|O: %.4f| H: %.4f|L: %.4f|C: %.4f|", barData[0], barData[1], barData[2], barData[3]);
         
      break;
      
    case 5:
      Send("Collecting Data");
      // TO-DO
  }
  
  Print("Sending: " + response);
  Send(response);
}


// Message parser
void ParseZmqMessage(string message, string &retArray[])
{
  Print("Parsing: " + message);
   
  string sep = "|";
  ushort u_sep = StringGetCharacter(sep,0);
   
  int splits = StringSplit(message, u_sep, retArray);
   
  for(int i = 0; i < splits; i++)
    Print(StringFormat("%d) %s", i, retArray[i]));
}

//+------------------------------------------------------------------+

// Generate string for Bid/Ask by symbol
string GetBidAsk(string symbol) 
{   
  double bid = MarketInfo(symbol, MODE_BID);
  double ask = MarketInfo(symbol, MODE_ASK);
   
  return(StringFormat("%f|%f", bid, ask));
}


//Gets latest bar data
void FillBarData(double &barData[], string symbol)
{
  barData[0] = iOpen(symbol, PERIOD_H1, 0);
  barData[1] = iClose(symbol, PERIOD_H1, 0);
  barData[2] = iHigh(symbol, PERIOD_H1, 0);
  barData[3] = iLow(symbol, PERIOD_H1, 0);
}

//Sends string message to client
void Send(string message) 
{
  if(message != "" || message != NULL){
    ZmqMsg pushReply(StringFormat("[SERVER] : %s", message));
   
    Print(StringFormat("Sending message : %s", message));
    PushSocket.send(pushReply, true);
  }
}