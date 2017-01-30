
#include <ESP8266WiFi.h>


// WiFi parameters
const char* ssid = "Your SSID";
const char* password = "Your Password";


// Create an instance of the server
WiFiServer server(LISTEN_PORT);

//

int ledControl(String command);

void wifi(){

  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  }

void setup(void) {
  // Start Serial
  Serial.begin(115200);

  // Set the title
  title("Light Automation for DL-5");

  // Create button to control pin 5
  button(0);
  button(2);


  
// Give name and ID to device
  set_id("1");
  set_name("esp8266");

  
  // Function to be exposed
  function("led", ledControl);
  
  
  wifi();

}



void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  handle(client);

}

int ledControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(1, state);
  return 1;
}
