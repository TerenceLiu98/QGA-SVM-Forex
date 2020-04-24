# -*- coding: utf-8 -*-
"""
    Strategy.py
    --
    @author: Darwinex Labs (www.darwinex.com)
    
    Copyright (c) 2019 onwards, Darwinex. All rights reserved.
    
    Licensed under the BSD 3-Clause License, you may not use this file except 
    in compliance with the License. 
    
    You may obtain a copy of the License at:    
    https://opensource.org/licenses/BSD-3-Clause
"""
import os

#############################################################################
#############################################################################
# _path = '<PATH_TO_ROOT_DIR_CONTAINING_Connector>'
#os.chdir(_path)
#############################################################################
#############################################################################

from Connector import Connector
from Execution import Execution
from Reporting import Reporting

class Strategy(object):
    
    def __init__(self, _name="DEFAULT_STRATEGY",    # Name 
                 _symbols=[('EURUSD',0.01),     # List of (Symbol,Lotsize) tuples
                           ('AUDNZD',0.01),
                           ('NDX',0.10),
                           ('UK100',0.1),
                           ('GDAXI',0.01),
                           ('XTIUSD',0.01),
                           ('SPX500',1.0),
                           ('STOXX50E',0.10),
                           ('XAUUSD',0.01)],
                 _broker_gmt=3,                 # Darwinex GMT offset
                 _verbose=False):               # Print ZeroMQ messages
                 
        self._name = _name
        self._symbols = _symbols
        self._broker_gmt = _broker_gmt
        
        # Not entirely necessary here.
        self._zmq = Connector(_verbose=_verbose)
        
        # Modules
        self._execution = Execution(self._zmq)
        self._reporting = Reporting(self._zmq)
        
    ##########################################################################
    
    def _run_(self):
        
        """
        Enter strategy logic here
        """
         
    ##########################################################################