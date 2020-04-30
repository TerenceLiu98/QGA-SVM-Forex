from threading import Thread
from time import sleep
from datetime import datetime

from mt4 import Trader
from mt4 import Connection
import numpy as np
now = datetime.now

BUY = 0
SELL = 1

class Client(Thread):
    """ZMQ client thread connecting to MQL server"""
    def __init__(self, push=1111, pull=2222):
        self.manager = Trader(push, pull)
        super(Client, self).__init__()
        self.symbol = "BTCCNH"
    def run(self, symbol):
        #Thread(target=self.manager.push_listener).start()
        x = []
        i = 0
        while True:
            try:
                self.manager.data(symbol, "H1")
                #self.manager.data("EURUSD", "H1")
                print("{hour}:{min}:{sec} - Data request sent".format(hour=now().hour, min=now().minute, sec=now().second))
                x.append[self.manager.get_response()]
                sleep(5)
            except:
                continue
        print('Disconnecting sockets..')
        self.manager.Connection.disconnect()
        print('Done')
    
    def period(self, time_init, time_end):
        time_init = datetime.strptime(str(time_init),"%Y-%m-%d %H:%M:%S.%f")
        time_end = datetime.strptime(str(time_end),"%Y-%m-%d %H:%M:%S.%f")
        hour = abs((time_end - time_init).seconds / 3600
        return 

symbol = 'BCHUSD'
client = Client()
client.run(symbol)
