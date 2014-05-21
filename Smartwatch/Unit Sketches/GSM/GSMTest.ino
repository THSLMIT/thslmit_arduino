void setup() {
	initPin();
	powerON();
	gsm_mode();

	delay(2000);
  	Serial.begin(9600);
  	delay(5000);

  	Serial.println("INIT COMMANDS");
  	delay(1000);

  	send_msg();
}

void loop() {
}

void initPin() {
	pinMode(3,OUTPUT);//The default digital driver pins for the GSM and GPS mode
  	pinMode(4,OUTPUT);
  	pinMode(5,OUTPUT);
}

void powerON() {
	digitalWrite(5,HIGH);//Output GSM Timing 
  	delay(1500);
  	digitalWrite(5,LOW); 
}

void gsm_mode() {
	digitalWrite(3,LOW);  //Enable the GSM mode
  	digitalWrite(4,HIGH); //Disable the GPS mode
}

void send_msg() {
	Serial.println("SEND TXT MESSAGE!");

		Serial.println("AT"); //Send AT command  
		delay(2000);
		
		Serial.println("AT");   
		delay(2000);
		
		//Send message
		Serial.println("AT+CMGF=1");
		delay(1000);
		
		Serial.println("AT+CMGS=\"12013678531\"");//Change the receiver phone number
		delay(1000);
		
		Serial.print("HELLO WORLD!");//the message you want to send
		delay(1000);
		
		Serial.write(26);
		while(1);
}