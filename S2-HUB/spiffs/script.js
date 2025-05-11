
//Infos
let DEVICE_TYPE;
let DEVICE_NAME;
let WIFI_SSID;
var WALKIE_STATUE;
var BATTERY_STATUS;
let gps_latitude;
let gps_longitude;
let gps_elevation;
var gps_elevation_type;
var TEMP_STATUS;
var lux;

var loginBox = document.getElementById("login-box");
var logoutBox = document.getElementById("logout-box");
var homeBox  = document.getElementById("home-box");

//Log-in
var loginBtn = document.getElementById("login-btn");

//Home
let home_welcome_label = document.getElementById("home-welcome-label");
let device_date_label = document.getElementById("device-date-label");
let device_time_label = document.getElementById("device-time-label");
let device_name_label = document.getElementById("device-name-label");
let device_wifi_ssid_label = document.getElementById("device-wifi-ssid-label");
let device_walkie_status_label = document.getElementById("device-walkie-status-label");
let device_battery_status_label = document.getElementById("device-battery-status-label");
let device_gps_latitude_label = document.getElementById("device-gps-latitude-label");
let device_gps_londitude_label = document.getElementById("device-gps-longitude-label");
let device_gps_elevation_label = document.getElementById("device-gps-elevation-label");
let device_temperature_label = document.getElementById("device_temperature_label");
let device_lux_label = document.getElementById("device_lux_label");
let camera_auto_dashcam_label = document.getElementById("camera-auto-dashcam-label");
let camera_auto_dashcam_switch = document.getElementById("camera-auto-dashcam-switch");

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

    // device_date_label.innerText = _getDate();
    // device_time_label.innerText = _getTime();
}


const _getDeviceInfo = () => {
    fetch("/device_info")
        .then(res => res.text())
        .then(data => {
            // Split CSV data
            const deviceInfo = data.split(",");

            DEVICE_TYPE = deviceInfo[0];
            device_name_label.innerHTML = deviceInfo[1];
            device_wifi_ssid_label.innerHTML   = deviceInfo[2];
            device_walkie_status_label.innerHTML = deviceInfo[3];
            device_battery_status_label.innerHTML = deviceInfo[4];
            device_gps_latitude_label.innerHTML  = deviceInfo[5];
            device_gps_londitude_label.innerHTML = deviceInfo[6];
            device_gps_elevation_label.innerHTML = `${deviceInfo[7]} ${deviceInfo[8] == '1'? 'M':'FT'}`;
            device_temperature_label.innerHTML = deviceInfo[9];
            device_lux_label.innerHTML = deviceInfo[10];
            device_date_label.innerText = deviceInfo[11];
            device_time_label.innerText = deviceInfo[12];

            deviceInfo[0] == '0'? hide_helmet_elements(): null;
            deviceInfo[0] == '2'? hide_bicycle_elemtents(): null;

        });
        
};


// function pingESP() {
//   fetch('/ping')
//     .then(res => res.text())
//     .then(txt => home_welcome_label.innerText = txt);
// }


// CHANGES

const _setDeviceTimeDate=()=>{
    const now = new Date();

    //Date
    const day = now.getDay();
    const date = now.getDate();
    const month = now.toLocaleString('default', { month: 'short' });
    const year = now.getFullYear();
    const dateString = `${month}-${date}`;
    
    //Time
    const hours = now.getHours();
    const minutes = now.getMinutes();
    const seconds = now.getSeconds();
    const timeString = `${hours}:${minutes < 10 ? '0' + minutes : minutes}`;

    device_date_label.innerText = dateString;
    device_time_label.innerText = timeString;

    const full = `${hours},${minutes},${seconds},${day},${date},${month},${year}`;

    fetch('/update_time_date',{
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
          },
          body: full
    });

}

const _change_device_name=(txt)=>{
    alert("device name changed");
}

const _change_wifi_ssid=(txt)=>{
    alert("SSID changed");
}

const _change_walkie_status=()=>{
    alert("WALKIE STATUS CHANGED");
}