#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 15, 24};

EthernetServer server(80);

void setup()
{
  Ethernet.begin(mac,ip);
  server.begin();
}

void loop()
{
  EthernetClient client = server.available();
  if(client){
    while(client.connected()){
      // Cabeçalho HTTP Padrão:
      client.println("HTTP/1.1 200 OK");
      client.println("COntent-Type: text/html");
      client.println();
  
      // Codigo da pagina html:
      double T = analogRead(0);
      
      client.println("<html>");
      client.println("<body>");
      client.println("<h1>Temperatura: ");
      client.println(500*T/1024);
      client.println(" C </h1>");
      client.println("</body>");
      client.println("</html>");
      client.stop();
    }
    delay(1);
  }
}

