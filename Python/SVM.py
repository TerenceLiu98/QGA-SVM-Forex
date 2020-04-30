from py_mt5 import Operation as O
from sklearn import svm
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import learning_curve
import time
import matplotlib.pyplot as plt


## DONT USE IT! IT IS A WRONG MODEL ##

## define variables ##
Symbol_pool = ["USDJPY", "EURUSD"]

account = 67057413
password = "1maqblxo"
O.Initialization(account, password, 100)

rates = O.rates_Collection(Symbol_pool[1], "H1", 2020, 4, 30, 100)

rates_frame = O.to_Dataframe(rates)
print("\nDisplay dataframe with data of '{}': ".format(Symbol_pool[1]))
print(rates_frame)  

# rates_frame.to_csv(r'{}_{}.csv'.format(Symbol_pool[1], "M1"), index = False)
# randomly shuffle the data we get 

data = rates_frame
y = data['close']
X = data.drop(columns = ['close', 'time'])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)

X_train_matrix = X_train.iloc[:,:].values
y_train_matrix = np.array(y_train)


X_test_matrix = X_test.iloc[:,:].values
y_test_matrix = np.array(y_test)

clf = svm.SVR(kernel='poly', C=100, gamma='auto', degree=3, epsilon=.1,
               coef0=1)

clf.fit(X_train_matrix, y_train_matrix)
print(clf.predict(X_test_matrix))

#with plt.style.context(['science']):
plt.figure()
plt.plot(model.predict(X_test_matrix))
plt.plot(y_test_matrix, linestyle = ":")
plt.legend()
plt.show()
