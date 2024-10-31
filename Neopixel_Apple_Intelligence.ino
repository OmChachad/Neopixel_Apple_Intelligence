#include <Adafruit_NeoPixel.h>

#define LED_PIN    6      // Pin connected to the data line of the LED strip
#define NUM_LEDS   90     // Number of LEDs in the strip
#define BRIGHTNESS 100     // Set brightness (0 - 255)
#define SPEED      1      // Speed of the gradient flow

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Define the colors to use in the gradient
uint32_t colors[] = {
  strip.Color(54, 128, 255),    // Blue
  strip.Color(255, 101, 0),    // Yellow
  strip.Color(255, 30, 80),     // Red
};


const int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  static uint16_t offset = 0;
  offset++;

  // Iterate over each LED to set its color
  for (int i = 0; i < NUM_LEDS; i++) {
    // Calculate which color segment this LED is in
    float position = (float(i) / NUM_LEDS + offset * 0.01) * numColors; 
    int colorIndex1 = int(position) % numColors;
    int colorIndex2 = (colorIndex1 + 1) % numColors;
    float blendFactor = position - int(position);

    // Blend between the two colors
    uint32_t color = blendColors(colors[colorIndex1], colors[colorIndex2], blendFactor);
    strip.setPixelColor(i, color);
  }

  strip.show();
  delay(20);  // Small delay to control the speed of the motion
}

// Function to blend between two colors
uint32_t blendColors(uint32_t color1, uint32_t color2, float blend) {
  uint8_t r1 = (color1 >> 16) & 0xFF;
  uint8_t g1 = (color1 >> 8) & 0xFF;
  uint8_t b1 = color1 & 0xFF;
  
  uint8_t r2 = (color2 >> 16) & 0xFF;
  uint8_t g2 = (color2 >> 8) & 0xFF;
  uint8_t b2 = color2 & 0xFF;

  uint8_t r = r1 + (r2 - r1) * blend;
  uint8_t g = g1 + (g2 - g1) * blend;
  uint8_t b = b1 + (b2 - b1) * blend;

  return strip.Color(r, g, b);
}
