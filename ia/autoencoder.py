

import keras
import importData
from keras import layers
from keras.callbacks import TensorBoard
import numpy as np
import matplotlib.pyplot as plt



# FAIRE EN SORTE QUE CHAQUE IMAGES NORMALES CORRESPONDE A LA MEME IMAGE APRES FUSION ( 2 dossier different mais meme indice)
images_train_noisy, images_test_noisy = importData.loadImages("traindata/noise/", "grayscale")
images_train_clean, images_test_clean = importData.loadImages("traindata/clean/", "grayscale")


input_img = keras.Input(shape=images_train_clean[0].shape)


x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(input_img)
x = layers.MaxPooling2D((2, 2), padding='same')(x)
x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(x)
encoded = layers.MaxPooling2D((2, 2), padding='same')(x)


x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(encoded)
x = layers.UpSampling2D((2, 2))(x)
x = layers.Conv2D(32, (3, 3), activation='relu', padding='same')(x)
x = layers.UpSampling2D((2, 2))(x)
decoded = layers.Conv2D(1, (3, 3), activation='sigmoid', padding='same')(x)

autoencoder = keras.Model(input_img, decoded)
autoencoder = keras.models.load_model("AutoEncoder_astro")
autoencoder.summary()
autoencoder.compile(optimizer='adam', loss='binary_crossentropy')


# TRAINING PART

#normalize values between 0 and 1 and flatten img in a vector
x_train = images_train_clean.astype('float32') / 255.
x_test = images_test_clean.astype('float32') / 255.
x_train = x_train.reshape((len(x_train), 512, 512, 1))
x_test = x_test.reshape((len(x_test), 512, 512, 1))
print(x_train.shape)
print(x_test.shape)

x_train_noisy = images_train_noisy.astype('float32') / 255.
x_test_noisy = images_test_noisy.astype('float32') / 255.

"""
noise_factor = 0.5
x_train_noisy = x_train + noise_factor * np.random.normal(loc=0.0, scale=1.0, size=x_train.shape)
x_test_noisy = x_test + noise_factor * np.random.normal(loc=0.0, scale=1.0, size=x_test.shape)

x_train_noisy = np.clip(x_train_noisy, 0., 1.)
x_test_noisy = np.clip(x_test_noisy, 0., 1.) """

"""
autoencoder.fit(x_train_noisy, x_train,
                epochs=120,
                batch_size=4096,
                shuffle=True,
                validation_data=(x_test_noisy, x_test))
"""
autoencoder.save("./AutoEncoder_astro")

# test


unique = np.array([x_test_noisy[0]])


decoded_imgs = autoencoder.predict(unique)


n = 1
plt.figure(figsize=(20, 4))
for i in range(1, n + 1):
    # Display original
    ax = plt.subplot(2, n, i)
    plt.imshow(x_test_noisy[i].reshape(512, 512))
    plt.gray()
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)

    # Display reconstruction
    ax = plt.subplot(2, n, i + n)
    plt.imshow(decoded_imgs[0].reshape(512, 512))
    plt.gray()
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
plt.show()
