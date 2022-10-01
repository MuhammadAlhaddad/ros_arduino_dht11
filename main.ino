// DHT Temperature Reading
// Written by Muhammad Alhaddad

#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Float32.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2  
#define DHTTYPE    DHT11   
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

std_msgs::Float32 sensor_msg;
ros::Publisher pub_sensor("sensor", &sensor_msg);
ros::NodeHandle nh;
void setup() {
  nh.initNode();
  nh.advertise(pub_sensor);
  // Initialize device.
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}
long publisher_timer;
void loop() {
  if (millis() > publisher_timer) {
  // Delay between measurements.
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
  }
  else {
    sensor_msg.data = event.temperature;
  pub_sensor.publish(&sensor_msg);
  }
  publisher_timer = millis() + 4000; 
  }
  nh.spinOnce();

}
