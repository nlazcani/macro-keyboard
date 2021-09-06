#include <Arduino.h>

// Include for the LED's
#include <Adafruit_NeoPixel.h>

#define PIN A2
#define NUMPIXELS 13

#define GENERAL 150, 150, 150
#define PURPLE 150, 0, 150
#define GOLD 168, 67, 0
#define ORANGE 168, 47, 0
#define BLUE 0, 92, 168
#define GREEN 0, 168, 0
#define RED 168, 0, 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int colorUpdate = 0; // Flag for updating colors

// Include the necessary keyboard stuff
#include <Keyboard.h>
#include <Keypad.h>

// Simplifying key names
#define CTRL KEY_LEFT_CTRL
#define ALT KEY_LEFT_ALT
#define SHIFT KEY_LEFT_SHIFT
#define WIN KEY_LEFT_GUI

// Include stuff for display
#include <U8g2lib.h>

// Setup OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

// Scroll Text setup
int x, x2, minX;

// Mode Button Variables
int modePushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

// Keyboard Mapping and initialization
const int ModeButton = 16;

const byte ROWS = 3;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'0', '1', '2', '3'},
    {'4', '5', '6', '7'},
    {'8', '9', 'A', 'B'},
};

byte rowPins[ROWS] = {4, 5, A3};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Function Declarations
void checkModeButton();
void writeToDisplay(char *toWrite, int size);
void setPixelMode();
void setAllPixels(int r, int g, int b);
void setPixelColor(int pixel, int r, int g, int b);
void updateDisplay(char const *mode[], int mode_id, int selected);

void setup()
{
  u8g2.begin();
  pinMode(ModeButton, INPUT_PULLUP);
  Keyboard.begin();

  // Turn off the TX LED.
  pinMode(LED_BUILTIN_TX, INPUT);
  pixels.begin();
}
char const *modes[3] = {"VScode", "Discord", "Windows"};

char const *modes0[12] = {"New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal"};
char const *modes1[12] = {"New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal"};
char const *modes2[12] = {"New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal", "New Terminal"};

