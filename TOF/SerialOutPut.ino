#define baud 115200

//Normal print methodes

void print(String s)
{
  if(s.length()<=0)
  {
    return;
  }
  else
  {
    Serial.begin(baud);
    //Wait for Serialport to open
    while (!Serial)
    {
      delay(1);
    }
    Serial.print(s);
    delay(2);
    Serial.end();    
  }
}

void print(int i)
{
    Serial.begin(baud);
    //Wait for Serialport to open
    while (!Serial)
    {
      delay(1);
    }
    Serial.print(i);
    delay(2);
    Serial.end();    
}

void print(float f)
{
    Serial.begin(baud);
    //Wait for Serialport to open
    while (!Serial)
    {
      delay(1);
    }
    Serial.print(f);
    delay(2);
    Serial.end();    
}

//Print methode using a new line

void println(String s)
{
  if(s.length()<=0)
  {
    return ;
  }
  else
  {
    Serial.begin(baud);
    //Waiting for Serailport to Open
    while (!Serial)
    {
      delay(1);
    }
    Serial.println(s);
    delay(2);
    Serial.end();
  }
}

void println(int i)
{
    Serial.begin(baud);
    //Waiting for Serailport to Open
    while (!Serial)
    {
      delay(1);
    }
    Serial.println(i);
    delay(2);
    Serial.end();
}

void println(float f)
{
    Serial.begin(baud);
    //Waiting for Serailport to Open
    while (!Serial)
    {
      delay(1);
    }
    Serial.println(f);
    delay(2);
    Serial.end();
}
