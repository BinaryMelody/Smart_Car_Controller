#define IN1 2
#define IN2 7
#define EN12 10
#define IN3 5
#define IN4 6
#define EN34 12
#define signal 19

String inString = "";
int duty = 7850;
float aa = 1.0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN12,OUTPUT);
  
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(EN34,OUTPUT);
  
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  analogWrite(EN12,0);
  analogWrite(EN34,90);
  
}

char data = ' ';

void loop()
{
  while(Serial.available() > 0){
    inString += char(Serial.read());
    delay(2);
  }
  if(inString.length() > 0){
    check();
    inString = "";
  }
}

void PWM(int a, int b){
  analogWrite(EN12, a);
  analogWrite(EN34, b);
}

void check(){
  if('0'<=inString[0] && inString[0]<='9') { accelerate(); return;}
  switch(inString[0]){
    case 'u': u(); break;
    case 'l': l(); break;
    case 'r': r(); break;
    case 'd': d(); break;
    case 's': s(); break;
    case 'g': g(); break;
    case 'm': ml(); break;
    case 'n': nr(); break;
  }
}

void u(){
  PWM(140,180);
  go();
}

void l(){
  PWM(140,180);
  left();
}

void ml(){
  PWM(0,180);
  go();
}

void nr(){
  PWM(140,0);
  go();
}

void r(){
  PWM(140,180);
  right();
}

void d(){
  PWM(140,180);
  back();
}

void s(){
  PWM(0,0);
  park();
}

void g(){
  int a = 68, b = 85, c = 1;
  switch(inString[1]){
    case 'u': go(); break;
    case 'd': back(); break; 
  }
  switch(inString[2]){
    case '1': c = 1; break;
    case '2': c = 2; break;
    case '3': c = 3; break;
  }
  a *= c;
  b *= c;
  switch(inString[3]){
    case 'n': break;
    case 'l': a = 0; break;
    case 'r': b = 0; break;
  }
  
  /*switch(inString[2]){
    case '1': break;
    case '2': a*=3; b*=3; break;
    case '3': a*=6; b*=6; break;
  }
  switch(inString[3]){
    case '1': c = 2; break;
    case '2': c = 3; break;
  }
  switch(inString[4]){
    case 'l': a = 0; break;
    case 'r': b = 0; break;
    case 'n': break;
  }*/
  PWM(a,b);
}

void accelerate(){
  int a=0, i=0, b=0;
  for(i=0; i<inString.length(); ++i){
    a = a * 10 + inString[i] - '0';
  }
  b = a * 70 / 90;
  PWM(b,a);
  go();
}

void go(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void back(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void park(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
/*  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    data = Serial.read();
    if(data == 'u'){
      //duty = 7850*(aa-0.1);
      //turn1();
      gohead();
      delay(1000);
      //Serial.read();
    }
    else if(data == 'l'){
      turnLeft();
      delay(1000);
      //Serial.read();
    }
    else if(data == 'r'){
      turnRight();
      delay(1000);
      //Serial.read();
    }
    else if(data =='d'){
      //duty=7850*(aa+0.1);
      //turn();
      goback();
      delay(1000);
      //Serial.read();
    }
    else if(data == 'p'){
      park();
      delay(1000);
    }
    else if(data == 'a'){
      left();
    }
    else if(data == 'b'){
      right();
    }
    else if(data == 't'){
      turn();
    }
    else if(data =='u'){
      turn1();
    }
  }
}*/
/*
void left()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  delay(2000);
   digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void right()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(1700);
   digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}
void turn()
{duty=8850;//8200
  for (int i=0; i<100; i++) {
  digitalWrite(signal,LOW);
  delayMicroseconds(duty);
  digitalWrite(signal,HIGH);
  delayMicroseconds(10000-duty);
  }
}

void turn1()
{duty = 7500;
  for (int i=0; i<200; i++) {
  digitalWrite(signal,LOW);
  delayMicroseconds(duty);
  digitalWrite(signal,HIGH);
  delayMicroseconds(10000-duty);
  }
}

void gohead()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void turnLeft()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

void turnRight()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void goback()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void park()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}*/
