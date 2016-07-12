#define l1 7
#define l2 8
#define o1 A0
#define o2 A1

void setup() {
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(o1,INPUT);
  pinMode(o2,INPUT);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  delay(50);
  int L1 = analogRead(o1);
  int L2 = analogRead(o2);
  Serial.println("Vrijednost na otp pri upaljenom svijetlu(l1):");
  Serial.println(L1);
  Serial.println("Vrijednost na otp pri upaljenom svijetlu(l2):");
  Serial.println(L2);
  delay(5000);
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  delay(50);
  L1 = analogRead(o1);
  L2 = analogRead(o2);
  Serial.println("Vrijednost na otp pri ugasenom svijetlu(l1):");
  Serial.println(L1);
  Serial.println("Vrijednost na otp pri ugasenom svijetlu(l2):");
  Serial.println(L2);
  delay(5000);
}
