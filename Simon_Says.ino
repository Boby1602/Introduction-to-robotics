/// SIMON SAYS

unsigned long lastDebounceTimeL=0;
unsigned long lastDebounceTimeM=0;
unsigned long lastDebounceTimeR=0;

const int buttonState=1;
int PLBS=0,PMBS=0,PRBS=0;//PLBS= previous left button state, so is PMBS and PRBS
volatile bool possiblePressL=false;
volatile bool shouldStartCounterL=false;

volatile bool possiblePressM=false;
volatile bool shouldStartCounterM=false;

volatile bool possiblePressR=false;
volatile bool shouldStartCounterR=false;

const int debounceDelay=50;

const int LPin = 8;  //Left led
const int MPin = 7; //Middle led
const int RPin = 6; //Right led

const int GreenPin = 2;
const int YellowPin = 3;
const int RedPin = 4;

const int LButton = 13;//Left Button
const int MButton = 12;//Middle Button
const int RButton = 11;//Right Button

int simon_count=-1;
int Difficulty=1500;

int simon_sequence[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int player_sequence[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

bool game_start = false;

int winner=1;
unsigned long current_time;
int LBState=1;
int RBState=1;//same thing for PMBS and PRBS
int MBState=1;

int i;

void setup() {
  pinMode(LPin, OUTPUT);
  pinMode(RPin, OUTPUT);
  pinMode(MPin, OUTPUT);
  pinMode(LButton, INPUT_PULLUP);
  pinMode(MButton, INPUT_PULLUP);
  pinMode(RButton, INPUT_PULLUP);
  pinMode(GreenPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  digitalWrite(LPin, LOW);
  digitalWrite(MPin, LOW);
  digitalWrite(RPin, LOW);
  digitalWrite(RedPin, LOW);
  digitalWrite(GreenPin, LOW);
  digitalWrite(YellowPin, LOW);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  /*
  attachInterrupt(digitalPinToInterrupt(LButton),handleInterruptL,FALLING);
  attachInterrupt(digitalPinToInterrupt(MButton),handleInterruptM,FALLING);
  attachInterrupt(digitalPinToInterrupt(RButton),handleInterruptR,FALLING);
  */
}

void loop() {
  current_time=millis();
  if(simon_count == -1) // If it is the first round
  { while(millis()-current_time<1000)
      digitalWrite(RedPin,LOW);
    digitalWrite(RedPin, HIGH);
    while(millis()-current_time<3000)
      digitalWrite(YellowPin, LOW);
    digitalWrite(YellowPin,HIGH);
    while(millis()-current_time<5000)
      digitalWrite(GreenPin, LOW);
    digitalWrite(GreenPin, HIGH);
    while(millis()-current_time<10000)
      digitalWrite(GreenPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(YellowPin, LOW);
    digitalWrite(RedPin, LOW);
  }
  if(simon_count<9)
    simon_count++;
  for(i=0;i<=simon_count;i++)
    simon_sequence[i]=random(1,4); 
  
  
  for(i=0;i<=simon_count;i++){
    current_time=millis();
    while(millis()-current_time<Difficulty)
    { if(simon_sequence[i]==1){
        
        digitalWrite(LPin,HIGH);
      }
      if(simon_sequence[i]==2){
        digitalWrite(MPin,HIGH);
      }    
      if(simon_sequence[i]==3){
        digitalWrite(RPin,HIGH);
      }
    }
    digitalWrite(LPin,LOW);
    digitalWrite(MPin,LOW);
    digitalWrite(RPin,LOW);
    delay(100);
  }
  i=0;
  while(player_sequence[simon_count] == -1)
  {
    /*
    if(possiblePressL){
      if(shouldStartCounterL){
        lastDebounceTimeL=millis();
        shouldStartCounterL=false;
      }

    }
    if(millis()-lastDebounceTimeL>debounceDelay){
      LBState=digitalRead(LButton);

      if (LBState!=buttonState)
      {
        if(LBState==0)
        {
          player_sequence[i]= 1;
          i++;
          for(int j=0;j<=9;j++)
            Serial.println(player_sequence[j]);
          
        }
      }
    }
    possiblePressL=false;

    if(possiblePressM){
      if(shouldStartCounterM){
        lastDebounceTimeM=millis();
        shouldStartCounterM=false;
      }

    }
    if(millis()-lastDebounceTimeM>debounceDelay){
      MBState=digitalRead(MButton);

      if (MBState!=buttonState)
      {
        if(MBState==LOW)
        {
          player_sequence[i]= 2;
          i++;
          for(int j=0;j<=9;j++)
            Serial.println(player_sequence[j]);
        }
      }
    }
    possiblePressM=false;
    
    if(possiblePressR){
      if(shouldStartCounterR){
        lastDebounceTimeR=millis();
        shouldStartCounterR=false;
      }

    }
    if(millis()-lastDebounceTimeR>debounceDelay){
      RBState=digitalRead(RButton);

      if (RBState!=buttonState)
      {
        if(RBState==LOW)
        {
          player_sequence[i]= 3;
          i++;
          for(int j=0;j<=9;j++)
            Serial.println(player_sequence[j]);
        }
      }
    }
    possiblePressR=false;
    */
    
    LBState=digitalRead(LButton);
    MBState=digitalRead(MButton);
    RBState=digitalRead(RButton);
    
    digitalWrite(LPin,!LBState);
    digitalWrite(MPin,!MBState);
    digitalWrite(RPin,!RBState);
    
    if(LBState == 0 && PLBS == 1)
    {
      player_sequence[i] = 1;
      i++;
     
      delay(100);
    }
    
    if(MBState == 0 && PMBS == 1)
    {
      player_sequence[i] = 2;
      i++;
      
      delay(100);
    }

    if(RBState == 0 && PRBS == 1)
    {
      player_sequence[i] = 3;
      i++;
      delay(100);
    }
    PLBS=LBState;
    PMBS=MBState;
    PRBS=RBState;
    

  }
  digitalWrite(LPin,LOW);
  digitalWrite(RPin,LOW);
  digitalWrite(MPin,LOW);
  for (i = 0; i <=simon_count; i++) {
    if (simon_sequence[i] != player_sequence[i]) {
      winner = 0; // Vectors are not equal
    }
  }
  if (winner){
    current_time=millis();
    while(millis()-current_time<2000)
      digitalWrite(GreenPin,HIGH);
   digitalWrite(GreenPin,LOW);
  }   
  else{
    current_time=millis();
    while(millis()-current_time<2000)
      digitalWrite(RedPin,HIGH);
    digitalWrite(RedPin,LOW);
    simon_count=-1;
    winner=1;
  }
  
  for(i=0;i<9;i++)
    simon_sequence[i]=-1; 
  for(i=0;i<10;i++)
    player_sequence[i]=-1; 
  if(simon_count==9)
  {
    digitalWrite(YellowPin,HIGH);
    delay(3000);
    Difficulty/=2;
    simon_count=-1;
  }
  digitalWrite(YellowPin,LOW);
}
/*
void handleInterruptL(){
  possiblePressL=true;
  shouldStartCounterL=true;
}

void handleInterruptM(){
  possiblePressM=true;
  shouldStartCounterM=true;
}

void handleInterruptR(){
  possiblePressR=true;
  shouldStartCounterR=true;
}
*/