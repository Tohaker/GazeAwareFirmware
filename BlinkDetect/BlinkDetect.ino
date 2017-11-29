void setup() 
{
  // initialise serial port
  Serial.begin(9600);
  // set LED as our output
  pinMode(13, OUTPUT);
  // wait until the port has been setup
  while(!Serial);
  // tell the user the arduino is ready
  Serial.write("ready");
}

void loop() 
{
  if (Serial.available())
  {
    int state = Serial.parseInt();
    // look for the state requested
    if (state == 1)
    {     
      digitalWrite(13, HIGH);
    }
    else if (state == 0)
    {
      digitalWrite(13, LOW);
    }
  }
}
