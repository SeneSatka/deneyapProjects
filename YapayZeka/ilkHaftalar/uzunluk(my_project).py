from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
X = [[1.5],[1.51],[1.53],[1.55],[1.57],[1.6],[1.67],[1.64],[1.7],[1.71],[1.78],[1.74],[1.78],[1.80],[1.81],[1.91],[1.87],[1.89],[1.96],[2.23],[2.45],[2.14],[2.9]]
Y = [0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,2,2,]
model = DecisionTreeClassifier()
model.fit(X,Y)
Y_tahmin = model.predict([[input()]])
if Y_tahmin == 0:
    Y_tahmin="Kısa"
elif Y_tahmin==1:
    Y_tahmin="Orta"
elif Y_tahmin==2:
    Y_tahmin="Uzun"
print("Tahmin edilen: ",Y_tahmin)
