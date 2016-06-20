#include "ofMain.h"

#include <string.h>
#include <jni.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android/looper.h>

enum SENSOR_TYPE {
    SENSOR_TYPE_ACCELEROMETER = 1,
    SENSOR_TYPE_MAGNETIC_FIELD = 2,
    SENSOR_TYPE_ORIENTATION = 3,
    SENSOR_TYPE_GYROSCOPE = 4,
    SENSOR_TYPE_LIGHT = 5,
    SENSOR_TYPE_PRESSURE = 6,
    SENSOR_TYPE_TEMPERATURE = 7,
    SENSOR_TYPE_PROXIMITY = 8,
    SENSOR_TYPE_GRAVITY = 9,
    SENSOR_TYPE_LINEAR_ACCELERATION = 10,
    SENSOR_TYPE_ROTATION_VECTOR = 11,
    SENSOR_TYPE_RELATIVE_HUMIDITY = 12,
    SENSOR_TYPE_AMBIENT_TEMPERATURE = 13,
    SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED = 14,
    SENSOR_TYPE_GAME_ROTATION_VECTOR = 15,
    SENSOR_TYPE_GYROSCOPE_UNCALIBRATED = 16,
    SENSOR_TYPE_SIGNIFICANT_MOTION = 17,
    SENSOR_TYPE_STEP_DETECTOR = 18,
    SENSOR_TYPE_STEP_COUNTER = 19,
    SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR = 20,
    SENSOR_TYPE_HEART_RATE = 21
};

class ofxAndroidSensor : public ofThread {
private:
    ASensorManager* sensorManager = NULL;
    ASensorEventQueue* queueEvent = NULL;
    ASensorRef sensor = NULL;
    ALooper* looper = NULL;

    SENSOR_TYPE type;
    int rate;
    ofVec3f data;

    void threadedFunction();

public:
    ofxAndroidSensor(SENSOR_TYPE type, int rate = 30);
    ~ofxAndroidSensor();

    bool IsExist();
    ofVec3f GetData();
};
