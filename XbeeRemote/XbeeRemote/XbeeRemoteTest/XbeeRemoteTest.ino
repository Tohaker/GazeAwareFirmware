void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int bytes_read = 0;
  byte rec[8];
  while (bytes_read < 8)
  {
    if (Serial.available() > 0)
    {
      if (Serial.peek() != 13)  // make sure to ignore CRs
      {
        rec[bytes_read] = Serial.read();
        bytes_read++;
      }
      else
        Serial.read();  // Remove CR from buffer
    }    
  }

  Serial.println("I have received: ");
  Serial.write(rec, 8);
  
}
