#define RED 5
#define BLUE 6
#define GREEN 3

#define RED2 9
#define BLUE2 10
#define GREEN2 11

#define d 5

// Grupos de leds
int abajo[] = {RED, GREEN, BLUE};
int arriba[] = {RED2, GREEN2, BLUE2};

// Colores
int rojo[]={255,0,0};
int azulElectrico[]={60,236,255};

void setup() {
  pinMode(RED, 0);
  pinMode(GREEN, 0);
  pinMode(BLUE, 0);
  pinMode(RED2, 0);
  pinMode(GREEN2, 0);
  pinMode(BLUE2, 0);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

int rVal = 254;
int gVal = 1;
int bVal = 127;

int rDir = -1, rDir2 = -1;
int gDir = 1, gDir2 = 1;
int bDir = -1, bDir2 = -1;


void fadeEffect(int grupo[]) {

  int r = grupo[0];
  int g = grupo[1];
  int b = grupo[2];
   
  analogWrite(r, rVal);
  analogWrite(g, gVal);
  analogWrite(b, bVal);

  if(r == RED) {
    rVal = rVal + rDir;
    gVal = gVal + gDir;
    bVal = bVal + bDir; 
  } else {
    rVal = rVal + rDir2;
    gVal = gVal + gDir2;
    bVal = bVal + bDir2;
  }

  if (rVal >= 255 || rVal <= 0) {
    if(r == RED) {
      rDir = rDir * -1; 
    } else {
      rDir2 = rDir2 * -1;
    }
  }

  if (gVal >= 255 || gVal <= 0) {
    if(g == GREEN) {
      gDir = gDir * -1; 
    } else {
      gDir2 = gDir2 * -1;
    }
  }

  if (bVal >= 255 || bVal <= 0) {
    if(b == BLUE) {
      bDir = bDir * -1; 
    } else {
      bDir2 = bDir2 * -1;
    }
  }

  delay(1);
}

void staticEffect(int color[], int grupo[]) {
  for(int i = 0; i < 3; i++) {
    analogWrite(grupo[i], color[i]);
  }
}
int voltages[10];
int contador = 0, promedioVoltage = 1;
float lectura;
float volt;

void loop() {
  if(contador >= 10){
    for(int i = 0; i < 10; i++) {
      promedioVoltage += voltages[i];
    }
    promedioVoltage = promedioVoltage / 10;

    // Acá es dónde se produce el cambio de las luces por el switch
    if(promedioVoltage > 2) {
      staticEffect(rojo, arriba);
      staticEffect(azulElectrico, abajo);
    } else if(promedioVoltage < 1) {
      fadeEffect(arriba);
      fadeEffect(abajo);
    }
    contador = 0;
    promedioVoltage = 0;
  }
  
  lectura = analogRead(A0);
  volt = lectura /1023 * 5.0;
  voltages[contador] = volt;
  
  contador++;
}
