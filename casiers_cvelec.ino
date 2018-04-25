#include <EEPROM.h>


#define bouton0 37
#define bouton1 35
#define bouton2 43
#define bouton3 51
#define bouton4 33
#define bouton5 41
#define bouton6 49
#define bouton7 31
#define bouton8 39
#define bouton9 47
#define boutonvalid 45
#define boutonannul 29

#define LED 53

#define servo_casier1 20
#define servo_casier2 20
#define servo_casier3 20
#define servo_casier4 20
#define servo_casier5 20
#define servo_casier6 20

int etat ;
unsigned int code ;
int num_casier ;
int valeur_bouton ;
unsigned int code_saisit;



void setup() {
  // put your setup code here, to run once:
  pinMode(bouton0, INPUT_PULLUP) ;
  pinMode(bouton1, INPUT_PULLUP) ;
  pinMode(bouton2, INPUT_PULLUP) ;
  pinMode(bouton3, INPUT_PULLUP) ;
  pinMode(bouton4, INPUT_PULLUP) ;
  pinMode(bouton5, INPUT_PULLUP) ;
  pinMode(bouton6, INPUT_PULLUP) ;
  pinMode(bouton7, INPUT_PULLUP) ;
  pinMode(bouton8, INPUT_PULLUP) ;
  pinMode(bouton9, INPUT_PULLUP) ;
  pinMode(boutonvalid, INPUT_PULLUP) ;
  pinMode(boutonannul, INPUT_PULLUP) ;

  pinMode(LED, OUTPUT) ;
  pinMode(7, OUTPUT) ;
  digitalWrite(7, LOW) ;
  Serial.begin(9600) ;

  etat = 1 ;



}

void loop() {
  switch (etat) {
    case 1:
      num_casier = -1 ;
      while (num_casier < 0) {
        num_casier = which_button() ;
      }
      Serial.print("num_casier: ") ; Serial.println(num_casier) ;
      digitalWrite(LED, HIGH) ;
      code = get_code() ;
      if (valeur_bouton == -3){
        digitalWrite(LED, LOW) ;
        break;
      }
         
      Serial.print("Code saisit: ") ; Serial.println(code, HEX) ;
      if (check_code(code, num_casier)) {
        digitalWrite(LED, LOW) ;
        Serial.println("Code bon!") ;
      }
      else if (check_code(code, 10)) {
        Serial.println("Code C-velec!") ;
        digitalWrite(LED, LOW) ;
      }
      else  {
        Serial.println("Code mauvais!") ;
        digitalWrite(LED, LOW) ;
      }

      //digitalWrite(LED,LOW) ;
      break ;
    default:
      break ;
  }
}


// put your main code here, to run repeatedly:
//unsigned int code = get_code() ;
//Serial.print("code: ") ; Serial.println(code, HEX) ;


int which_button() {
  if  (digitalRead(bouton0) == 0) {
    while (digitalRead(bouton0) == 0) ;
    return 0 ;
  }
  else if  (digitalRead(bouton1) == 0) {
    while (digitalRead(bouton1) == 0) ;
    return 1 ;
  }
  else if  (digitalRead(bouton2) == 0) {
    while (digitalRead(bouton2) == 0) ;
    return 2 ;
  }
  else if  (digitalRead(bouton3) == 0) {
    while (digitalRead(bouton3) == 0) ;
    return 3 ;
  }
  else if  (digitalRead(bouton4) == 0) {
    while (digitalRead(bouton4) == 0) ;
    return 4 ;
  }
  else if  (digitalRead(bouton5) == 0) {
    while (digitalRead(bouton5) == 0) ;
    return 5 ;
  }
  else if  (digitalRead(bouton6) == 0) {
    while (digitalRead(bouton6) == 0) ;
    return 6;
  }
  else if  (digitalRead(bouton7) == 0) {
    while (digitalRead(bouton7) == 0) ;
    return 7 ;
  }
  else if  (digitalRead(bouton8) == 0) {
    while (digitalRead(bouton8) == 0) ;
    return 8 ;
  }
  else if  (digitalRead(bouton9) == 0) {
    while (digitalRead(bouton9) == 0) ;
    return 9 ;
  }
  else if  (digitalRead(boutonvalid) == 0) {
    while (digitalRead(boutonvalid) == 0) ;
    return -2 ;
  }
  else if  (digitalRead(boutonannul) == 0) {
    while (digitalRead(boutonannul) == 0) ;
    return -3 ;
  }
  else
    return -1 ;
}

unsigned int get_code() {
  static unsigned int clic_counter = 0 ; // compte le nombre de clic sur les boutons
  code_saisit = 0 ;
  int valider = 0 ;
  while (valider != -2 ) {
    valeur_bouton = which_button() ;
    if (valeur_bouton >= 0 & clic_counter < 4) {
      Serial.print("Bouton: ") ; Serial.println(valeur_bouton) ;
      code_saisit = code_saisit ^ (valeur_bouton << (clic_counter * 4)) ; // créer le code avec les 4 chiffres
      clic_counter++ ;
    }
    if (valeur_bouton == -3) {
      //clic_counter = 0 ;
      Serial.println("annuler") ;
      break;
    }
    valider = valeur_bouton ;

  }
  clic_counter = 0 ;
  return code_saisit ;
}

void ouvrir_casier(int numero_casier) {

}

bool check_code(unsigned int code, unsigned int num_casier) {
  unsigned int saved_code ;
  EEPROM.get(num_casier * sizeof(int) - sizeof(int), saved_code);
  Serial.print("code casier: ") ; Serial.println(saved_code, HEX) ;
  if (code == saved_code)
    return true ;
  else
    return false ;
}

