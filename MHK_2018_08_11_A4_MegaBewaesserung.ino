char Version[ ] = {"MHK_2018_08_11_A4_MegaBewaesserung"};

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);
int letzte=16;

int Relais[] = {22,26,23,27,24,28,25,29,30,34,31,35,32,36,33,37};
char* Pflanze[ ] = {"Birke       ","Kastanie    ","Geranie     ","Chilli      ","kl. Birke   ","Schnittlauch","Thaibasil   ","Minze       ","Birke       ","Kastanie    ","Geranie     ","Chilli      ","kl. Birke   ","Kastanie    ","Geranie     ","Chilli      ","keine"};
int Max[] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
int Sensor[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int SensorProzent[16];

void setup() {
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(Version);
  Serial.begin(9600);         // Serial Monitor initialisieren 
  Serial.println("= = = = = = = = = = = = = = = = = = = = =");
  Serial.println(Version);
  Serial.println("= = = = = = = = = = = = = = = = = = = = =");
  for (int i=0; i<16; i++) pinMode(Relais[i],OUTPUT); 
  for (int i=0; i<16; i++) digitalWrite(Relais[i],HIGH); // alle Relais ausschalten
 // for (int i=0; i<16; i++) pinMode(Sensor[i],INPUT);   
 delay(1000);
}

void loop() {
  for (int z=0; z<2; z++) { 
   for (int i=0; i<16; i++) {
    SensorProzent[i] = 100- analogRead(Sensor[i])/10,3;            //  Sensor Wert auslesen und in % Umrechnung
    if (SensorProzent[i] < Max[i]) {
      digitalWrite(Relais[i],LOW);
      letzte = i;
      }
     if (i<10) Serial.print("0");
     Serial.print(i); Serial.print(". - ");
     if (Relais[i]<10) Serial.print("0");
    Serial.print(Relais[i]); Serial.print(" - A");
     if (Sensor[i]<10) Serial.print("0");
    Serial.print(Sensor[i]); Serial.print(" - ");
    Serial.print(Pflanze[i]); Serial.print(" - ");
    Serial.print(SensorProzent[i]); Serial.print("% - ");
    Serial.print(Max[i]);
    if (SensorProzent[i] < Max[i]) {Serial.print(" *");}
    Serial.println(" ");

    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("D");
     if (Relais[i]<10) lcd.print("0");
    lcd.print(Relais[i]); lcd.print(" A");
     if (Sensor[i]<10) lcd.print("0");
    lcd.print(Sensor[i]); lcd.print(" ");
    lcd.print(SensorProzent[i]); lcd.print("%/");
    lcd.print(Max[i]); lcd.print("%");
    if (SensorProzent[i] < Max[i]) {lcd.print(" *");}
    
    lcd.setCursor(0,1);
     if (i<9) lcd.print("0");
    lcd.print(i+1); lcd.print(". ");
    lcd.print(Pflanze[i]); lcd.print(" ");
    lcd.setCursor(0,3);
    lcd.print("letzte: "); lcd.print(Pflanze[letzte]);
    
    
    delay(5000);
    digitalWrite(Relais[i],HIGH);
    }
   Serial.println("= = = = = = = = = = = = = = = = = = = = =");
   delay(5000);
  } 
  Serial.println("= = = Pause fur 10 Minuten          = = =");
  Serial.println("= = = = = = = = = = = = = = = = = = = = =");
  delay(600000); 
}
