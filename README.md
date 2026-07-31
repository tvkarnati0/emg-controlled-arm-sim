# EMG-Controlled Robotic Hand
A machine learning pipeline that classifies hand and wrist gestures from raw EMG signals to control a physical, servo-actuated robotic hand in real time. Simplified model of a prostheitc hand.

## Overview
The project processes 8-channel EMG data. Through signal processing, it extracts time-domain feautres, trains a gesture classifier, and sends live predictions to the Arduino-controlled hand. Correct and incorrect predictions are determined by green/red LEDs and the hand shows immediate visual feedback.
**Pipeline:** Raw EMG → Bandpass Filter → Windowing → Feature Extraction → Random Forest Classifier → Serial Communication → Arduino → Servo-Actuated Hand + LED Feedback

## Dataset
EMG data for gestures (Kaggle mirror of the UCI "EMG data for gestures" dataset) — 8-channel EMG recordings across 36 subjects, sampled at 1000 Hz.
Gesture classes (all gestures per UCI documentation expect gesture 4 and 7):
**Class**	**Gesture**
0	Unmarked / rest data
1	Hand at rest
2	Hand clenched in a fist
3	Wrist flexion
4	Index finger (vs. wrist extension)
5	Radial deviation
6	Ulnar deviation
7	Middle finger (vs. extended palm)

##Methods
- **Filtering:** 20–450 Hz bandpass filter (typical EMG frequency range)
- **Windowing:** 200ms windows with 75% overlap (50ms step) 
- **Features:** Mean Absolute Value (MAV), Root Mean Square (RMS), Waveform Length (WL), and Zero-Crossing Rate (ZCR) — extracted per channel (32 features total across 8 channels)
- **Classifier:** Random Forest with balanced class weights, to address significant class imbalance (the rest class had ~10x more samples than active gestures)
- **Hardware:** Arduino Uno R4 WiFi driving 4 SG90 micro servos (3 fingers + 1 wrist axis) through a cardboard-and-thread mechanical hand, fully reusable/glue-free construction
- **Feedback:** Green LED for correct predictions, red LED for incorrect predictions, based on live comparison against true test labels

## Results
- **84% overall accuracy** on held-out test data
- Strong performance on most gestures (F1 0.77–0.93)
- Class 1 (hand at rest) was frequently - misclassified as class 0 (unmarked/rest) — 13% recall. This reflects an ambiguity in the dataset's labeling protocol (both classes represent an inactive hand) rather than a model or pipeline flaw.
- Adding the Zero-Crossing Rate feature improved macro-average F1 from 0.73 to 0.75 and slightly improved detection of subtle, low-amplitude gestures.

## Hardware
**Materials List**
- Arduino R4 WiFi
- x4 SG90 micr servos
- Cardboard
- Dental floss
- Toothpicks
- Exacto knife
- 1 green LED
- 1 red LED
- x2 220Ohm resistors

**Mechanical Design:** 3 servos controlling one finger each and 4th servo providing wrist rotation on left-right axis.

**Hardware Limitation:** Wrist servo is limited to left and right rotation, which supports radial/ulnar deviation but not wrist flexion/tension. Future work involves adding aother servo to expad motion to the up/down rotation axis.

## Future Work
- Addition wrist servo to account for wrist flexion/extension movements
- Class 1 vs Class 0 confusion is an issue from source dataset
- Use of live EMG data that can stream directly into the pipeline
- Use more datasets to generalize the model
- Upgrade the hand frame using 3D printed parts for enhanced durability and motion