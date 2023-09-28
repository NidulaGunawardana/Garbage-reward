#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#define HOST "dkgproject.000webhostapp.com" // Enter HOST URL without "http:// "  and "/" at the end of URL

JSONVar myObject = "undefined";

void setup()
{

    Serial.begin(115200);
    Serial.println("Communication Started \n\n");
    delay(1000);

    pinMode(LED_BUILTIN, OUTPUT); // initialize built in led on the board

    WiFiManager wifiManager;
    wifiManager.autoConnect("Garbage Reward");

    Serial.println("connected :)");

    delay(30);
}

void loop()
{

    ///////////////////////////////////// Uploading data to database //////////////////////////////////////////////
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFiManager wifiManager;

        wifiManager.autoConnect("Garbage Reward");

        Serial.println("connected :)");
        wifiManager.setBreakAfterConfig(true);
    }
    HTTPClient http; // http object of clas HTTPClient
    // Convert integer variables to string
    WiFiClient client;

    String mobile = "0778482017"; // Enter mobile number here
    float reward = 150.50;           // enter reward here

    String postData = "mobile=" + (String)mobile + "&reward=" + (String)reward;
    http.begin(client, "http://dkgproject.000webhostapp.com/errorWrite.php"); // Connect to host where MySQL databse is hosted
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");            // Specify content-type header

    int httpCode = http.POST(postData); // Send POST request to php file and store server response code in variable named httpCode
    Serial.println("mobile=" + (String)mobile + "&reward=" + (String)reward);
    if (httpCode == 200)
    {
        Serial.println(httpCode);
        String webpage = http.getString(); // Get html webpage output and store it in a string                                              //Serial.println(webpage + "\n");
    }

    // if failed to connect then return and restart

    else
    {
        Serial.println(httpCode);
        Serial.println("Failed to upload values. \n");
        http.end();
        return;
    }

    //////////////////////////////////////////////// END ///////////////////////////////////////////////////////////////
delay(5000);
    ////////////////////////////////////////////////// Reading From databse //////////////////////////////////////////////////////////////

    if (WiFi.status() != WL_CONNECTED)
    {
        WiFiManager wifiManager;

        wifiManager.autoConnect("Garbage Reward");

        Serial.println("connected :)");
        wifiManager.setBreakAfterConfig(true);
    }

    HTTPClient http; // http object of clas HTTPClient
    String mobile = "0778482017";
    String postData = "mobile=" + (String)mobile;
    WiFiClient client;

    http.begin(client, "http://dkgproject.000webhostapp.com//dbreadphp.php"); // Connect to host where MySQL databse is hosted
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");           // Specify content-type header

    int httpCode = http.POST(postData); // Send POST request to php file and store server response code in variable named httpCode
    Serial.println("Values are, mobile=" + (String)mobile);

    // if connection eatablished then do this

    if (httpCode == 200)
    {
        Serial.println(httpCode);
        String webpage = http.getString(); // Get html webpage output and store it in a string
        myObject = JSON.parse(webpage);

        if (JSON.typeof(myObject) != "undefined")
        {
            Serial.println("sol 1 = " + (String)myObject["reward"]);
        }
    }

    // if failed to connect then return and restart

    else
    {
        Serial.println(httpCode);
        Serial.println("Failed to upload values. \n");
        http.end();
        return;
    }
delay(5000);
    //////////////////////////////////////////// END ////////////////////////////////////////////////////
}