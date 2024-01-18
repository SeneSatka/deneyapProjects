from keras.models import Sequential
from keras.layers import Dense
import numpy as np 
from sklearn.model_selection import train_test_split as t2p
from sklearn import metrics
import matplotlib.pyplot as plt


dataset=np.genfromtxt("INTELLIGENT IRRIGATION SYSTEM.csv",delimiter=",")
Input=dataset[1:,0:2]
Output=dataset[1:,2]
Input_train,Input_test,Output_train,Output_test=t2p(Input,Output,test_size=0.2,random_state=0)

model=Sequential()
model.add(Dense(6,input_dim=2,activation="relu"))
model.add(Dense(6,activation="relu"))
model.add(Dense(6,activation="relu"))
model.add(Dense(6,activation="relu"))
model.add(Dense(1,activation="sigmoid"))
model.compile(loss="binary_crossentropy",optimizer="adam",metrics=["accuracy"])
model.summary()

model.fit(Input_train,Output_train,epochs=30,batch_size=5)
Output_pred=model.predict(Input_test)
Output_pred=(Output_pred>0.5).flatten()
print("Doğruluk:",metrics.accuracy_score(Output_test,Output_pred))

from sklearn.metrics import confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
cm= confusion_matrix(Output_test,Output_pred)
index = ['Çalışmıyor','Çalışıyor']
columns = ['Çalışmıyor','Çalışıyor']
cm_df = pd.DataFrame(cm,columns,index)
plt.figure(figsize=(10,6))
sns.heatmap(cm_df, annot=True,fmt="d")
