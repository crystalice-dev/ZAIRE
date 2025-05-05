#include <globalVar.h>





char *html =
"<!DOCTYPE html><html><head><title>Zaire Settings</title>"
"<style>"
"body{font-family:sans-serif;padding:2em;background:#f4f4f4;}h1{color:#333;}"
".section{margin-bottom:2em;}label{display:block;margin:0.5em 0 0.2em;}input{padding:0.4em;width:100%%;}"

"#modal{display:none;position:fixed;top:0;left:0;width:100%%;height:100%%;"
"background:rgba(0,0,0,0.6);z-index:1000;display:flex;justify-content:center;align-items:center;}"

"#modal-content{background:white;padding:2em;width:85vw;"
"border-radius:12px;text-align:center;box-shadow:0 8px 30px rgba(0,0,0,0.3);font-size:1.2em;}"
"#modal-content button{margin-top:1em;padding:0.6em 1.2em;font-size:1em;}"
"</style>"
"</head><body>"

"<h1>Zaire Helmet Status</h1>"
"<div class='section'><strong>Device Name:</strong> Helmet_Alpha</div>"
"<div class='section'><strong>Wi-Fi SSID:</strong> SuperMon</div>"
"<div class='section'><strong>Walkie Status:</strong> <span style='color:green;'>Online</span></div>"
"<div class='section'><strong>GPS Lock:</strong> <span style='color:red;'>Searching...</span></div>"
"<div class='section'><strong>Battery:</strong> 87%%</div>"
"<div class='section'><strong>Sensor Readings:</strong><br/>"
"Accel: X=0.12 Y=0.03 Z=9.81<br/>"
"Temp: 36.5°C<br/>"
"Light: 740 lux"
"</div>"
"<hr/>"

"<div><button id='modalButton'>Open Modal</button></div>"

"<h2>Settings</h2>"
"<form method='POST' action='/update'>"
"<label>Wi-Fi SSID</label><input type='text' name='ssid' value='SuperMon'>"
"<label>Wi-Fi Password</label><input type='password' name='pass' value='123nopass'>"
"<label>Device Name</label><input type='text' name='name' value='Helmet_Alpha'>"
"<br/><br/><input type='submit' value='Save Settings'>"
"</form>"

"<hr/><h2>Interaction</h2>"
"<button onclick=\"pingESP()\">Ping ESP32</button>"

"<div id='modal'><div id='modal-content'>"
"<p id='modal-text'></p><br/><button onclick=\"hideModal()\">Close</button>"
"</div></div>"

"<script>"
"function showModal(msg){"
"  document.getElementById('modal-text').innerText = msg;"
"  document.getElementById('modal').style.display = 'flex';"
"}"
"function hideModal(){"
"  document.getElementById('modal').style.display = 'none';"
"}"
"function pingESP() {"
"  fetch('/ping')"
"    .then(res => res.text())"
"    .then(txt => showModal('ESP32 says: ' + txt));"
"}"

"</script>"

"</body></html>";
