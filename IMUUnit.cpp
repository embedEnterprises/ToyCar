
#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);
volatile int mpu_angle = 0;
volatile int prev_angle = 0;
uint8_t MMM;
float current, first;

TaskHandle_t ImuTask;

void mpu_loop(void* pvParameters) {
  while (1) {
    for (int i = 0; i < 10; i++) {
      mpu6050.update();
      current = mpu6050.getAngleZ();
      mpu_angle = (first - current) * 1.1;
    }

    mpu6050.update();
    current = mpu6050.getAngleZ();
    mpu_angle = (first - current) * 1.1;
    if (prev_angle != mpu_angle) {
      Serial.print("mpu_angle: ");
      Serial.println(mpu_angle);
      prev_angle = mpu_angle;
    }
    //  Serial.println(encoder_counts);
  }
}

void setupIMU() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  mpu6050.begin();

  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  first = mpu6050.getAngleZ();
  xTaskCreatePinnedToCore(
    mpu_loop,  /* Task function. */
    "ImuTask", /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &ImuTask,  /* Task handle to keep track of created task */
    0          /* pin task to core 0 */
  );
}

int getImuAngle() {
  return mpu_angle;
}
