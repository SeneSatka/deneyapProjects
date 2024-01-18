from sklearn import datasets
iris= datasets.load_iris()
from sklearn.model_selection import train_test_split
x_train,x_test,y_tarin,y_test=train_test_split(iris.data, iris.target,test_size=0.3)
from sklearn.naive_bayes import GaussianNB
bayes= GaussianNB()
bayes.fit(x_train, y_tarin)


y_tahmin=bayes.predict(x_test)

print("Olması gereken",y_test)
print("Tahmin edilen",y_tahmin)


from sklearn import metrics
print("Başarı oranı",metrics.accuracy_score(y_test, y_tahmin))
