void setPinsLow();

String inString = "";
int dir, cmd, data;

void setup()
{
  Serial.begin(9600);

  while (!Serial);  // Wait for connection
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  int rec;
  int CR = '\r';  // Carriage return
  int NL = '\n';  // New Line

  // This loop reads individual bytes into a buffer to be extracted.
  if (Serial.available() > 0)
  {
    int inChar = Serial.read();

    if (isDigit(inChar))
    {
      inString += (char)inChar;   //Forming the string
    }

    if ((inChar == CR) || (inChar == NL)) // Wait until either a new line or a carriage return indicating the end of the data.
    {
      if (inString != "")   // Only attempt to parse when data has been read.
      {
        rec = inString.toInt();
        parseData(rec);
        
        Serial.println(constructMessage(cmd, data));  // Print what the Arduino received to check if they are identical.

        checkData();

        digitalWrite(13, HIGH); // Flashes to show a message was received.

        inString = "";  // Reset the string to accept more data.
      }
    }
  }
}

void checkData()
{
  if ((cmd >= 0) && (cmd <= 15) && (data >= 0) && (data <= 7))  // Makes sure the commands and data received are within specifed bounds.
    carryOutCommand();
}

int constructMessage(int command, int data)
{
  return command | (data << 4) | (0 << 7);
}

void carryOutCommand()
{
  setPinsHigh();

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
  Serial.print("Command: ");
  Serial.println(cmd);
  Serial.print("Data: ");
  Serial.println(data);
  Serial.print("Direction: ");
  Serial.println(dir);
}

void parseData(int rec)
{
  if (rec <= 255)
  {
    cmd = bitRead(rec, 0) | bitRead(rec, 1) << 1 | bitRead(rec, 2) << 2 | bitRead(rec, 3) << 3;
    data = bitRead(rec, 4) | bitRead(rec, 5) << 1 | bitRead(rec, 6) << 2;
    dir = bitRead(rec, 7);
  }
}

void forward()
{
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
}

void reverse()
{
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
}

void brake()
{
  setPinsHigh();
}

void left()
{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void right()
{
  digitalWrite(2, LOW);
  digitalWrite(5, LOW);
}

void setspeed(int _speed)
{
  //digitalWrite(7, HIGH);
  // flash at speed?
}

void ping(int data)
{
  //digitalWrite(8, HIGH);
}

void error()
{

}

void setPinsLow()
{
  for (int i = 2; i <= 5; i++)
  {
    digitalWrite(i, LOW);   // Reset all pins low.
  }
}

void setPinsHigh()
{
  for (int i = 2; i <= 5; i++)
  {
    digitalWrite(i, HIGH);   // Reset all pins low.
  }
}
