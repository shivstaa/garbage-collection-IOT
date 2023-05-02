import cv2
import numpy as np
import tensorflow as tf
import time
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array
import serial
import pyrebase

config = {
    "apiKey": "AIzaSyClZJeiw0cpZ3JkwwVczTE2lOFvxKDKajk",
    "authDomain": "lahacks-4be07.firebaseapp.com",
    "projectId": "lahacks-4be07",
    "storageBucket": "lahacks-4be07.appspot.com",
    "messagingSenderId": "566228910809",
    "appId": "1:566228910809:web:e3a9408f1eac72780db4c8",
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()

plasticCount, canCount, paperCount, wasteCount = 0, 0, 0, 0

# Set up the Bluetooth connection
bluetooth = serial.Serial("COM4", 57600)  # Replace "COM_PORT" with the appropriate port for your Bluetooth device

# Set the model URL
url = "./my_model/"

# Load the model
model = load_model(url + "keras_model.h5")

# Get the number of classes
max_predictions = model.output_shape[1]

# Load class names from labels.txt
with open(url + "labels.txt", "r") as f:
    class_names = [line.strip() for line in f.readlines()]

# Set up the webcam
cap = cv2.VideoCapture(0)

def predict(frame):
    resized_frame = cv2.resize(frame, (224, 224))
    resized_frame = img_to_array(resized_frame)
    resized_frame = np.array([resized_frame], dtype="float32")
    resized_frame /= 255.0

    prediction = model.predict(resized_frame)[0]
    return prediction

cv2.namedWindow("Video Feed", cv2.WINDOW_NORMAL)

start_time = time.time()
label = "default state"
first_three_seconds = True
pause_start = None
post_pause_start = None

while cv2.getWindowProperty("Video Feed", cv2.WND_PROP_VISIBLE) >= 1:
    ret, frame = cap.read()
    if not ret:
        break

    elapsed_time = time.time() - start_time

    if elapsed_time > 3 and first_three_seconds:
        first_three_seconds = False
        start_time = time.time()

    if not first_three_seconds and post_pause_start is None:
        prediction = predict(frame)
        max_prob_idx = np.argmax(prediction)
        max_prob = f"{prediction[max_prob_idx]:.2f}"

        accuracy_threshold = 0.75
        duration_threshold = 3

        if float(max_prob) > accuracy_threshold:
            label = f"{class_names[max_prob_idx]}: {max_prob}"
            elapsed_time = time.time() - start_time
            if elapsed_time > duration_threshold and pause_start is None:
                pause_start = time.time()
        else:
            label = "default state"
            start_time = time.time()
            pause_start = None

        if pause_start is not None and time.time() - pause_start < 3:
            label = f"Paused - {class_names[max_prob_idx]}: {max_prob}"
            if class_names[max_prob_idx] in ["0 Plastic", "1 Can", "2 Paper"]:
                print("here")
                bluetooth.write(b'1')
                print('wrote 1')
                if class_names[max_prob_idx] == "0 Plastic":
                    plasticCount += 1
                elif class_names[max_prob_idx] == "1 Can":
                    canCount += 1
                elif class_names[max_prob_idx] == "2 Paper":
                    paperCount += 1
                
            elif class_names[max_prob_idx] == "3 Waste":
                bluetooth.write(b'2')
                print('wrote 0')
                wasteCount += 1
                
            db.child("counts").update({
                "plastic": plasticCount,
                "can": canCount,
                "paper": paperCount,
                "waste": wasteCount
            })

        elif pause_start is not None and time.time() - pause_start >= 3:
            pause_start = None
            post_pause_start = time.time()
            label = "default state"

    if post_pause_start is not None and time.time() - post_pause_start < 2:
        label = "default state"
    elif post_pause_start is not None and time.time() - post_pause_start >= 2:
        post_pause_start = None
        start_time = time.time()

    # Display the label on the video feed
    # Display the label on the video feed
    cv2.putText(frame, label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)

    # Display the video feed
    cv2.imshow("Video Feed", frame)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
bluetooth.close()