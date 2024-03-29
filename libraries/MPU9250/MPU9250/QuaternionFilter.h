#pragma once
#ifndef QUATERNIONFILTER_H
#define QUATERNIONFILTER_H

#define RAD2DEG	57.2957795130823208767
#define DEG2RAD	0.01745329251994329576

enum QuatFilterSel {
    NONE,
    MADGWICK,
    MAHONY,
};

class QuaternionFilter {
    // for madgwick
    double GyroMeasError = PI * (40.0f / 180.0f);     // gyroscope measurement error in rads/s (start at 40 deg/s)
    double GyroMeasDrift = PI * (0.0f / 180.0f);      // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
    double beta = 0.25f;  // compute beta
    double zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;  // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value

	//beta = 0.25f;
	
    // for mahony
    float Kp = 30.0;
    float Ki = 0.0;
	
	QuatFilterSel filter_sel = QuatFilterSel::MADGWICK;

    double deltaT = 0;
    uint32_t newTime{0};
    uint32_t oldTime{0};
	double yaw = 0.0, pitch = 0.0, roll = 0.0;
	double yawOffset = 0.0, pitchOffset = 0.0, rollOffset = 0.0;

public:
    void select_filter(QuatFilterSel sel) {
        filter_sel = sel;
    }

	float invSqrt(float x)
    {
      float halfx = 0.5f * x;
      float y = x;
      long i = *(long*)&y;
      i = 0x5f3759df - (i>>1);
      y = *(float*)&i;
      y = y * (1.5f - (halfx * y * y));
      return y;
    }
	
    void update(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float* q) {
        newTime = micros();
        deltaT = newTime - oldTime;
        oldTime = newTime;
        deltaT = fabs(deltaT * 0.001 * 0.001);
		//deltaT = 0.005;

        switch (filter_sel) {
            case QuatFilterSel::MADGWICK:
                //madgwick(ax, ay, az, gx, gy, gz, mx, my, mz, q);
				madgwick(gx, gy, gz, ax, ay, az, q);
                break;
            case QuatFilterSel::MAHONY:
                mahony(ax, ay, az, gx, gy, gz, mx, my, mz, q);
                break;
            default:
                no_filter(ax, ay, az, gx, gy, gz, mx, my, mz, q);
                break;
        }
    }

    void no_filter(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float* q) {
        float q0 = q[0], q1 = q[1], q2 = q[2], q3 = q[3];  // variable for readability
        q[0] += 0.5f * (-q1 * gx - q2 * gy - q3 * gz) * deltaT;
        q[1] += 0.5f * (q0 * gx + q2 * gz - q3 * gy) * deltaT;
        q[2] += 0.5f * (q0 * gy - q1 * gz + q3 * gx) * deltaT;
        q[3] += 0.5f * (q0 * gz + q1 * gy - q2 * gx) * deltaT;
        float recipNorm = 1.0 / sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
        q[0] *= recipNorm;
        q[1] *= recipNorm;
        q[2] *= recipNorm;
        q[3] *= recipNorm;
    }

    // Madgwick Quaternion Update
    void madgwick(float xg, float yg, float zg, float xa, float ya, float za, float* q)
{
  static uint32_t old_time;
  uint32_t real_time;
  static double _time;
  float q0 = q[0];
  float q1 = q[1];
  float q2 = q[2];
  float q3 = q[3];
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

  /*real_time = time_service::getCurTime();
  _time = (time_service::getCurTime() - old_time) / 1000.0;
  old_time = time_service::getCurTime();*/
  //_time = 0.001;
	_time = deltaT;
  
	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * xg - q2 * yg - q3 * zg);
	qDot2 = 0.5f * (q0 * xg + q2 * zg - q3 * yg);
	qDot3 = 0.5f * (q0 * yg - q1 * zg + q3 * xg);
	qDot4 = 0.5f * (q0 * zg + q1 * yg - q2 * xg);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((xa == 0.0f) && (ya == 0.0f) && (za == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(xa * xa + ya * ya + za * za);
		xa *= recipNorm;
		ya *= recipNorm;
		za *= recipNorm;   

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * xa + _4q0 * q1q1 - _2q1 * ya;
		s1 = _4q1 * q3q3 - _2q3 * xa + 4.0f * q0q0 * q1 - _2q0 * ya - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * za;
		s2 = 4.0f * q0q0 * q2 + _2q0 * xa + _4q2 * q3q3 - _2q3 * ya - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * za;
		s3 = 4.0f * q1q1 * q3 - _2q1 * xa + 4.0f * q2q2 * q3 - _2q2 * ya;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback stepcorrect
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}
	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * _time;
	q1 += qDot2 * _time;
	q2 += qDot3 * _time;
	q3 += qDot4 * _time;

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	//recipNorm = 1 / sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
  q[0] = q0;
  q[1] = q1;
  q[2] = q2;
  q[3] = q3;
  
	pitch = asin(2*(q0*q2 - q3*q1));
	roll = atan2(2*(q0*q1 + q2*q3), 1 - 2*(q1*q1 + q2*q2));
	yaw = atan2(2*(q0*q3 + q1*q2), 1 - 2*(q2*q2 + q3*q3));
  
  pitch = pitch * RAD2DEG - pitchOffset;
  roll = roll * RAD2DEG - rollOffset;
  yaw = yaw * RAD2DEG;// - yawOffset;
  
}

