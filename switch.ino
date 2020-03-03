
#include <Nextion.h> 
NexDSButton bt0 = NexDSButton(1, 1, "bt0");
NexDSButton bt1 = NexDSButton(1, 2, "bt1");
NexDSButton bt2 = NexDSButton(1, 3, "bt2");
NexDSButton bt3 = NexDSButton(1, 4, "bt3");
NexDSButton bt4 = NexDSButton(1, 5, "bt4");
NexDSButton bt5 = NexDSButton(1, 6, "bt5");
NexDSButton bt6 = NexDSButton(1, 7, "bt6");
NexDSButton bt7 = NexDSButton(1, 8, "bt7");
NexTouch *nex_listen_list[] = 
{
  &bt0,
  &bt1,
  &bt2,
  &bt3,
  &bt4,
  &bt5,
  &bt6,
  &bt7, 
  NULL
};
void bt0PushCallback(void *ptr)
{
  uint32_t state = 0; 
  bt0.getValue(&state);
  if(state == 1){ 
    digitalWrite(2, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(2, LOW);  // Turn OFF 
  }
}  
void bt1PushCallback(void *ptr)
{
  uint32_t state1 = 0; 
  bt1.getValue(&state1);
  if(state1 == 1){ 
    digitalWrite(3, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(3, LOW);  // Turn OFF 
  }
} 
void bt2PushCallback(void *ptr)
{
  uint32_t state2 = 0; 
  bt2.getValue(&state2);
  if(state2 == 1){ 
    digitalWrite(4, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(4, LOW);  // Turn OFF 
  }
}
void bt3PushCallback(void *ptr)
{
  uint32_t state3 = 0; 
  bt3.getValue(&state3);
  if(state3 == 1){ 
    digitalWrite(5, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(5, LOW);  // Turn OFF 
  }
}  
void bt4PushCallback(void *ptr)
{
  uint32_t state4 = 0; 
  bt4.getValue(&state4);
  if(state4 == 1){ 
    digitalWrite(6, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(6, LOW);  // Turn OFF 
  }
}
void bt5PushCallback(void *ptr)
{
  uint32_t state5 = 0; 
  bt5.getValue(&state5);
  if(state5 == 1){ 
    digitalWrite(7, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(7, LOW);  // Turn OFF 
  }
}
void bt6PushCallback(void *ptr)
{
  uint32_t state6 = 0; 
  bt6.getValue(&state6);
  if(state6 == 1){ 
    digitalWrite(8, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(8, LOW);  // Turn OFF 
  }
}
void bt7PushCallback(void *ptr)
{
  uint32_t state7 = 0; 
  bt7.getValue(&state7);
  if(state7 == 1){ 
    digitalWrite(9, HIGH);  // Turn ON 
  }
  else{  
    digitalWrite(9, LOW);  // Turn OFF 
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt0.attachPush(bt0PushCallback);
  bt1.attachPush(bt1PushCallback);
  bt2.attachPush(bt2PushCallback);
  bt3.attachPush(bt3PushCallback);
  bt4.attachPush(bt4PushCallback);
  bt5.attachPush(bt5PushCallback);
  bt6.attachPush(bt6PushCallback);
  bt7.attachPush(bt7PushCallback);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);
}
