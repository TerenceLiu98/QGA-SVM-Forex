from datetime import datetime
import MetaTrader5 as mt5
import pandas as pd
import pytz
import pandas as pd

class Basic(object):

    def __init__(self, timezone, timeout, utc_from):
        self.timezone = pytz.timezone('Etc/UTC')
        self.timeout = 100
        self.utc_from = datetime(year, mon, day, tzinfo=self.timezone)
    
    def __author__():
        print("|------------------------------------------------------|")
        print("|         py_mt5 package author: Terence Lau           |")
        print("|               package version: 0.1.0                 |")
        print("|It is a enhanced version of MetaTrader5(python package|")
        print("|------------------------------------------------------|")
        print("MetaTrader5 package author: ",mt5.__author__)
        print("MetaTrader5 package version: ",mt5.__version__)


    def Period(x):
        return{
            "M1":     mt5.TIMEFRAME_M1,
            "M5":     mt5.TIMEFRAME_M5,
            "M10":    mt5.TIMEFRAME_M10,
            "M30":    mt5.TIMEFRAME_M30,
            "H1":     mt5.TIMEFRAME_H1,
            "H12":    mt5.TIMEFRAME_H12,
            "D1":     mt5.TIMEFRAME_D1,
        }.get(x, mt5.TIMEFRAME_M1)

    def Initialization(account, password, timeout):
        mt5.initialize()
        # Connection with mt5 via socket  
        authorized = mt5.login(account, password, timeout = timeout)
        if authorized == True:
            print("Initialization Finished")
        if authorized == False:
            print("Initialization Failed: Here is the error code:", mt5.last_error())
        return True
        

    def rates_Collection(symbol, timeframe, year, mon, day, num):
        timezone = pytz.timezone('Etc/UTC')
        utc_from = datetime(year, mon, day, tzinfo=timezone)
        rates = mt5.copy_rates_from(symbol, Operation.Period(timeframe), utc_from, num)
        return(rates)

    def to_Dataframe(data):
        rates_frame = pd.DataFrame(data)
        rates_frame['time'] = pd.to_datetime(rates_frame['time'], unit='s')
        return rates_frame


    def Shutdown():
        re = mt5.shutdown()
        if re == True:
            print("Done")