void loop()
{
  char key = keypad.getKey();
  int number = (key < '9') ? key - '0' : key - '7';
  checkModeButton();
  setPixelMode();
  updateDisplay(modes0,modePushCounter, number);
  switch (modePushCounter)
  {
  case 0:
    if (key != NO_KEY)
    {
      switch (number)
      {
      case 0:
        // Discord Mute Microphone
        Keyboard.press(CTRL);
        Keyboard.press(ALT);
        Keyboard.print('1');
        break;
      case 1:
        // Discord Mute Microphone
        Keyboard.press(CTRL);
        Keyboard.press(ALT);
        Keyboard.print('1');
        break;
      case 2:
        // Discord Deafen
        Keyboard.press(CTRL);
        Keyboard.press(ALT);
        Keyboard.print('2');
        break;
      case 3:
        // Discord Screen Share
        Keyboard.press(CTRL);
        Keyboard.press(ALT);
        Keyboard.print('3');
        break;
      case 4:
        // Open/Switch to Discord
        Keyboard.press(WIN);
        Keyboard.print('3');
        break;
      case 5:
        // Open Spotify
        Keyboard.press(WIN);
        Keyboard.print('5');
        break;
      case 6:
        // Open VSCode
        Keyboard.press(WIN);
        Keyboard.print('6');
        modePushCounter = 2;
        colorUpdate = 0;
        break;
      case 7:
        //
        break;
      case 8:
        //
        break;
      case 9:
        //
        break;
      case 10:
        //
        break;
      case 11:
        // Focus/Unfocus Desktop
        Keyboard.press(WIN);
        Keyboard.print('d');
        break;
      }
    }
    Keyboard.releaseAll();
    break;
  case 1:
    if (key != NO_KEY)
    {
      switch (number)
      {
      case 0:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('0');
        break;
      case 1:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('1');
        break;
      case 2:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('2');
        break;
      case 3:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('3');
        break;
      case 4:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('4');
        break;
      case 5:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('5');
        break;
      case 6:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('6');
        break;
      case 7:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('7');
        break;
      case 8:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('8');
        break;
      case 9:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('8');
        break;
      case 10:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('-');
        break;
      case 11:
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('=');
        break;
      }
    }
    colorUpdate = 0;
    Keyboard.releaseAll();
    break;
  case 2:
    if (key != NO_KEY)
    {
      switch (number)
      {
      case 0:
        // Go to ending of line
        Keyboard.press(KEY_END);
        break;
      case 1:
        // Open Command Panel
        Keyboard.press(CTRL);
        Keyboard.press(SHIFT);
        Keyboard.print('p');
        break;
      case 2:
        // Open Terminal
        Keyboard.press(CTRL);
        Keyboard.print('`');
        break;
      case 3:
        // Toggle Comment line
        Keyboard.press(CTRL);
        Keyboard.print('/');
        break;
      case 4:
        // Toggle Comment Block
        Keyboard.press(SHIFT);
        Keyboard.press(ALT);
        Keyboard.print('a');
        break;
      case 5:
        // Split editor Vertical
        Keyboard.press(CTRL);
        Keyboard.print('\\');
        break;
      case 6:
        // Split editor Orthogonal
        Keyboard.press(CTRL);
        Keyboard.print('k');
        Keyboard.print('\\');
        break;
      case 7:
        // Fold all regions
        Keyboard.press(CTRL);
        Keyboard.print('k');
        Keyboard.print('0');
        break;
      case 8:
        // Unfold all regions
        Keyboard.press(CTRL);
        Keyboard.print('k');
        Keyboard.print('j');
        break;
      case 9:
        // Go to beginning of line
        Keyboard.press(KEY_HOME);
        break;
      case 10:
        // Go to beginning of file
        Keyboard.press(CTRL);
        Keyboard.press(KEY_HOME);
        break;
      case 11:
        // Go to ending of file
        Keyboard.press(CTRL);
        Keyboard.press(KEY_END);
        break;
      }
    }
    Keyboard.releaseAll();
    break;
  }
}

void checkModeButton()
{
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      modePushCounter++;
      colorUpdate = 0;
    }
  }
  lastButtonState = buttonState;
  if (modePushCounter > 2)
  {
    modePushCounter = 0;
  }
}

void setPixelMode()
{
  if (colorUpdate == 0)
  {
    switch (modePushCounter)
    {
    case 0:
      setAllPixels(GENERAL);
      pixels.show();
      break;
    case 1:
      setAllPixels(GOLD);
      pixels.show();
      break;
    case 2:
      setAllPixels(BLUE);
      pixels.show();
      break;
    }
    colorUpdate = 1;
  }
}

void setAllPixels(int r, int g, int b)
{
  for (int i = 0; i < 14; i++)
  {
    setPixelColor(i, r, g, b);
  }
}

void setPixelColor(int pixel, int r, int g, int b)
{
  pixels.setPixelColor(pixel, pixels.Color(r, g, b));
}

int y = 135;
int offset = 139;

void updateDisplay(char const *mode[], int mode_id, int selected)
{
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_t0_11_tr);
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 16, u8g2.getDisplayHeight() - 1);
    u8g2.setFontDirection(3);
    u8g2.setDrawColor(0);
    u8g2.drawStr(11, 62, modes[mode_id]);
    u8g2.setFontDirection(0);

    u8g2.setFont(u8g2_font_t0_11_tr);
    u8g2.setDrawColor(1);
    for (int i = 0; i < 12; i++)
    {
      u8g2.drawStr(19, offset - ((y + 11 * (11 - i) + 7) % offset), mode[i]);
    }

    if (selected >= 0 && selected < 12)
    {
      u8g2.setFont(u8g2_font_t0_11_tr);
      u8g2.setDrawColor(1);
      u8g2.drawBox(19, 0, 144, 12);
      u8g2.setDrawColor(0);
      u8g2.drawStr(24, 11, mode[selected]);
    }
  } while( u8g2.nextPage() );
  y = (y + 1) % offset;
}