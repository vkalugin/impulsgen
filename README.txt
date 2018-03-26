Fast and simple generator of artificial impulses for Arduino DUE and M0.
It is optimized for the shortest possible impulses (few us for DUE).
All other boards are untested.
Make sure gnu99 C standard (or newer) is enabled in Arduino environment. To enable this in Arduino IDE, -std=gnu99 should be added in file platform.txt after compiler.c.flags= (in the same line).
