//
//Projekat: Senzori-brojaci osoba u prostoriji 
//Sekulović Milorad
//Mentor:Jovanov Ilija
//


//Promjenjive koje ce se koristiti kao pinovi na ploci
#define Las1 7
#define Las2 8
#define Fotp1 A1
#define Fotp2 A0
#define Out 6
#define buzz 5
//Promjenjive potrebne u glavnom programu, za cuvanje vrijednosti
int L1; // ovdje se cuva ulaz sa foto otpornika 1
int L2; // ovdje se cuva ulaz sa foto otpornika 2
int prag = 850; // prag koji smo postavili na vrijednost kada laser ne baca svjetlo na foto otpornik
bool ppres1;//ovdje cemo cuvati prethodne vrijednosti toga da li je neko prekinuo laser na senzoru
bool ppres2;//-||-
bool onvi, onvu;//Osoba na vratima izlazi/Osoba na vratima ulazi
int pCount;//Brojac osoba
int ppCount;//Prethodna informacija o broju osoba u prostoriji
void setup() {
  pinMode(Fotp1, INPUT);//Definisanje izlaznog pina za laser
  pinMode(Fotp2, INPUT);//-||-
  pinMode(Las1, OUTPUT);//Definisanje ulaznog pina za foto otpornik
  pinMode(Las2, OUTPUT);//-||-
  pinMode(Out, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);//Otvaranje serijskog porta sa baud rate-om 9600 *
  while (!Serial);
}

void loop() {
  digitalWrite(Las1, HIGH);//Paljenje lasera
  digitalWrite(Las2, HIGH);//-||-
  delay(5);//pauza 1 ms, da budemo sigurni da ce otpornik ocitati pravu vrijednost
  L1 = analogRead(Fotp1);//citanje vrijednosti na otporniku
  L2 = analogRead(Fotp2);//-||-
  digitalWrite(Las1, LOW);//gasenje lasera
  digitalWrite(Las2, LOW);//-||-
  delay(20);//pauza 4ms zbog smanjenja vidljivosti snopa i ustede energije
  //boolovi nam predstavljaju da li je presjecen laserski zrak kao poredjenje ulaza sa foto otpornika i praga
  bool pres1 = (L1 > prag);
  bool pres2 = (L2 > prag);
  //podrazumijeva se da u pocetnom trenutku postavljanja nema nikog u prostoriji i poredimo proslu i
  //sadastnju vrijednost i tako znamo da je neko usao.
//  Serial.print("L1:");Serial.println(L1);
//  Serial.print("L2:");Serial.println(L2);
  //
  //ULAZ
  //
  if ((ppres1 & !pres1)&pres2) {
    onvu = true;
  }
  if ((!ppres1 & pres1) & !pres2 & onvu) {
    onvu = false;
    pCount++;
  }
  if ((!ppres1 & pres1)&pres2 & onvu) {
    onvu = false;
  }
  //
  //IZLAZ
  //
  if ((ppres1 & !pres1) & !pres2) {
    onvi = true;
  }
  if ((!ppres1 & pres1)&pres2 & onvi) {
    onvi = false;
    pCount--;
  }
  if ((ppres1 & pres1) & !pres2 & onvi) {
    onvi = false;
  }
  //pamtimo prosle vrijednosti, da bi ih u sledecem trenutku u vremenu uporedili
  ppres1 = pres1;
  ppres2 = pres2;
  if(ppCount!=pCount){
    beep();
  Serial.println(pCount);}
  ppCount=pCount;
  //Kontrola osvetljenja (trenutno u modu za led), modifikovati za relay
  if(pCount!=0){
    digitalWrite(Out,HIGH);
    //beep();
    }
    else{
      digitalWrite(Out,LOW);
      //beep();
      }
}

void beep(){
  digitalWrite(buzz,HIGH);
  delay(10);
  digitalWrite(buzz,LOW);
  }

//* baud rate wikipedia article - http://en.wikipedia.org/wiki/Baud
//Najbrzi covjek na svijetu - Usain Bolt - 44.7km/h -> 12.4m/s -> 1,24cm/ms
//Srednja brzina na maratonu - 16 km/h -> 4.47m/s ->0.447cm/ms
//Srednja brzina hodanja - 4.82km/h -> 1.34m/s -> 0.1314cm/ms
//Razdaljina izmedju 2 senzora ~1,24cm 
