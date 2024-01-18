import numpy as np
import pandas as pd
data =pd.read_csv("car.csv",encoding="unicode_escape")
data_copy=data.copy()


from sklearn import preprocessing
sayisallastirma=preprocessing.LabelEncoder()
data_copy["fiyat"]=sayisallastirma.fit_transform(data_copy["fiyat"])
data_copy["onarim"]=sayisallastirma.fit_transform(data_copy["onarim"])
data_copy["kapi sayisi"]=sayisallastirma.fit_transform(data_copy["kapi sayisi"])
data_copy["kisi sayisi"]=sayisallastirma.fit_transform(data_copy["kisi sayisi"])
data_copy["bagaj boyutu"]=sayisallastirma.fit_transform(data_copy["bagaj boyutu"])
data_copy["Guvenlik"]=sayisallastirma.fit_transform(data_copy["Guvenlik"])
data_copy["satis "]=sayisallastirma.fit_transform(data_copy["satis "])

inputs=np.array(data_copy.drop(["satis "],axis=1))
output=np.array(data_copy["satis "])



from sklearn.model_selection import train_test_split
input_learn,input_test,satis_learn,satis_test=train_test_split(inputs,output,test_size=0.3,random_state=109)


from sklearn.naive_bayes import CategoricalNB
model = CategoricalNB()
model.fit(input_learn,satis_learn)
satis_tahmin=model.predict(input_test)