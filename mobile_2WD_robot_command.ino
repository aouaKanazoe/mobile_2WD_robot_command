// Assignation des broches moteurs
int in1 = 2;
int in2 = 4;
int enA = 3;
int in3 = 5;
int in4 = 7; 
int enB = 6;

// Broches capteur ultrason
const int trigPin = 9;
const int echoPin = 10;

// Seuil de déclenchement en cm

const int DIST_SEUIL = 35;

// Fonctions utilitaires
void avancer(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
}

void reculer(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
}
void tournerDroite(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopRobot() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
}

// Mesure de distance avec HC-SRO4
long lireDistanceUltrason() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duree = pulseIn(echoPin, HIGH);
  return duree * 0.0343 / 2; // Conversion temps→distance en cm :contentReference[oaicite:1]{index=1}
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT); 
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // activation du moniteur série
}

void loop() {
  long dist = lireDistanceUltrason();// recupérer la distance en appelant la fonct lireDistanceUltrason
  Serial.print("Distance: "); 
  Serial.print(dist); 
  Serial.println(" cm");

   if (dist > 0 && dist < DIST_SEUIL) {
    stopRobot();
    unsigned long t0 = millis();
    while (millis() - t0 < 200) {
      // attente de 200 ms, sans bloquer
      dist = lireDistanceUltrason();
      if (dist == 0) break;
    }

    reculer(200);
    t0 = millis();
    while (millis() - t0 < 300) {
      dist = lireDistanceUltrason();
    }

    tournerDroite(200);
    t0 = millis();
    while (millis() - t0 < 400) {
      dist = lireDistanceUltrason();
    }

    stopRobot();
  }
  else {
    avancer(200);
  }
}
