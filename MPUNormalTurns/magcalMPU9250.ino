void magcalMPU9250(float* dest1, float* dest2) 
 {
 uint16_t ii = 0, sample_count = 0;
 int32_t mag_bias[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
 int16_t mag_max[3] = {0x8000, 0x8000, 0x8000}, mag_min[3] = {0x7FFF, 0x7FFF, 0x7FFF}, mag_temp[3] = {0, 0, 0};

 Serial.println("Mag Calibration: Wave device in a figure eight until done!");

 sample_count = 128;
 for(ii = 0; ii < sample_count; ii++) {
 readMagData(mag_temp);  // Read the mag data   
 for (int jj = 0; jj < 3; jj++) {
  if(mag_temp[jj] > mag_max[jj]) mag_max[jj] = mag_temp[jj];
  if(mag_temp[jj] < mag_min[jj]) mag_min[jj] = mag_temp[jj];
 }
 delay(135);  // at 8 Hz ODR, new mag data is available every 125 ms
 }

// Get hard iron correction
 mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
 mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
 mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts

 dest1[0] = (float) mag_bias[0]*mRes*magCalibration[0];  // save mag biases in G for main program
 dest1[1] = (float) mag_bias[1]*mRes*magCalibration[1];   
 dest1[2] = (float) mag_bias[2]*mRes*magCalibration[2];  

// Get soft iron correction estimate
 mag_scale[0]  = (mag_max[0] - mag_min[0])/2;  // get average x axis max chord length in counts
 mag_scale[1]  = (mag_max[1] - mag_min[1])/2;  // get average y axis max chord length in counts
 mag_scale[2]  = (mag_max[2] - mag_min[2])/2;  // get average z axis max chord length in counts

 float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
 avg_rad /= 3.0;

 dest2[0] = avg_rad/((float)mag_scale[0]);
 dest2[1] = avg_rad/((float)mag_scale[1]);
 dest2[2] = avg_rad/((float)mag_scale[2]);

 Serial.println("Mag Calibration done!");
 Serial.println(mag_bias[0]);
 Serial.println(mag_bias[1]);
 Serial.println(mag_bias[2]);
 Serial.println(dest1[0]);
 Serial.println(dest1[1]);
 Serial.println(dest1[2]);

 Serial.println(mag_scale[0]);
 Serial.println(mag_scale[1]);
 Serial.println(mag_scale[2]);
 Serial.println(dest2[0]);
 Serial.println(dest2[1]);
 Serial.println(dest2[2]);

 Serial.println(avg_rad);

 Serial.println(mag_temp[0]);
 Serial.println(mag_temp[1]);
 Serial.println(mag_temp[2]);

 Serial.println(mag_max[0]);
 Serial.println(mag_max[1]);
 Serial.println(mag_max[2]);

 Serial.println(mag_min[0]);
 Serial.println(mag_min[1]);
 Serial.println(mag_min[2]);
 delay(2000);

 /*818
-2239
4776
1461.26
-4025.94
8252.03
165
170
225
1.13
1.10
0.83
186.67
794
-2280
4598
984
-2069
5001
653
-2410
4551*/


/*854
-2227
4827
1525.57
-4004.36
8340.15
227
240
337
1.18
1.12
0.80
268.00
874
-2004
4650*/

/* 818
-2239
4776
1461.26
-4025.94
8252.03
165
170
225
1.13
1.10
0.83
186.67
794
-2280
4598
984
-2069
5001
653
-2410
4551*/

/*mag_bias[0] = 854;
mag_bias[1] = -2227;
mag_bias[2] = 4776;
dest1[0] = 1525.57;
dest1[1] = -4004.36;
dest1[2] = 8250.15;
mag_scale[0] = 165;
mag_scale[1] = 170;
mag_scale[2] = 225;
dest2[0] = 1.13;
dest2[1] = 1.10;
dest2[2] = 0.83;
float avg_rad = 186.00;
mag_temp[0] = 794;
mag_temp[1] = -2280;
mag_temp[2] = 4650;
mag_max[0] = 984;
mag_max[1] = -2069;
mag_max[2] = 5001;
mag_min[0] = 653;
mag_min[1] = -2410;
mag_min[2] = 4551;*/


/*1286
-387
236
2297.29
-695.86
407.76
147
119
48
0.71
0.88
2.18
104.67
1230
-352
216*/

 }
