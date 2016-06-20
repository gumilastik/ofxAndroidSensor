#include "ofMain.h"

void GetRotationMatrixFromVector(float* mat4x4, float* vec3);
ofVec3f QuatToEuler(const ofQuaternion& rotation);
ofQuaternion EulerToQuat(const ofVec3f& rotationEuler);
