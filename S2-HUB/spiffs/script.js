
var DEVICE_TYPE;
var subDEVICE_TYPE;

var loginBox = document.getElementById("login-box");
var logoutBox = document.getElementById("logout-box");
var homeBox  = document.getElementById("home-box");

//Log-in
var loginBtn = document.getElementById("login-btn");

//Home
var home_welcome_label = document.getElementById("home-welcome-label");
var device_date_label = document.getElementById("device-date-label");
var device_time_label = document.getElementById("device-time-label");
var device_name_label = document .getElementById("device-name-label");


// Modular elemets
var elevation_row = document.getElementById("elevation-row");
var light_sensor_row = document.getElementById("light-sensor-row");
var auto_dash_row = document.getElementById("auto-dash-row");
var blindspot_monitoring_row = document.getElementById("blindspot-monitoring-row");
var auto_stop_row = document.getElementById("auto-stop-light-row");
var turn_signal_duration_row = document.getElementById("turn-signal-duration-row");

const hide_helmet_elements=()=>{
    light_sensor_row.hidden = true;
    blindspot_monitoring_row.hidden = true;
    auto_stop_row.hidden = true;
    auto_dash_row.hidden = true;
    turn_signal_duration_row.hidden = true;
}

const hide_goggle_elements=()=>{
    elevation_row.hidden = true;
}

const hide_bicycle_elemtents=()=>{
    turn_signal_duration_row.hidden = true;
}

//OnStart
loginBtn.onclick=()=>{
    loginBox.hidden = true;
    homeBox.hidden = false;
    onBoard();
}

const onBoard=()=>{
    _getDeviceInfo(); // Get all device info's

    device_date_label.innerText = _getDate();
    device_time_label.innerText = _getTime();
    device_name_label.innerText = "YANN";

    DEVICE_TYPE === 1? hide_helmet_elements(): hide_goggle_elements();
    subDEVICE_TYPE === 0? hide_bicycle_elemtents(): null;
}

const _getDate=()=>{ // Data from browser
    const now = new Date();

    const day = now.getDate();
    const month = now.toLocaleString('default', { month: 'short' });
    const year = now.getFullYear();

    const dateString = `${month} ${day}, ${year}`;
    return dateString;
}

const _getTime=()=>{ // Data from browser
    const now = new Date();

    const hours = now.getHours();
    const minutes = now.getMinutes();
    
    const timeString = `${hours}:${minutes < 10 ? '0' + minutes : minutes}`;
    return timeString;
}

const _getDeviceInfo=()=>{ // Data from Device
    fetch("/device_info")
        .then(res=>res.txt)
        .then(txt=>{
            
        });
}

// function pingESP() {
//   fetch('/ping')
//     .then(res => res.text())
//     .then(txt => home_welcome_label.innerText = txt);
// }


// CHANGES

const _change_device_name=(txt)=>{
    alert("device name changed");
}

const _change_wifi_ssid=(txt)=>{
    alert("SSID changed");
}

const _change_walkie_status=()=>{
    alert("WALKIE STATUS CHANGED");
}