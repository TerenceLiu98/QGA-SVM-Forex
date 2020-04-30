//+------------------------------------------------------------------+
//|                                           Download_data_test.mq5 |
//|                                      Copyright 2020, Terence Lau |
//|                                   https://terenceliu98.github.io |
//+------------------------------------------------------------------+
#property copyright "Copyright 2020, Terence Lau"
#property link      "https://terenceliu98.github.io"
#property version   "1.00"

/*
string  Symbol_Pool[120]={"XAGUSD","CORN","US30","AUDUSD","EURCHF","GBPCAD","NZDJPY","USDCNH","XAUAUD","XAUCHF",
                          "XAUEUR","XAUGBP","XAUJPY","XAUUSD","COPPER","PALLAD","PLAT","UK_OIL","US_OIL","US_NATG",
                          "HTG_OIL","COTTON","SOYBEAN","SUGAR","WHEAT","IT40","AUS200","CHINAA50","ESP35","ESTX50",
                          "FRA40","GER30","HK50","JPN225","N25","NAS100","SIGI","SPX500","SWISS20","UK100","US2000",
                          "AUDCAD","AUDCHF","AUDCNH","AUDJPY","AUDNOK","AUDNZD","AUDPLN","AUDSGD","CADCHF","CADJPY",
                          "CADNOK","CADPLN","CHFHUF","CHFJPY","CHFNOK","CHFPLN","CNHJPY","EURAUD","EURCAD","EURCNH",
                          "EURCZK","EURDKK","EURGBP","EURHKD","EURHUF","EURJPY","EURMXN","EURNOK","EURNZD","EURPLN",
                          "EURRON","EURRUB","EURSEK","EURSGD","EURTRY","EURUSD","EURZAR","GBPAUD","GBPCHF","GBPDKK",
                          "GBPHKD","GBPJPY","GBPMXN","GBPNOK","GBPNZD","GBPPLN","GBPSEK","GBPSGD","GBPUSD","GBPZAR",
                          "HKDJPY","NOKDKK","NOKJPY","NOKSEK","NZDCAD","NZDCHF","NZDUSD","SGDHKD","SGDJPY","TRYJPY",
                          "USDCAD","USDCHF","USDCZK","USDDKK","USDHKD","USDHUF","USDILS","USDJPY","USDMXN","USDNOK",
                          "USDPLN","USDRON","USDRUB","USDSEK","USDSGD","USDTHB","USDTRY","USDZAR","ZARJPY"};
*/
string  Symbol_Pool[5] = {"EURUSD", "EURSGD","EURTRY","EURUSD","EURSEK"};
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+

void  OnStart()
{
   for(int i=0; i < ArraySize(Symbol_Pool); i++)
   {  
      Print("Getting Data from: " + Symbol_Pool[i]);
      Comment("Loading...");
      int maxBars= MathMin(TerminalInfoInteger(TERMINAL_MAXBARS),100000);
      string comment="";
      ENUM_TIMEFRAMES periods[] = {PERIOD_M1, PERIOD_M5, PERIOD_M15, PERIOD_M30, PERIOD_H1, PERIOD_H4, PERIOD_D1};
      for(int p=0;p<ArraySize(periods);p++)
        {
         comment+=ExportBars(Symbol_Pool[i], periods[p], maxBars)+"\n";
         //Print("Period is:", periods[p]);
         Comment(comment);
        }
      comment+="Ready";
      Comment(comment);
   }
   Alert("All Done");
}
  
string ExportBars(string Product, ENUM_TIMEFRAMES period, int maxBars)
{
   MqlRates  rates_array[];
   ArraySetAsSeries(rates_array,true);
   int bars=CopyRates(Product,period,0,maxBars,rates_array);
   string fileName=Product+PeriodToStr(period)+".csv";
   string comment="";
   if(bars>1)
     {
      int filehandle=FileOpen(fileName,FILE_WRITE|FILE_CSV);
      for(int i=bars-1; i>=0; i--)
        {
         FileWrite(filehandle,
            TimeToString(rates_array[i].time,TIME_DATE),
            TimeToString(rates_array[i].time,TIME_MINUTES),
            rates_array[i].open,
            rates_array[i].high,
            rates_array[i].low,
            rates_array[i].close,
            rates_array[i].tick_volume);
        }
      FileFlush(filehandle);
      FileClose(filehandle);
      comment="File exported: "+fileName+", "+IntegerToString(bars)+" bars";
     }
   else
     {
      comment="Error with exporting: "+fileName;
     }
   return (comment);
}

string PeriodToStr(ENUM_TIMEFRAMES period)
  {
   string strper;
   switch(period)
     {
      case PERIOD_M1  : strper="M1";      break;
      case PERIOD_M5  : strper="M5";      break;
      case PERIOD_M15 : strper="M15";     break;
      case PERIOD_M30 : strper="M30";     break;
      case PERIOD_H1  : strper="H1";      break;
      case PERIOD_H4  : strper="H4";      break;
      case PERIOD_D1  : strper="D1";      break;
      case PERIOD_W1  : strper="W1";      break;
      case PERIOD_MN1 : strper="MH1";     break;
      default : strper="";
     }
   return (strper);
  }
//+------------------------------------------------------------------+