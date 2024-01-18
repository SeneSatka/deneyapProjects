
import pandas as pd
from sklearn import preprocessing as ppg
from sklearn.model_selection import train_test_split as t2p,GridSearchCV
from sklearn.tree import DecisionTreeClassifier  
from sklearn.metrics import accuracy_score,confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt
ppgn=ppg.LabelEncoder()
a=pd.read_csv("./emission_dataset.csv",encoding="unicode_escape")
data=a.copy()
data["country_or_area"]=ppgn.fit_transform(data["country_or_area"])
data["category"]=ppgn.fit_transform(data["category"])
X=data.drop("category",axis=1)
y=data["category"]

X_train,X_test,y_train,y_test=t2p(X,y,test_size=0.5)



agac_parametreleri={"criterion":["gini","entropy"],"max_depth":[2,5,10,20,30,90,120,150]}
arama_algoritmasi=GridSearchCV(DecisionTreeClassifier(),agac_parametreleri,cv=5)
arama_algoritmasi.fit(X_train,y_train)
best_params=arama_algoritmasi.best_params_
model=DecisionTreeClassifier(criterion=best_params["criterion"],max_depth=best_params["max_depth"])
clf=model.fit(X_train,y_train)

pred=clf.predict(X_test)

# while(accuracy_score(y_test,pred)<0.67):
#     clf=model.fit(X_train,y_train)
#     pred=clf.predict(X_test)
print("(DecisionTreeClassifier)Doğruluk oranı: ",accuracy_score(y_test,pred))
hata_matrixi=confusion_matrix(y_test,pred)
index = ['CO2','GHG(Indirect CO2)','GHG',"HFC","CH4","NF3","N2O","PFC","SF6","HFC+PFC"]
columns = ['CO2','GHG(Indirect CO2)','GHG',"HFC","CH4","NF3","N2O","PFC","SF6","HFC+PFC"]

hata_goster = pd.DataFrame(hata_matrixi,columns,index)
plt.figure(figsize=(10,6))
sns.heatmap(hata_goster, annot=True,fmt="d")
