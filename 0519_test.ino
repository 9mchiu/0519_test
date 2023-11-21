/* BR system_moving average method */

// L293D Motor controller
int enb = 9;
int in1 = 10; // L293D Pin_in1 connect to arduino Pin_10
int in2 = 11; // L293D Pin_in2 connect to arduino Pin_10

//Honeywell pressure sensor
int PIN_PRESSURE = A2; //pressure sensor接腳
int FLOWMETER = A3;
int FAN_PRESSURE = A5; //濾材前壓力接腳


//const int PRESSURE_LO = 459;
//const int PRESSURE_HI = 501;
const int PRESSURE_LO = 455;
const int PRESSURE_HI = 490;
//const int PRESSURE_LO = 475;
//const int PRESSURE_HI = 510;

//const int PRESSURE_ATM =516;
//const int PRESSURE_RESTART = 460; // -5 mmH2O

// 風扇最大最小
#define FAN_MIN 5
#define FAN_MAX 255


//移動平均
//const int numReading = 5;
//int reading[numReading]; // numdata個整數元素的陣列reading。實際上有reading[0]~reading[numdata-1] 個元素
//int index = 0;
//int total = 0;
//int average = 0;
//int fan = 1;

void setup() {
  Serial.begin(9600);
  // Set all the motor control pins to outputs
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(PIN_PRESSURE, INPUT);
  pinMode(FAN_PRESSURE, INPUT);
  pinMode(FLOWMETER, INPUT);
  //   pinMode(led, OUTPUT);
  // 初始化 motor & light
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //   digitalWrite(led, LOW);

}

void loop() {
  //read pressure sensor signal
  int fan = 0;
  int sensorValue = analogRead(PIN_PRESSURE);
  int flowmeterValue = analogRead(FLOWMETER);
  int fanpressureValue = analogRead(FAN_PRESSURE);
  // 移除最舊的data，加入最新的data進去陣列中
//  total = total - reading[index]; //減掉最舊的 index = 0
//  reading[index] = sensorValue;
//  total = total + reading[index];

  // 移動index的位置
//  index = (index + 1) % numReading;

  // 計算平均值
//  average = total / numReading;

  // 把平均值代入方程式
  if (sensorValue >= PRESSURE_LO && sensorValue <= PRESSURE_HI) {
    fan = (7.1429 * sensorValue - 3245); //455 490
//    fan = (7.1429 * average - 3387.9); //475 510

  }

  else if (sensorValue < PRESSURE_LO) {
    fan = FAN_MIN;
  }

  else if (sensorValue > PRESSURE_HI) {
    fan = FAN_MAX;
  }

  //把平均值送到風扇
  analogWrite(enb, fan);

  fan = fan > FAN_MAX ? FAN_MAX : fan < FAN_MIN ? FAN_MIN : fan;

  // print fan數值
  //  Serial.print(fan);
  //  Serial.print(",");
  //  Serial.print(flowValue);
  //  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",   ");
//    Serial.println(average);
//    Serial.print(",");
  //  Serial.println(fan);
  Serial.print(flowmeterValue);
  Serial.print(",   ");
  Serial.println(fanpressureValue);
  // 延遲
  delay(1); //20 左右

}
