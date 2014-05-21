void setup() {
	// Initialize Default Module GPS Pins
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);

  	Serial.begin(9600);
  	delay(5000);

	// Power Module Switch
	// TODO: Create a function to check power status.
	gps_init();
}

void loop() {
	/*
	if (Serial.available() > 0) {
		char c = (char)Serial.read();
		Serial.print(c);

		// if (c == 13) Serial.println("CHAR RETURN");
	} */

	/*
	if (ID()) {
		Serial.println("DATA");
		UTC();
	} */


	char i=0;
  	char target_protocol[6]={'$','G','P','G','G','A'};
  	char val[6]={'0','0','0','0','0','0'};
 
  	while(1) {
    	if(Serial.available()) {
      		val[i] = Serial.read();
      		if(val[i]==value[i]) {    
        		i++;
        		if(i==6) {
          			i=0;
          			break;
        		}
      		} else i=0;
    	}
  	}
}

void power_switch() {
	digitalWrite(5, HIGH);
	delay(1500);
	digitalWrite(5, LOW);
	delay(1000);
}

void gps_init() {
	power_switch();

	// GSM Mode Enable
  	digitalWrite(3,LOW);
  	digitalWrite(4,HIGH);

  	delay(5000);

  	Serial.println("AT");
 	delay(2000);

 	Serial.println("AT+CGPSPWR=1");
  	delay(2000);

	Serial.println("AT+CGPSRST=1");
  	delay(2000);

   	digitalWrite(4,LOW);//Enable GPS mode
  	digitalWrite(3,HIGH);//Disable GSM mode
  	delay(2000);
}

double Datatransfer(char *data_buf,char num)//convert the data to the float type
{                                           //*data_buf：the data array                                       
  double temp=0.0;                           //the number of the right of a decimal point
  unsigned char i,j;
 
  if(data_buf[0]=='-')
  {
    i=1;
    //process the data array
    while(data_buf[i]!='.')
      temp=temp*10+(data_buf[i++]-0x30);
    for(j=0;j<num;j++)
      temp=temp*10+(data_buf[++i]-0x30);
    //convert the int type to the float type
    for(j=0;j<num;j++)
      temp=temp/10;
    //convert to the negative numbe
    temp=0-temp;
  }
  else//for the positive number
  {
    i=0;
    while(data_buf[i]!='.')
      temp=temp*10+(data_buf[i++]-0x30);
    for(j=0;j<num;j++)
      temp=temp*10+(data_buf[++i]-0x30);
    for(j=0;j<num;j++)
      temp=temp/10 ;
  }
  return temp;
}
 
char ID()//Match the ID commands
{ 
  char i=0;
  char value[6]={
    '$','G','P','G','G','A'    };//match the gps protocol
  char val[6]={
    '0','0','0','0','0','0'    };
 
  while(1)
  {
    if(Serial.available())
    {
      val[i] = Serial.read();//get the data from the serial interface
      if(val[i]==value[i]) //Match the protocol
      {    
        i++;
        if(i==6)
        {
          i=0;
          return 1;//break out after get the command
        }
      }
      else
        i=0;
    }
  } 
}
 
void comma(char num)//get ','
{   
  char val;
  char count=0;//count the number of ','
 
  while(1)
  {
    if(Serial.available())
    {
      val = Serial.read();
      if(val==',')
        count++;
    }
    if(count==num)//if the command is right, run return
      return;
  }
 
}
void UTC()//get the UTC data -- the time
{
  char i;
  char time[9]={
    '0','0','0','0','0','0','0','0','0'
  };
  double t=0.0;
 
  if( ID())//check ID
  {
    comma(1);//remove 1 ','
    //get the datas after headers
    while(1)
    {
      if(Serial.available())
      {
        time[i] = Serial.read();
        i++;
      }
      if(i==9)
      {
        i=0;
        t=Datatransfer(time,2);//convert data
        t=t+80000.00;//convert to the chinese time GMT+8 Time zone
        Serial.println(t);//Print data 
        return;
      }  
    }
  }
}
void latitude()//get latitude
{
  char i;
  char lat[10]={
    '0','0','0','0','0','0','0','0','0','0'
  };
 
 
  if( ID())
  {
    comma(2);
    while(1)
    {
      if(Serial.available())
      {
        lat[i] = Serial.read();
        i++;
      }
      if(i==10)
      {
        i=0;
        Serial.println(Datatransfer(lat,5),5);//print latitude 
        return;
      }  
    }
  }
}
void lat_dir()//get dimensions
{
  char i=0,val;
 
  if( ID())
  {
    comma(3);
    while(1)
    {
      if(Serial.available())
      {
        val = Serial.read();
        Serial.write(val);
        Serial.println();
        i++;
      }
      if(i==1)
      {
        i=0;
        return;
      }  
    }
  }
}
void longitude()//get longitude
{
  char i;
  char lon[11]={
    '0','0','0','0','0','0','0','0','0','0','0'
  };
 
  if( ID())
  {
    comma(4);
    while(1)
    {
      if(Serial.available())
      {
        lon[i] = Serial.read();
        i++;
      }
      if(i==11)
      {
        i=0;
        Serial.println(Datatransfer(lon,5),5);
        return;
      }  
    }
  }
}
void lon_dir()//get direction data
{
  char i=0,val;
 
  if( ID())
  {
    comma(5);
    while(1)
    {
      if(Serial.available())
      {
        val = Serial.read();
        Serial.write(val); //Serial.println(val,BYTE);
        Serial.println();
        i++;
      }
      if(i==1)
      {
        i=0;
        return;
      }  
    }
  }
}
void altitude()//get altitude data
{
  char i,flag=0;
  char alt[8]={
    '0','0','0','0','0','0','0','0'
  };
 
  if( ID())
  {
    comma(9);
    while(1)
    {
      if(Serial.available())
      {
        alt[i] = Serial.read();
        if(alt[i]==',')
          flag=1;
        else
          i++;
      }
      if(flag)
      {
        i=0;
        Serial.println(Datatransfer(alt,1),1);//print altitude data
        return;
      }  
    }
  }
}