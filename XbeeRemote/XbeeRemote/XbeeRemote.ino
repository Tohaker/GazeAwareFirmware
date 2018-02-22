void setPinsLow();

String inString = "";
int dir, cmd, data;

void setup() 
{
  Serial.begin(9600);

  while (!Serial);  // Wait for connection
}

void loop() 
{
  int rec;
  int CR = '\r';
  // This loop reads individual bytes into a buffer to be extracted.
  
  if (Serial.available() > 0)
  {
    int inChar = Serial.read();
    
    if (isDigit(inChar))
    {
      inString += (char)inChar;
    }
    
    if (inChar == CR)
    {
      if (inString != "")
      {
        rec = inString.toInt();
        //printReturn(rec);
        Serial.println(rec);
        splitByte(rec);
        carryOutCommand();
        inString = "";
      }
    }
  }    
}

void carryOutCommand()
{
  setPinsLow();

  if (dir == 1)
  {
    switch (cmd)
    {
      case 0:
        forward();
        break;
      case 1:
        reverse();
        break;
      case 2:
        brake();
        break;
      case 3:
        left();
        break;
      case 4:
        right();
        break;
      case 5:
        setspeed(data);
        break;
      case 6:
        ping(data);
        break;
      default:
        error();
        break;
    }
  }
}

void printReturn(int rec)
{
  Serial.println("I have received: " + rec);
  
  
  
//  Serial.print("Command: ");
//  Serial.println(cmd);
//  Serial.print("Data: ");
//  Serial.println(data);
//  Serial.print("Direction: ");
//  Serial.println(dir);
}

void splitByte(int rec)
{
  cmd = bitRead(rec, 0) | bitRead(rec, 1) << 1 | bitRead(rec, 2) << 2 | bitRead(rec, 3) << 3;
  data = bitRead(rec, 4) | bitRead(rec, 5) << 1 | bitRead(rec, 6) << 2;
  dir = bitRead(rec, 7);
}

void forward()
{
  digitalWrite(2, HIGH);
}

void reverse()
{
  digitalWrite(3, HIGH);
}

void brake()
{
  digitalWrite(4, HIGH);
}

void left()
{
  digitalWrite(5, HIGH);
}

void right()
{
  digitalWrite(6, HIGH);
}

void setspeed(int _speed)
{
  digitalWrite(7, HIGH);
  // flash at speed?
}

void ping(int data)
{
  digitalWrite(8, HIGH);
}

void error()
{
  
}

void setPinsLow()
{
  for (int i = 2; i < 9; i++)
  {
    digitalWrite(i, LOW);   // Reset all pins low.
  }
}
