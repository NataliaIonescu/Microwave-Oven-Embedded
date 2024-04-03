 Microwave oven

Design an Arduino Uno microsystem that will control a microwave oven. The operation of the oven is done by means of 5 pushbuttons and a liquid crystal display. The heating time is displayed in the format mm: ss. The oven works as follows:

1. At power up, the initial time value is 00:00

2. First, the user sets the heating time. The setting of the heating time is done by means of three pushbuttons: MIN10, MIN and SEC10. The maximum value of this time is 99:50.

3. The heating starts after the user presses the START button. During heating, the time previously set decreases until it reaches zero (00:00). When the time reaches zero, the heating stops. For example, if the time value after setting phase is 08:00, in the heating phase it will be displayed as: 08:00→07:59→07:58 →... 00:03→00:02→00:01 → 0:00.

4. Heating can be switched off at any time by pressing the CANCEL button. Pressing CANCEL causes the time to become zero (00:00). During heating, pressing the MIN10, MIN and SEC10 push buttons does not change the time.

The role of the push buttons MIN10, MIN and SEC10 through which the heating time is set is:

1. Pressing the MIN10 button increments circularly the tens of minutes: ......70:00→80:00→90:00→ 00:00→10:00...
2. Pressing the MIN button circularly increments minutes: ...58:00→59:00→50:00→51:00→52:00...
3. Pressing the SEC10 button circularly increases the tens of seconds: ...10:30→10:40→10:50→ 10:00...
4. Push buttons show instability.

The microsystem generates the RUN output which is '1' during heating. The logical value of the RUN will be displayed via an LED.

Specifications and mandatory requirements:
Time management with soft loops such as for (i=0;i<DELAY;i++) { } or with delay (...) function is not allowed.
