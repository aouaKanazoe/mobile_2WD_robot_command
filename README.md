# Robot Mobile 2WD DIY avec Arduino, L298N & Capteur Ultrason

## 📋 Présentation
Ce projet consiste en un robot mobile 2 roues motorisées contrôlé par une carte Arduino UNO via un pont en H L298N. Il évite les obstacles grâce à un capteur à ultrasons HC-SR04.

## 💾 Code Arduino

Le code inclus :  
- Lecture de la distance via le HC-SR04  
- Avance en permanence  
- Lorsqu'un obstacle est détecté à moins de 35 cm :
  - Arrêt, recul, puis virage à droite  
  - Reprise de l’avancée  
- Mesures affichées sur le moniteur série (via USB ou Bluetooth)
