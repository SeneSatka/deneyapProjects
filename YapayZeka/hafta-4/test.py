import numpy as np
import PIL.Image as img
import os
import pandas as pd
tas_path="./myphoto/tas/"
kagit_path="./myphoto/kagit/"
makas_path="./myphoto/makas/"
def dosya(yol):
 return [os.path.join(yol,f) for f in os.listdir(yol)]
print("Tas fotografi",len(dosya(tas_path)))
print("Kagit fotografi",len(dosya(kagit_path)))
print("Makas fotografi",len(dosya(makas_path)))
def veri_donusturme(klasor_adi,sinif_adi):
    goruntuler=dosya(klasor_adi)
    goruntu_sinif=[]
    for goruntu in goruntuler:
        goruntu_oku= img.open(goruntu).convert('L')
        gorunu_boyutlandirma=goruntu_oku.resize((1024,1024))
        goruntu_donusturme=np.array(gorunu_boyutlandirma).flatten()
        if sinif_adi=="tas":
            veriler=np.append (goruntu_donusturme, [0])
        elif sinif_adi=="kagit":
            veriler=np.append (goruntu_donusturme, [1])
        elif sinif_adi=="makas":
            veriler=np.append (goruntu_donusturme, [2])
        else:
            continue
        goruntu_sinif.append(veriler)
    return goruntu_sinif

tas=veri_donusturme(tas_path,"tas")
kagit=veri_donusturme(kagit_path,"kagit")
makas=veri_donusturme(makas_path,"makas")
tas_df=pd.DataFrame(tas)
kagit_df=pd.DataFrame(kagit)
makas_df=pd.DataFrame(makas)
tum_veri= pd.concat([tas_df,kagit_df,makas_df])
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics
from sklearn.model_selection import GridSearchCV
Giris=np.array(tum_veri)[:,:1048576]
Cikis=np.array(tum_veri)[:,1048576]
Giris_train, Giris_test, Cikis_train, Cikis_test = train_test_split(Giris, Cikis,
test_size=0.2, random_state=1)
model= DecisionTreeClassifier()
clf = model.fit(Giris_train,Cikis_train)
Cikis_pred = clf.predict(Giris_test)
print("Doğruluk:",metrics.accuracy_score(Cikis_test, Cikis_pred))

