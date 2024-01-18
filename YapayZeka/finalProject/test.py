from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.utils import to_categorical
import numpy as np
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score
from sklearn import preprocessing 
import pandas as pd

ppgn=preprocessing.LabelEncoder()
a=pd.read_csv("./greenhouse_gas_inventory_data_data.csv",encoding="unicode_escape")
dataset=a.copy()

dataset["country_or_area"]=ppgn.fit_transform(dataset["country_or_area"])
dataset["year"]=ppgn.fit_transform(dataset["year"])
dataset["value"]=ppgn.fit_transform(dataset["value"])
dataset["category"]=ppgn.fit_transform(dataset["category"])
X=np.array(dataset.drop(["category"],axis=1))
y=np.array(to_categorical(dataset["category"],num_classes=len(dataset['category'].unique())))
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.2,random_state=1)

model=Sequential()
model.add(Dense(60,input_dim=3,activation="relu"))
model.add(Dense(60,activation="relu"))
model.add(Dense(60,activation="relu"))  
model.add(Dense(60,activation="relu"))
model.add(Dense(10,activation="softmax"))
model.compile(optimizer="adam",loss="categorical_crossentropy",metrics=["acc"])
model.summary()

model.fit(X_train,y_train,epochs=200,batch_size=32)    
print(model.predict(X_test))
print(y_test)
