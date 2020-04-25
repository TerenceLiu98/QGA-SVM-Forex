# py-mt4
Using Python (3.x) to auto trading with MT4

- [py-mt4](#py-mt4)
  * [Pre-requisites:](#pre-requisites-)
  * [Introduction (Reasoning behind the webinar)](#introduction--reasoning-behind-the-webinar-)
    + [Reasoning behind this webinar:](#reasoning-behind-this-webinar-)
    + [What is ZeroMQ ? Why use it?](#what-is-zeromq---why-use-it-)
  * [ZeroMQ Communication Patterns](#zeromq-communication-patterns)
    + [ZeroMQ: Requrest/Reply](#zeromq--requrest-reply)
    + [ZeroMQ: PUSH/PULL](#zeromq--push-pull)
    + [Planning System Architecture](#planning-system-architecture)
    + [In summary:](#in-summary-)
- [Machine Environment](#machine-environment)
- [Installation](#installation)

## Pre-requisites:

1. Programming experiment in Python/R/MQL
2. Knowledge of TCP Socket Communication 
3. Knowledge of MQL EQ default functions 

## Introduction (Reasoning behind the webinar)

We present a technique employing `ZeroMQ` (an Open Source, Asynchronous messaging Library and Concurrency Framework)

### Reasoning behind this webinar:

1. Lack of comprehensive, publicly available literature about this topic on the web
2. Traders have traditionally relied on Winsocket/WinAPI based solution that often require revision with both Microsoft and MetaQuote updates
3. Alternative to ZeroMQ include named pipes, and approaches where filesystem - dependent functionality forms the bridge between MT and external languages 



### What is ZeroMQ ? Why use it? 

1. Enables programmers to connect any code to any other code, in a number of ways
2. Eliminates a MT user's dependency on just MT-supported tech 
3. Traders can develop indicators and strategies in C/C#/C++, Python, R and Java (to name a few), and deploy to market via MT4
4. Different strategy components can be built in different languages if required, and seamlessly talk to each other over TCP, in process, inter-process or multicast protocols
5. Multiple communication patterns and disconnected opertion.
   1. REP / REQ
   2. PUB / SUB
   3. PUSH / PULL

## ZeroMQ Communication Patterns

1. Request (REQ)/Reply(REP), Publish(PUB)/Subscribe(SUB) and Push(PUSH)/Pull(PULL).

2. In our example, we will employ the REQ/REP and PUSH/PULL communication patterns

3. MetaTrader 4 will be our "server", and trading strategies will be "Clients"

   

### ZeroMQ: Requrest/Reply

1. The server will employ a TCP socket of type REP, to receive requests and send responses
2. A REP socket MUST always initiate a pair of call: first, a receive, followed by a send.
3. The Client (Trading Strategy, e.g. in Python) will employ a TCP socket of type REQ, to send requests and receive responses.
4. A REQ socket MUST always initiate a pair of calls too: first, a send, followed by a receive.
5. For this implementation, the REQ/REP pattern will enable our Clients: 
   - Send commands to the MetaTrader 4 Server 
   - Receive acknowledgement of the same
   - (e.g. OPEN/MODIFY/CLOSE trades, GET BID/ASK)

### ZeroMQ: PUSH/PULL 

1. The Server (Meta Trader 4 EA) will also employ a second, PUSH socket, to send additional information to Clients (Trading Strategies)
2. This is a one-way socket, and the server will only be able to send data to this socket, without being able to receive anything back.
3. The Client(Trading Strategy will also employ a second, PULL socket, to receive additional information from the Server)
4. This too is a one-way socket, and the client will only be able to receive data from this socket, without being able to send anything back
5. The PUSH/PULL pattern therefore, enables servers and clients to exchange data with each other on-demand, but in one direction without expecting a response
6. This could of course be swapped out for another REQ/REP pattern, depending on your application's flow control requirements

### Planning System Architecture 

![Planning system.png](https://i.loli.net/2020/04/24/mGbf7FIgx6LkqUD.png)

### In summary:

1. The server will employ two sockets, REP/PUSH 
2. Each Client will employ two sockets, REQ/PULL
*Acturally, we use PULL/PUSH on Server and PUSH/PULL on Client*

# Machine Environment 
- win10 Version 2004
- python 3.8.2

# Installation 
- The DLLs require that you have the latest Visual C++ runtime (2015)]：[Microsoft Visual C++ Runtime](!https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)
- `cd test`
- Turn off the anti-virus program, which may interdict the network
- unzip the `.zip`
- put the file inside the `include` into your MT4's `include` (same operation to the `Linbrary`)
- pip install pyzmq
- pip install TA_Lib-0.4.17-cp38-cp38m-win_amd64.whl   * you can find your version in [pythonlibs](https://www.lfd.uci.edu/~gohlke/pythonlibs/)*
- you can try the `.py` & `.mq4` from the `test` file