    // Mahony accelleration filter
    // Mahony scheme uses proportional and integral filtering on
    // the error between estimated reference vector (gravity) and measured one.
    // Madgwick's implementation of Mayhony's AHRS algorithm.
    // See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
    // Free parameters in the Mahony filter and fusion scheme,
    // Kp for proportional feedback, Ki for integral
    // float Kp = 30.0;
    // float Ki = 0.0;
    // with MPU-9250, angles start oscillating at Kp=40. Ki does not seem to help and is not required.
    // with MPU-6050, some instability observed at Kp=100 Now set to 30.
    void mahony(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float* q) {
        float recipNorm;
        float vx, vy, vz;
        float ex, ey, ez;  //error terms
        float qa, qb, qc;
        static float ix = 0.0, iy = 0.0, iz = 0.0;  //integral feedback terms
        float tmp;

        // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
        tmp = ax * ax + ay * ay + az * az;
        if (tmp > 0.0) {
            // Normalise accelerometer (assumed to measure the direction of gravity in body frame)
            recipNorm = 1.0 / sqrt(tmp);
            ax *= recipNorm;
            ay *= recipNorm;
            az *= recipNorm;

            // Estimated direction of gravity in the body frame (factor of two divided out)
            vx = q[1] * q[3] - q[0] * q[2];
            vy = q[0] * q[1] + q[2] * q[3];
            vz = q[0] * q[0] - 0.5f + q[3] * q[3];

            // Error is cross product between estimated and measured direction of gravity in body frame
            // (half the actual magnitude)
            ex = (ay * vz - az * vy);
            ey = (az * vx - ax * vz);
            ez = (ax * vy - ay * vx);

            // Compute and apply to gyro term the integral feedback, if enabled
            if (Ki > 0.0f) {
                ix += Ki * ex * deltaT;  // integral error scaled by Ki
                iy += Ki * ey * deltaT;
                iz += Ki * ez * deltaT;
                gx += ix;  // apply integral feedback
                gy += iy;
                gz += iz;
            }

            // Apply proportional feedback to gyro term
            gx += Kp * ex;
            gy += Kp * ey;
            gz += Kp * ez;
        }

        // Integrate rate of change of quaternion, q cross gyro term
        deltaT = 0.5 * deltaT;
        gx *= deltaT;  // pre-multiply common factors
        gy *= deltaT;
        gz *= deltaT;
        qa = q[0];
        qb = q[1];
        qc = q[2];
        q[0] += (-qb * gx - qc * gy - q[3] * gz);
        q[1] += (qa * gx + qc * gz - q[3] * gy);
        q[2] += (qa * gy - qb * gz + q[3] * gx);
        q[3] += (qa * gz + qb * gy - qc * gx);

        // renormalise quaternion
        recipNorm = 1.0 / sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
        q[0] = q[0] * recipNorm;
        q[1] = q[1] * recipNorm;
        q[2] = q[2] * recipNorm;
        q[3] = q[3] * recipNorm;
    }
	
	float returnYaw() {
		return yaw;
	}
	
	float returnPitch() {
		return pitch;
	}
	
	float returnRoll() {
		return roll;
	}
};

#endif  // QUATERNIONFILTER_H
