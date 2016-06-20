# ofxAndroidSensor
Wrapper for Android native and virtual sensors (accelerometer, magnetic, gyroscope, heart rate, orientation, rotation vector and others) in OF

Installation
-----

 - Android Studio 2:

   Add libs in ndk section of build.gradle:

   ```
   ldLibs.addAll(['android', 'log'])
   ```

 - Eclipse:

   Add lines in config.make :
   ```
   PROJECT_LDFLAGS=-Wl,-rpath=./libs
   PROJECT_LDFLAGS += -llog -landroid
   ```
   Change project settings: 
   Properties -> C/C++ General -> Preprocessor, add path to NDK (current version 19)
   ```
   ${NDK_ROOT}\platforms\android-19\arch-arm\usr\include
   ```
 - App for Android version > 5 needed to change AndroidManifest.xml:

   ```
   android:installLocation="auto"
   ```

Usage
-----

See sensors description on https://developer.android.com/reference/android/hardware/Sensor.html

Create a new sensor:

	ofxAndroidSensor* sensor = new ofxAndroidSensor(SENSOR_TYPE_ORIENTATION);

In app loop get sensor data:

	ofVec3f sensorData = sensor->GetData();

Close sensor when exit:

	delete sensor;