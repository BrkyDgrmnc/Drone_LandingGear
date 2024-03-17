
/*RC Input Pin*******************************/
#define RC_PIN          2                 /**/
/********************************************/

/*Motor Limit Switches***********************/
#define LSW_2           3                   //
#define LSW_1           4                   //
#define RSW_2           6                   //
#define RSW_1           7                   //
/********************************************/

/*Motor Direction Select Pins****************/
#define ROutA           12                  //
#define ROutB           13                  //
/*------------------------------------------*/
#define LOutA           10                  //
#define LOutB           11                  //
/********************************************/

#define TimeOutR        500
#define TimeOutL        500

unsigned int rcsignal = 1500;


unsigned long lastTimeR = 0;
bool j = true;
bool k = true;

unsigned long lastTimeL = 0;
bool i = true;
bool l = true;


void gearUp(int out_a , int out_b){
  digitalWrite(out_a, HIGH);
  digitalWrite(out_b, LOW);
}

void gearDown(int out_a , int out_b){
  digitalWrite(out_a, LOW);
  digitalWrite(out_b, HIGH);
}

void gearStop(int out_a , int out_b){
  digitalWrite(out_a, HIGH);
  digitalWrite(out_b, HIGH);
}

void GearLeft(){

  if(digitalRead(LSW_2) && rcsignal < 1400)
  {
    gearUp(LOutA , LOutB);
    i = true;
    k = true;
  }

  else if(digitalRead(LSW_1) && rcsignal > 1700)
  {
    gearDown(LOutA , LOutB);
    i = true;
    k = true;
  }

  else
  {
    if((!digitalRead(LSW_1) || !digitalRead(LSW_2)) && i)
    {
      lastTimeL = millis();
      i = false;
    } 
    if((millis() - lastTimeL) > TimeOutL && k)
    {  
      gearStop(LOutA , LOutB);
      k = false;
    } 
  }
}

void GearRight(){
    
  if(digitalRead(RSW_2) && rcsignal < 1400)
  {
    gearUp(ROutA , ROutB);
    j = true;
    l = true;
  }

  else if(digitalRead(RSW_1) && rcsignal > 1700)
  {
    gearDown(ROutA , ROutB);
    j = true;
    l = true;
  }
  
  else 
  {  
    if((!digitalRead(RSW_1) || !digitalRead(RSW_2)) && j )
    {
      lastTimeR = millis();
      j = false;
    }
    
    if((millis() - lastTimeR) > TimeOutR && l)
    {  
      gearStop(ROutA , ROutB);
      l = false;
    }
  }
}
  
void setup() {
  pinMode(RSW_1, INPUT_PULLUP);
  pinMode(RSW_2, INPUT_PULLUP);
  pinMode(LSW_1, INPUT_PULLUP);
  pinMode(LSW_2, INPUT_PULLUP);
  
  pinMode(RC_PIN, INPUT);      
  
  pinMode(ROutA, OUTPUT);
  pinMode(ROutB, OUTPUT);
  pinMode(LOutA, OUTPUT);
  pinMode(LOutB, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  gearStop(ROutA , ROutB);
  gearStop(LOutA , LOutB);
  
  //Serial.begin(115200);
}

void loop() {
  
  rcsignal = pulseIn(RC_PIN, HIGH);
  //Serial.println(rcsignal);
  GearLeft();
  GearRight();
}
