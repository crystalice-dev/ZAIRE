
//DEVICE
const DEVICE_TYPE_SKI_GOGGLES = '0';
const DEVICE_TYPE_BICYCLE_HELMET = '1';
const DEVICE_TYPE_MOTOR_HELMET = '2';

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


//Views
const loginBox = document.getElementById("login-box");
const logoutBox = document.getElementById("logout-box");
const homeBox = document.getElementById("home-box");
const newNameChangeBox = document.getElementById("device-name-change-box");
const newWifiNameBox = document.getElementById("device-wifi-change-box"); 

//Log-in
var loginBtn = document.getElementById("login-btn");

//Home
let home_welcome_label = document.getElementById("home-welcome-label");
let device_date_label = document.getElementById("device-date-label");
let device_time_label = document.getElementById("device-time-label");
let device_name_label = document.getElementById("device-name-label");
let device_wifi_ssid_label = document.getElementById("device-wifi-ssid-label");
let device_walkie_status_label = document.getElementById("device-walkie-status-label");
let device_walkie_status_checkbox = document.getElementById("device-walkie-status-checkbox");
let device_battery_status_label = document.getElementById("device-battery-status-label");
let device_gps_latitude_label = document.getElementById("device-gps-latitude-label");
let device_gps_londitude_label = document.getElementById("device-gps-longitude-label");
let device_gps_elevation_label = document.getElementById("device-gps-elevation-label");
let device_temperature_label = document.getElementById("device_temperature_label");
let device_lux_label = document.getElementById("device_lux_label");
let camera_auto_dashcam_label = document.getElementById("camera-auto-dashcam-label");
let camera_auto_dashcam_check = document.getElementById("device-auto-dashcam-status-checkbox");
let device_blindspot_monitoring_label = document.getElementById("device-blindspot-monitoring-label");
let device_blindspot_monitoring_check = document.getElementById("device-blindspot-monitoring-status-checkbox");
let device_auto_back_light_label = document.getElementById("device-auto-back-light-label");
let device_auto_back_light_check = document.getElementById("device-auto-back-light-checkbox");
let device_turn_signal_duration_label = document.getElementById("turn-signal-duration-label");
let device_video_label = document.getElementById("device-video-label");
let device_photo_label = document.getElementById("device-photo-label");

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
            device_walkie_status_label.innerHTML =`${ deviceInfo[3] == '1'? 'ON':'OFF'}`;
            device_walkie_status_checkbox.value = deviceInfo[3] == '1'? true : false;
            device_battery_status_label.innerHTML = deviceInfo[4];
            device_gps_latitude_label.innerHTML  = deviceInfo[5];
            device_gps_londitude_label.innerHTML = deviceInfo[6];
            device_gps_elevation_label.innerHTML = `${deviceInfo[7]} ${deviceInfo[8] == '1'? 'M':'FT'}`;
            device_temperature_label.innerHTML = deviceInfo[9];
            device_lux_label.innerHTML = deviceInfo[10];
            device_date_label.innerText = deviceInfo[11];
            device_time_label.innerText = deviceInfo[12];
            camera_auto_dashcam_label.innerHTML = deviceInfo[13] == '1'? 'ON' : 'OFF';
            camera_auto_dashcam_check.checked = deviceInfo[13] == '1'? true : false;
            device_blindspot_monitoring_label.innerHTML = deviceInfo[14] == '1'? 'ON' : 'OFF';
            device_blindspot_monitoring_check.checked = deviceInfo[14] == '1'? true : false;
            device_auto_back_light_label.innerHTML = deviceInfo[15] == '1'? 'ON' : 'OFF';
            device_auto_back_light_check.checked = deviceInfo[15] == '1'? true : false;
            device_turn_signal_duration_label.innerHTML = `${deviceInfo[16]} sec`;
            const radios = document.getElementsByName("delay");
            for(let i = 0; i < radios.length; i ++){
                if(radios[i].value == deviceInfo[16]){
                    radios[i].checked = true;
                    break;
                }
            }

            device_video_label.innerHTML = `Videos: ${deviceInfo[17]}`;
            device_photo_label.innerHTML = `Photos: ${deviceInfo[18]}`;

            deviceInfo[0] == DEVICE_TYPE_SKI_GOGGLES? hide_helmet_elements(): null;
            deviceInfo[0] == DEVICE_TYPE_MOTOR_HELMET? hide_bicycle_elemtents(): null;

        });
        
};

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

