# Esp32PIR
Esp32 PIR sensor project

So I've finally received the two ESP32 boards I ordered.

https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

ESP32-MINI-32-V2.0

They look just like this: 
![alt text](./README_img/image1.jpg "Logo Title Text 1")

I've not soldered any pin headers on, but I'd like to see if I can make one flash.

Need to make sure board in installed in Arduino.
https://www.instructables.com/id/How-to-Set-Up-WeMos-TTgo-ESP32-Uno-D1-R32/

https://dl.espressif.com/dl/package_esp32_index.json

There is a flash example (and others) here https://github.com/LilyGO/ESP32-MINI-32-V2.0/blob/master/Module_test/Blink/Blink.ino

Installed the ESP 32 dev board driver for arduino.
Selected board ESP32 Dev Module
Chose Port /dev/cu.chbubserialfa130

Uploaded esp32_blink

```21:41:18.949 -> ⸮⸮ ⸮ ⸮⸮⸮ ⸮   ⸮ ⸮⸮⸮⸮⸮ ⸮⸮             ⸮   ⸮        ⸮        ⸮ ⸮⸮⸮ ⸮⸮⸮⸮⸮⸮⸮Ғ⸮Ҫ⸮j
21:41:18.949 -> 
21:41:18.949 -> rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
21:41:19.155 -> configsip: 0, SPIWP:0xee
21:41:19.155 -> clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
21:41:19.155 -> mode:DIO, clock div:1
21:41:19.155 -> load:0x3fff0018,len:4
21:41:19.155 -> load:0x3fff001c,len:1216
21:41:19.155 -> ho 0 tail 12 room 4
21:41:19.155 -> load:0x40078000,len:9720
21:41:19.155 -> ho 0 tail 12 room 4
21:41:19.155 -> load:0x40080400,len:6352
21:41:19.155 -> entry 0x400806b8
21:41:19.155 -> blink start
21:41:20.160 -> blink on
21:41:21.137 -> blink off
21:41:22.642 -> blink on
21:41:23.667 -> blink off
21:41:25.132 -> blink on
21:41:26.148 -> blink off
21:41:27.650 -> blink on
21:41:28.659 -> blink off
21:41:30.136 -> blink on
21:41:31.150 -> blink off
21:41:32.653 -> blink on
```

Tried esp32_wifi_scan

```
21:45:06.795 -> scan done
21:45:06.795 -> 23 networks found
21:45:06.795 -> 1: DIRECT-92-HP ENVY 4520 series (-23)*
21:45:06.795 -> 2: Virgin Media (-61)*
21:45:06.795 -> 3: VM4826469 (-62)*
21:45:06.795 -> 4: Ocean (-66)*
21:45:06.832 -> 5: ESP_6B2A09 (-71) 
21:45:06.832 -> 6: VMP8610697 (-75)*
21:45:06.832 -> 7: ManCaveIOT (-77)*
21:45:06.866 -> 8: ESP_380D53 (-78) 
21:45:06.866 -> 9: Virgin Media (-85)*
21:45:06.866 -> 10: Eureka (-86)*
21:45:06.866 -> 11: BTWifi-with-FON (-87) 
21:45:06.899 -> 12: DIRECT-43-HP ENVY Photo 6200 (-90)*
21:45:06.899 -> 13: VM9399380-2G (-91)*
21:45:06.935 -> 14: VM6258824 (-91)*
21:45:06.935 -> 15: Virgin Media (-92)*
21:45:06.935 -> 16: Virgin Media (-93)*
21:45:06.935 -> 17: Virgin Media (-93)*
21:45:06.969 -> 18: The Passeys (-93)*
21:45:06.969 -> 19: Virgin Media (-93)*
21:45:06.969 -> 20: VM4607075 (-94)*
21:45:06.969 -> 21: VM0536174 (-94)*
21:45:07.003 -> 22: VM9399380-5G_2GEXT (-95)*
21:45:07.038 -> 23: LAN Solo (-95)*
21:45:07.038 -> 
21:45:12.038 -> scan start
```

The PIR board I am using takes 5V VCC, but has a regulator which drops that to 3.3V.
This means the output trigger voltage is 3.3V.

So in theory, if I wire this up to a GPIO on the eps 32, it will just work...

I've wired the sensor directly to the board, and changed the blink sketch to read from GPIO17.
Added pulldown to the pin set in esp32_read. This seems to work.

Connected to home wifi with esp32_wifiServer.ino

Things the ESP can say.

Hiya! Just got given an IP address of 192.168.0.50. Has the power been off?

[05:00-06:00] "Good morning! Early start today?"
[07:15-09:00] "School run, was it?"
[10:00-12:00] "The house could do with a spruce!"
[12:00-14:00] "Back from shopping?"
[14:00-15:00] "Here to pick up the kids!"
[15:00-16:30] "Kids back from the park?"
[16:30-17:30] "You made good time!"
[17:30-18:00] "How was the weather out there?"
[18:00-20:00] "Kids back from cubs/rainbows?"
[20:00-21:00] "Shopping's late tonight?"
[21:00-22:00] "Did you forget something?"
[22:00-23:00] "Good night!"
[23:00-23:59] "Phew, late one is it?"
[00:00-04:00] "Not normally anyone pottering around at this time of night. Everything ok?"
[12:00-14:00] "Hi! Want to play hide and seek? I'll count first... 1...2...3...3 and a half..."
[12:00-14:00] "Ooo, nice outfit."
[12:00-14:00] "Have you been here the whole time?"

Digressed onto Tetris clock project - see /Tetris.
I want to steal lots of this code for my final PIR work, since it has time all worked out.

Script

This is not an entirely new project - it's actually a re-implementation of an old project.
Until recently I had a raspberry pi doing this same job, but also several other jobs, like hosting a website and running various scheduled tasks.
I'm splitting up these responsibilities onto smaller, cheaper dedicated hardware, so that they can be tinkered with independently.

In this case, the job is to tweet whenever someone walks past a PIR sensor.
There are strengths and limits to using twitter to send myself information. It wouldn't be a big task to switch to another service.

I would have liked to delay this task until I could 3d print a better case, but I decided to modify a cheap ABS enclosure - even if the results are a little ugly.

I'm using sugru here to reinforce and neaten the join between the enclosure and plug. It's relatively expensive but it's ideal for small jobs like this.

I've switched recently to making projects more modular, soldering in headers and connectors, so they can be separated again to more easily fix bugs or patch for security.

I did a rotten job filming here, sorry you can mostly just see the back of my hands..

Because there is no direct interface, I have it tweet once it has picked up an IP address on my home wifi.

It then tweets one of 100 movies quotes when the PIR sensor is triggered, then blocks for 15 minutes (to avoid spamming me too often)

I plan to build at least one more of these to put out in the workshop.