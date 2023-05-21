#include <WiFi.h>
#include <SD.h>
#include<ESP32WebServer.h>
const char* ssid = "ESP32AccessPoint";          // SSID of the access point
const char* password = "12345678";     // Password for the access point

const int chipSelect = 0;  // Chip select pin for the SD card

WiFiServer server(80);
File root;

void handleDownloadPage(WiFiClient& client) {
  root = SD.open("/");
  if (!root) {
    client.println("HTTP/1.1 500 Internal Server Error");
    client.println("Content-type: text/plain");
    client.println();
    client.println("Failed to open SD card root directory");
    client.println();
    root.close();
    return;
  }

  String fileList = "<ul>";

  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      break;
    }
    if (!entry.isDirectory()) {
      fileList += "<li><a href='/download/" + String(entry.name()) + "'>" + String(entry.name()) + "</a></li>";
    }
    entry.close();
  }
  root.close();

  fileList += "</ul>";

  String html = "<html><body><h1>Download Files</h1>" + fileList + "</body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println();
  client.println(html);
}

void handleCustomPage(WiFiClient& client) {
  String html = "<html><body><h1>Custom Page</h1><p>This is a custom HTML page.</p></body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println();
  client.println(html);
}

void setup() {
  Serial.begin(115200);

  // Mount SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Failed to initialize SD card.");
    return;
  }

  // Set up access point
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    // Wait for the client to send a request
    while (!client.available()) {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    client.readStringUntil('\n');

    // Process the request
    if (request.startsWith("GET /download")) {
      handleDownloadPage(client);
    }
    else if (request.startsWith("GET /custom")) {
      handleCustomPage(client);
    }
    else {
      // Invalid request
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-type: text/plain");
      client.println();
      client.println("File not found");
    }

    // Wait for the client to receive the response
    delay(10);
    client.stop();
  }
}
