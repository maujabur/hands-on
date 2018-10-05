const int minimo = 400;
const int maximo = 800;
const int entrada = A0;
const int led = 11;
const int aceso = 20;
const int tempo = 3000;

int leitura;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  leitura = analogRead(entrada);

  //// force valores para teste aqui
  //leitura = minimo+1;

  
  Serial.print(leitura);
  Serial.print(",");
  Serial.print(minimo);
  Serial.print(",");
  Serial.println(maximo);
  if (leitura < minimo) {
    analogWrite(led, aceso);
  }
  else if (leitura < maximo) {
//    analogWrite(led,0);
    int pisca = (millis() % tempo) ;
    if (pisca > tempo/2) {
      pisca = tempo-pisca;
    }
    pisca = map(pisca, 0, tempo/2, 0,aceso);
    analogWrite(led, pisca);

  }
  else {
    int pisca = (millis() / 500) % 2;
    analogWrite(led, pisca*aceso);
  }
  delay(20);
}
