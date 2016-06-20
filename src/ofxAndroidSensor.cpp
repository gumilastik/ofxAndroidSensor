#include "ofxAndroidSensor.h"

#define MYTAG "ofxAndroidSensor"
#define MYLOGI(...) __android_log_print(ANDROID_LOG_INFO, MYTAG, __VA_ARGS__)
#define MYLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, MYTAG, __VA_ARGS__)

#define LOOPER_ID 1

ofxAndroidSensor::ofxAndroidSensor(SENSOR_TYPE type, int rate)
{
    this->type = type;
    this->rate = rate;

    startThread(false);
}

ofxAndroidSensor::~ofxAndroidSensor()
{
    stopThread();
}


void ofxAndroidSensor::threadedFunction()
{
    sensorManager = ASensorManager_getInstance();
    MYLOGD("run");

    looper = ALooper_forThread();
    if (looper == NULL)
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

    queueEvent = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_ID, NULL, NULL);

    sensor = ASensorManager_getDefaultSensor(sensorManager, type);
    if (sensor != NULL) {
        MYLOGI("sensor: %s, vendor: %s",
            ASensor_getName(sensor),
            ASensor_getVendor(sensor));
        MYLOGI("min-delay: %d ", ASensor_getMinDelay(sensor));

        ASensorEventQueue_enableSensor(queueEvent, sensor);
        ASensorEventQueue_setEventRate(queueEvent, sensor, (1000L / rate) * 1000);

        int identifier;
        int events;

        while (isThreadRunning() != 0) {
            while ((identifier = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
                if (identifier == LOOPER_ID) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(queueEvent, &event, 1) > 0) {
                        //MYLOGI("INSIDE LOOP");
                        if (event.type == type) {
                            //MYLOGI("sensor (x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
                            data = ofVec3f(event.data[0], event.data[1], event.data[2]);//, event.data[3]);
                        }
                    }
                }
            }
        }

        ASensorEventQueue_disableSensor(queueEvent, sensor);
    }

    MYLOGI("stop");
    if (queueEvent != NULL) {
        ASensorManager_destroyEventQueue(sensorManager, queueEvent);
    }
}

bool ofxAndroidSensor::IsExist()
{
    return sensor != NULL;
}

ofVec3f ofxAndroidSensor::GetData()
{
    return data;
}