const _goBack=()=>{
    homeBox.hidden = false;
    newNameChangeBox.hidden = true;
    newWifiNameBox.hidden = true;
}

const _change_device_name_present=()=>{
    homeBox.hidden = true;
    newNameChangeBox.hidden = false;
}

const _change_wifi_ssid_present=()=>{
    homeBox.hidden = true;
    newWifiNameBox.hidden = false;
}

const _change_device_name = () => {
    const input = document.getElementById("device-new-name-input");
    const current = document.getElementById("device-name-label");
    const name = input.value;

   if (name !== '' && !name.includes(' ')) {
        fetch("/update_device_name", {
            method: "POST",
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded'
            },
            body: name
        });

        current.innerHTML = name;
    }
    
    input.value = '';  // Clear the input box
    
    _goBack();
};


const _change_wifi_ssid=()=>{
    const input = document.getElementById("device-wifi-ssid-input");
    const current = document.getElementById("device-wifi-ssid-label");
    const name = input.value;

    if (name !== '' && !name.includes(' ')) {
            fetch("/update_wifi_ssid", {
                method: "POST",
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                },
                body: name
            });

            current.innerHTML = name;
        }
        
        input.value = '';  // Clear the input box
        
        _goBack();
}

const _change_walkie_status = () => {
    const checkbox = document.getElementById("device-walkie-status-checkbox");
    const label = document.getElementById("device-walkie-status-label");

    var value;

    if (checkbox.checked) {
        label.innerText = "ON";
        value = "W1";
    } else {
        label.innerText = "OFF";
        value = "W0";
    }

    fetch("/update_accessory",{
        method:"POST",
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: value
    })

};

const _change_auto_dashcam_status = () => {
    const checkbox = document.getElementById("device-auto-dashcam-status-checkbox");
    const label = document.getElementById("camera-auto-dashcam-label");

    var value;

    if (checkbox.checked) {
        label.innerText = "ON";
        value = "D1";
    } else {
        label.innerText = "OFF";
        value = "D0";
    }

    fetch("/update_accessory",{
        method:"POST",
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: value
    })

};

const _change_blindspot_monitoring_status = () => {
    const checkbox = document.getElementById("device-blindspot-monitoring-status-checkbox");
    const label = document.getElementById("device-blindspot-monitoring-label");

    var value;

    if (checkbox.checked) {
        label.innerText = "ON";
        value = "B1";
    } else {
        label.innerText = "OFF";
        value = "B0";
    }

    fetch("/update_accessory",{
        method:"POST",
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: value
    })

};

const _change_auto_back_light_status = () => {
    const checkbox = document.getElementById("device-auto-back-light-checkbox");
    const label = document.getElementById("device-auto-back-light-label");

    var value;

    if (checkbox.checked) {
        label.innerText = "ON";
        value = "L1";
    } else {
        label.innerText = "OFF";
        value = "L0";
    }

    fetch("/update_accessory",{
        method:"POST",
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: value
    })

};

const _change_turn_signal_duration = () => {
    const radios = document.getElementsByName("delay");
    var value;
    for (let i = 0; i < radios.length; i++) {
        if (radios[i].checked) {
            document.getElementById("turn-signal-duration-label").innerHTML = radios[i].value + " sec";
            
            value = `S${radios[i].value}`;

            fetch("/update_accessory",{
                method:"POST",
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                },
                body: value
            })

            break;
        }
    }

};

