//Distance Sensor
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

//button code defines
#define buttonPin 4
#define ledPin 13 
#define D 5
#define NUMBER_OF_STEPS_PER_REV 512

// defines variables 
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

// Sensor Vars.
int sw=0, psw=0,count=1, sum=0;
int td = 5; // the distancs between the sensor rnd the turbain
unsigned int curT = 0,preT =0;
double f;
int dt;
double avg=0,RoundPerSec;
int delaytime = 100;
int temp = 0;

// Button variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonflag_1=0,buttonflag_2=0;
int countB=0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
//  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
//  Serial.println("with Arduino UNO R3");

  //button setup
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(D,OUTPUT);
}

void write(int d){
  digitalWrite(D,d);
}

void onestep(){
  write(0);
  //delay(100);
  write(1);
}

void buttonFunc() {
  // read the state of the pushbutton value:  
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    buttonflag_1= 1 ;
  }
  if(buttonflag_1 != buttonflag_2 && buttonflag_1 == 1 )
    countB++;
  buttonflag_2 = buttonflag_1;    
  buttonflag_1=0;

  if (countB%2==0){
    digitalWrite(ledPin, HIGH);// turn LED on:
    int i;
    i=0;
    while(i<NUMBER_OF_STEPS_PER_REV){
      onestep();
      i++;
    }
  }
  else {
    digitalWrite(ledPin, LOW); //turn LED off:
  }
  //Serial.println(countB);  
}
 
void SensorFunc(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delay(delaytime);// mesur D every 1 ms  TODO chane the delay time
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)


  // toggle sw
  if(distance <= td)
      sw = 1;
  else
      sw = 0;

  // updates count exactly once per change form 0 to 1
  if(sw!=psw && sw == 1)
    count++;

  psw=sw;

  
  // updating curT for 1 cycle
  if(count>=4){
    curT = millis();
    count=0;
  }

  if(curT-preT>0){
    dt=curT-preT;
    preT=curT;
   }
   
//  Serial.print("curT: ");
//  Serial.print(curT);
//  Serial.print(" preT: ");
//  Serial.println(preT);

  f=1000/(double)dt; // freq
  Serial.print("f: ");
  Serial.println(f);
  RoundPerSec = 1000*f ;

 // calculate the freq average
 sum = sum + f;
 avg = sum/count;



 
 //count++; 
    //Serial.print("sum ");
    //Serial.println(sum);

 
 //Serial.print("Round Per Sec : ");
 //Serial.println(RoundPerSec);

//  if(count >= delaytime*1){
//     Serial.print("Running Avg. RPS for delytime: ");
//     Serial.println(avg);
//      sum=0;
//      count=1;
//      curT=0;
//      preT=0;
//  }
 
  // Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
}

void loop() {

  buttonFunc();
  SensorFunc();

}