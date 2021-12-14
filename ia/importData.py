import os
import tensorflow as tf
from keras_preprocessing.image.utils import load_img
from keras_preprocessing.image.utils import img_to_array

print(tf.__version__)

import numpy as np



def loadImages( DIR, color):

    images_test = []
    images_train = []
    pick_factor = len(os.listdir(DIR)) * 0.2
    count = 0
    for i in os.listdir(DIR):
        img = load_img(DIR + i, color_mode=color, target_size=(512, 512))
        img = img_to_array(img)
        if count > pick_factor:
            images_train.append(img)

        else:
            images_test.append(img)
        count += 1
    images_train = np.array(images_train)
    images_test = np.array(images_test)
    return images_train, images_test

def SingleLoadImages( DIR, color):

    images = []
    for i in os.listdir(DIR):

        img = load_img(DIR + i, color_mode=color)
        img = img_to_array(img)
        images.append(img)
    images = np.array(images)
    return images


