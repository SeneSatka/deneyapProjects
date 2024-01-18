import pandas as pd

# Sera gazı envanteri veri setini yükleyin
data = pd.read_csv("greenhouse_gas_inventory_data_data.csv")  # Veri setinizi uygun bir şekilde yükleyin


# Kategorik sınıfları sayısala dönüştürme
from sklearn.preprocessing import LabelEncoder

label_encoder = LabelEncoder()
data['category'] = label_encoder.fit_transform(data['category'])
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical

# Giriş özelliklerinin boyutunu belirleyin (veri setinizin özellik sayısına göre)
feature_dim =  2

# Sınıfları sayısala dönüştürün
data['category'] = label_encoder.fit_transform(data['category'])
data['year'] = label_encoder.fit_transform(data['year'])
data['value'] = label_encoder.fit_transform(data['value'])
data['country_or_area'] = label_encoder.fit_transform(data['country_or_area'])
num_classes = len(data['category'].unique())
y_categorical = to_categorical(data['category'], num_classes=num_classes)
print(num_classes)
# Modeli oluştur
model = Sequential()
model.add(Dense(units=10, activation='relu', input_dim=feature_dim))
model.add(Dense(units=10, activation='relu'))
model.add(Dense(units=num_classes, activation='softmax'))  # num_classes, sınıf sayısına eşit olmalıdır

# Modeli derle
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
# Giriş verileri ve sınıf etiketleri
X = data.drop(["category","country_or_area"], axis=1)  # Giriş verilerini uygun şekilde belirtin

# Modeli eğit
model.fit(X, y_categorical, epochs=20, batch_size=32, validation_split=0.2)
