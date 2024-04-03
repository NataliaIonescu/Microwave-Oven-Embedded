
// Pin definitions
#define START   6
#define CANCEL  7
#define MIN10   8
#define MIN     9
#define SEC10  10
#define RUN    13
#define k 4 

#define setbit(var,bit) var |= 1<<bit

// Time variables
volatile int minutesTens = 0;
volatile int minutes = 0;
volatile int secondsTens = 0;
volatile int seconds = 0;

bool isRunning = false;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // 1 second interval for time decrement

void setup()
{ 
  Serial.begin(9600);
  pinMode(START, INPUT);
  pinMode(CANCEL, INPUT);
  pinMode(MIN10, INPUT);
  pinMode(MIN, INPUT);
  pinMode(SEC10, INPUT);
  pinMode(RUN, OUTPUT);
  
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  lcd.setCursor(0, 0);
  lcd.print("Time: 00:00");

}


int Start_B = LOW;
int Start_B_ante = LOW;

int Cancel_B = LOW;
int Cancel_B_ante = LOW;

int MIN10_B = LOW;
int MIN10_B_ante = LOW;

int MIN_B = LOW;
int MIN_B_ante = LOW;

int SEC10_B = LOW;
int SEC10_B_ante = LOW;

void loop()
{
   unsigned long currentMillis = millis(); // Declaration and initialization of currentMillis
  
  if (!isRunning) {
    setTime();
    displayTime();
  } else {
    if (currentMillis - lastUpdateTime >= updateInterval) {
      decrementTime();
      displayTime();
      lastUpdateTime = currentMillis;
    }
  }
  
  Start_B_ante = Start_B;
  Start_B=digitalRead(START);
  if (Start_B == HIGH && Start_B_ante == LOW && !isRunning) {
    isRunning = true;
    digitalWrite(RUN, HIGH);
  }

  Cancel_B_ante = Cancel_B;
  Cancel_B = digitalRead(CANCEL);
  if (Cancel_B == HIGH &&  Cancel_B_ante == LOW) {
    isRunning = false;
    digitalWrite(RUN, LOW);
    resetTime();
  }

}

void setTime() {
  
  MIN10_B_ante = MIN10_B; 
  MIN10_B = digitalRead(MIN10);
  if (MIN10_B == HIGH && MIN10_B_ante ==LOW) {
    minutesTens = (minutesTens + 1) % 10;
  }

  MIN_B_ante=MIN_B;
  MIN_B = digitalRead(MIN);
  if (MIN_B == HIGH && MIN_B_ante == LOW) {
    minutes = (minutes + 1) % 10;
    if (minutes == 0 && minutesTens == 9) {
      minutesTens = 0;
    }
  }

  SEC10_B_ante=SEC10_B;
  SEC10_B = digitalRead(SEC10);
  if (SEC10_B == HIGH && SEC10_B_ante== LOW) {
    secondsTens = (secondsTens + 1) % 6;
  }
}


void displayTime() {
  lcd.setCursor(6, 0);
  lcd.print(String(minutesTens) + String(minutes) + ":" + String(secondsTens) + String(seconds));
}

void decrementTime() {
  if (minutesTens == 0 && minutes == 0 && secondsTens == 0 && seconds == 0) {
    isRunning = false;
    digitalWrite(RUN, LOW);
    return;
  }
  
  if (seconds > 0) {
    seconds--;
  } else {
    if (secondsTens > 0) {
      secondsTens--;
      seconds = 9;
    } else {
      if (minutes > 0) {
        minutes--;
        secondsTens = 5;
        seconds = 9;
      } else {
        if (minutesTens > 0) {
          minutesTens--;
          minutes = 9;
          secondsTens = 5;
          seconds = 9;
        }
      }
    }
  }
}

void resetTime() {
  minutesTens = 0;
  minutes = 0;
  secondsTens = 0;
  seconds = 0;
  displayTime();
}
  