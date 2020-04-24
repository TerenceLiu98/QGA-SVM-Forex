from threading import Thread
from time import sleep
from datetime import datetime

from mt4 import Trader
from mt4 import Connection

now = datetime.now

BUY = 0
SELL = 1

class Client(Thread):
    """ZMQ client thread connecting to MQL server"""
    def __init__(self, push=1111, pull=2222):
        self.manager = Trader(push, pull)
        super(Client, self).__init__()

    def run(self):
        Thread(target=self.manager.push_listener).start()
        while True:
            try:
                self.manager.data("EURUSD", "H1")
                print("{hour}:{min}:{sec} - Data request sent".format(hour=now().hour, min=now().minute, sec=now().second))

                sleep(10)
            except:
                continue
        print('Disconnecting sockets..')
        self.con.disconnect()
        print('Done')


if Client.__init__ == "__main__":
    Client.run()
