# Smart-Clock
<li>This is a Project for computer programming 06016315</li>
<li>โปรเจคนี้ เป็นส่วนหนึ่งของรายวิชา คอมพิวเตอร์โปรแกรมมิ่ง 06016315</li>

## Abstract
&emsp;ความเป็นมาเป็นไปของโปรเจกต์นี้คือ พวกเรากลุ่ม แพรนวลพาเพลินได้ปรึกษาและพูดคุยกันว่าอยากทำโปรเจกต์ที่สามารถนำมาใช้ในชีวิตจริงและอาจนำมาสานต่อได้ โดยท้ายที่สุดตัดสินใจเลือกที่จะทำโปรเจต์ที่เกี่ยวข้องกับ micro controller โดยทางเราเลือกที่จะสร้างเป็นนาฬิกาที่สามารถแสดงเวลาได้ จับเวลาได้ นับเวลาถอยหลังได้ ตั้งปลุกได้ โดยทุกฟังก์ชั่นการทำงานจะสามารถควบคุมผ่าน smartphone เชื่อมต่อผ่าน WIFI กับตัวบอร์ด Node MCU ที่เป็นอุปกรณ์หลักของโปรเจกต์นี้

<h2><a id="user-content-library-in-use" class="anchor" aria-hidden="true" href="#library-in-use"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a><a target="_blank" rel="noopener noreferrer" href=""><img src="" alt="" style="max-width:100%;"></a>Library in Use</h2>
<ul>
<li>ESP8266WiFi.h</li>
  <li>ESP8266HTTPClient.h</li>
  <li>WiFiUdp.h</li>
  <li>NTPClient.h</li>
  <li>TimeLib.h</li>
  <li>ArduinoJson.h</li>
  <li>SPI.h</li>
  <li>Wire.h</li>
  <li>Adafruit_GFX.h</li>
  <li>Adafruit_SSD1306.h</li>
  <li>FirebaseArduino.h</li>
</ul>

<h2><a id="user-content-required-components" class="anchor" aria-hidden="true" href="#required-components"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a><a target="_blank" rel="noopener noreferrer" href=""><img src="" alt="" style="max-width:100%;"></a>Required Components</h2>
<table>
<thead>
<tr>
<th align="center">NodeMCU ESP8266</th>
<th align="center">OLED Display Module 128X64 0.96"</th>
<th align="center">Ultrasonic sensor HC-SR04</th>
<th align="center">Buzzer</th>
</tr>
</thead>
<tbody>
<tr>
<td align="center"><a align="center"><img src="img/equipment1.jpg" width="200px" style="max-width:100%;"></a></td>
<td align="center"><a align="center"><img src="img/equipment2.jpg" width="200px" style="max-width:100%;"></a></td>
<td align="center"><a align="center"><img src="img/equipment3.jpg" width="200px" style="max-width:100%;"></a></td>
<td align="center"><a align="center"><img src="img/equipment4.jpg" width="100px" style="max-width:100%;"></a></td>
</tr>
</tbody>
</table>
<table>
<thead>
<tr>
<th align="center">RGB LED 5mm</th>
<th align="center">Resistor 100ohm</th>
<th align="center">Jumper wire</th>
</tr>
</thead>
<tbody>
<tr>
<td align="center"><a align="center"><img src="img/equipment5.jpg" width="200px" style="max-width:100%;"></a></td>
<td align="center"><a align="center"><img src="img/equipment6.jpg" width="200px" style="max-width:100%;"></a></td>
<td align="center"><a align="center"><img src="img/equipment7.jpg" width="100px" style="max-width:100%;"></a></td>
</tr>
</tbody>
</table>

# Poster
<p><img src="img/poster.jpg" alt="" style="max-width:100%;"></p>

# Video
[![Watch the video](https://img.youtube.com/vi/drSTCwKjHcs/hqdefault.jpg)](https://www.youtube.com/watch?v=drSTCwKjHcs)

<!--Group Members-->
## Group Members

|<img src="img/mem1.jpg" width="120px" height="120px">|<img src="img/mem2.jpg" width="120px" height="120px">|<img src="img/mem3.jpg" width="120px" height="120px">|<img src="img/mem4.jpg" width="120px" height="120px">|
|:---:|:---:|:---:|:---:|
|[ddessertt](https://github.com/ddessertt)|[johntnw](https://github.com/johntnw)|[gearprn](https://github.com/gearprn)|[Vacharavat](https://github.com/Vacharavat)|
  |Natthaphat Kongthong<br>นางสาว ณัฏฐพัชร กองทอง|Thanawat Wongsud<br>นาย ธนวัฒน์ วงษ์สุด|Purinut Uomrod<br>นาย ภูริณัฐ อ่วมรอด|Vacharavat Kesbuntherng<br>นาย วชรวรรษ เกษบรรเทิง|
|61070051|61070077|61070172|61070192|

<h1><a id="user-content-special-thanks" class="anchor" aria-hidden="true" href="#special-thanks"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>Special Thanks</h1>

<table>
<thead>
<tr>
<th align="center"><img src="img/advisor1.jpg" alt="" width="250px" height="250px"></a></th>
<th align="center"><img src="img/advisor2.jpg" alt="" width="250px" height="250px"></a></th>
</tr>
</thead>
<tbody>
<tr>
<td align="center"> Asst Profressor Kitsuchart Pasupa<br>ผศ. ดร. กิติ์สุชาต พสุภา</td>
<td align="center"> Asst Profressor Panwit Tuwanut<br>ผศ. ดร. ปานวิทย์ ธุวะนุติ</td>
</tr>
</tbody>
</table>
