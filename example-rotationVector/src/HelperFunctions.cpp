#include "HelperFunctions.h"

void GetRotationMatrixFromVector(float* mat4x4, float* vec3)
{
    float q0;
    float q1 = vec3[0];
    float q2 = vec3[1];
    float q3 = vec3[2];

    q0 = 1 - q1 * q1 - q2 * q2 - q3 * q3;
    q0 = (q0 > 0) ? sqrt(q0) : 0;
//	q0 = vec3[3];

    float sq_q1 = 2 * q1 * q1;
    float sq_q2 = 2 * q2 * q2;
    float sq_q3 = 2 * q3 * q3;
    float q1_q2 = 2 * q1 * q2;
    float q3_q0 = 2 * q3 * q0;
    float q1_q3 = 2 * q1 * q3;
    float q2_q0 = 2 * q2 * q0;
    float q2_q3 = 2 * q2 * q3;
    float q1_q0 = 2 * q1 * q0;

    mat4x4[0] = 1 - sq_q2 - sq_q3;
    mat4x4[1] = q1_q2 - q3_q0;
    mat4x4[2] = q1_q3 + q2_q0;
    mat4x4[3] = 0.0f;

    mat4x4[4] = q1_q2 + q3_q0;
    mat4x4[5] = 1 - sq_q1 - sq_q3;
    mat4x4[6] = q2_q3 - q1_q0;
    mat4x4[7] = 0.0f;

    mat4x4[8] = q1_q3 - q2_q0;
    mat4x4[9] = q2_q3 + q1_q0;
    mat4x4[10] = 1 - sq_q1 - sq_q2;
    mat4x4[11] = 0.0f;

    mat4x4[12] = mat4x4[13] = mat4x4[14] = 0.0f;
    mat4x4[15] = 1.0f;
}

// functions by Elliot Woods
ofVec3f QuatToEuler(const ofQuaternion& rotation)
{
    ofVec3f euler;
    const static double PI_OVER_2 = PI * 0.5;
    const static double EPSILON = 1e-10;
    double sqw, sqx, sqy, sqz;

    // quick conversion to Euler angles to give tilt to user
    sqw = rotation[3] * rotation[3];
    sqx = rotation[0] * rotation[0];
    sqy = rotation[1] * rotation[1];
    sqz = rotation[2] * rotation[2];

    euler[1] = asin(2.0 * (rotation[3] * rotation[1] - rotation[0] * rotation[2]));
    if (PI_OVER_2 - fabs(euler[1]) > EPSILON) {
        euler[2] = atan2(2.0 * (rotation[0] * rotation[1] + rotation[3] * rotation[2]),
            sqx - sqy - sqz + sqw);
        euler[0] = atan2(2.0 * (rotation[3] * rotation[0] + rotation[1] * rotation[2]),
            sqw - sqx - sqy + sqz);
    }
    else {
        // compute heading from local 'down' vector
        euler[2] = atan2(2 * rotation[1] * rotation[2] - 2 * rotation[0] * rotation[3],
            2 * rotation[0] * rotation[2] + 2 * rotation[1] * rotation[3]);
        euler[0] = 0.0;

        // If facing down, reverse yaw
        if (euler[1] < 0)
            euler[2] = PI - euler[2];
    }
    return euler;
}

ofQuaternion EulerToQuat(const ofVec3f& rotationEuler)
{
    ofQuaternion rotation;

    float c1 = cos(rotationEuler[2] * 0.5);
    float c2 = cos(rotationEuler[1] * 0.5);
    float c3 = cos(rotationEuler[0] * 0.5);
    float s1 = sin(rotationEuler[2] * 0.5);
    float s2 = sin(rotationEuler[1] * 0.5);
    float s3 = sin(rotationEuler[0] * 0.5);

    rotation[0] = c1 * c2 * s3 - s1 * s2 * c3;
    rotation[1] = c1 * s2 * c3 + s1 * c2 * s3;
    rotation[2] = s1 * c2 * c3 - c1 * s2 * s3;
    rotation[3] = c1 * c2 * c3 + s1 * s2 * s3;

    return rotation;
}
