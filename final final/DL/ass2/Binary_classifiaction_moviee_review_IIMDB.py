import numpy as np
import pandas as pd
from keras.datasets import imdb
from keras.utils import to_categorical
from sklearn.model_selection import train_test_split
import seaborn as sns
import matplotlib.pyplot as plt
from keras import models, layers
import tensorflow as tf

# Load the IMDB dataset
(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words=10000)

# Combine train and test data for easier analysis
data = np.concatenate((X_train, X_test), axis=0)
label = np.concatenate((y_train, y_test), axis=0)

# Display sample data
print("Review is ", X_train[5])
print("Review label is ", y_train[5])

# Vocabulary
vocab = imdb.get_word_index()
print(vocab)

# Decoding a review from the integer-encoded form
index = imdb.get_word_index()
reverse_index = {value: key for key, value in index.items()}
decoded = " ".join([reverse_index.get(i - 3, "#") for i in data[0]])
print(decoded)

# Vectorization function
def vectorize(sequences, dimension=10000):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1
    return results

# Vectorizing the data
data = vectorize(data)
label = np.array(label).astype("float32")

# Train/test split (avoid re-splitting if already split)
X_train, X_test, y_train, y_test = train_test_split(data, label, test_size=0.20, random_state=1)

# Display class distribution
labelDF = pd.DataFrame({'label': label})
sns.countplot(x='label', data=labelDF)

# Model Architecture
model = models.Sequential()
model.add(layers.Dense(50, activation="relu", input_shape=(10000, )))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(50, activation="relu"))
model.add(layers.Dropout(0.2))
model.add(layers.Dense(50, activation="relu"))
model.add(layers.Dense(1, activation="sigmoid"))
model.summary()

# Compile the model
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])

# EarlyStopping callback
callback = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=3)

# Training the model
results = model.fit(
    X_train, y_train,
    epochs=2,
    batch_size=500,
    validation_data=(X_test, y_test),
    callbacks=[callback]
)

# Model performance evaluation
print("Validation Accuracy: ", np.mean(results.history["val_accuracy"]))
print("Training Accuracy: ", np.mean(results.history["accuracy"]))

# Plot the accuracy and loss curves
plt.plot(results.history['accuracy'])
plt.plot(results.history['val_accuracy'])
plt.title('Model Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend(['Train', 'Test'], loc='upper left')
plt.show()

plt.plot(results.history['loss'])
plt.plot(results.history['val_loss'])
plt.title('Model Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend(['Train', 'Test'], loc='upper left')
plt.show()

# Predict on test data
predictions = model.predict(X_test)
print(predictions)
