#include <globalVar.h>



const char PAGE_main[] = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ZAIRE HELMETS SETTINGS</title>
</head>
<body id="bb" style="display: flex; justify-content: center; height: 100vh; margin: 0; padding-top: 5dvh; ">

   

    <div style="text-align: center;">
        <h2  style="margin: 0;">ZAIRE HELMETS SETTINGS</h2>
        <h6 id="typeText" >TYPE: MOTORCYCLE</h6>
        <h4>BATTERY: ##% </h4>
        
        <div id="ui" hidden = "true" >

            <table style="border: 5px solid black; width: 25em; margin: auto; border-collapse: collapse; ">
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>SETTING</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4>CURRENT</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4>CHANGE</h4></td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>HELMET NAME</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="deviceNameText" >ZAIRE HELMETS</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <textarea style="width: 70%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="8"></textarea>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>TIME & DATE</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h5 id="dateTimeText" >12-22-2000 12:30PM</h5></td>
                    <td style="border: 2px solid black; text-align: center;"  >
                        <div style="display: flex; align-items: center; justify-content: center; gap: 5px; margin-top: 1vh;" >
                            <select id="hourFormat" style="width: 70px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                                <option value="12HR">12HR</option>
                                <option value="24HR">24HR</option>
                            </select>
                        </div>
                        <div style="display: flex; align-items: center; justify-content: center; gap: 5px;">
                            <h6>DATE: </h6>
                            <input type="tel" id="monthInput" style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2" placeholder="M" ></input>
                            <h5 style="margin: 0; line-height: 2em;">-</h5>
                            <input type="tel" id="dateInput" style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2" placeholder="D" ></input>
                            <h5 style="margin: 0; line-height: 2em;">-</h5>
                            <input type="tel" id="yearInput" style="width: 30%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="4" placeholder="YYYY" ></input>
                        </div>
                        <div id="12hrDiv" style="display: flex; align-items: center; justify-content: center; gap: 5px;">
                            <H6>TIME: </H6>
                            <input type="tel" id="hourInput" style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2"></input>
                            <h5 style="margin: 0; line-height: 2em;">-</h5>
                            <input type="tel" id="minutesInput" style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2"></input>
                            <h5 style="margin: 0; line-height: 2em;">-</h5>
                            <select style="width: 50px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                                <option value="AM">AM</option>
                                <option value="PM">PM</option>
                            </select>
                        </div>
                        <div id="24hrDiv" style="display: none; align-items: center; justify-content: center; gap: 5px;">
                            <H6>TIME: </H6>
                            <input type="tel" id="hourInput24"  style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2"></input>
                            <h5 style="margin: 0; line-height: 2em;">-</h5>
                            <input type="tel" id="minutesInput24" style="width: 20%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="2"></input>
                        </div>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>GPS METRIC</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="gpsMetricText" >MPH</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="gpsMetric" style="width: 70px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option value="MPH">MPH</option>
                            <option value="KMH">KMH</option>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>AUTO DASHCAM</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="autoDashCamText" >YES</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="autoDashCam" style="width: 70px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option value="YES">YES</option>
                            <option value="NO">NO</option>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>WALKIE TALKIE</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="walkieTalkieText" >YES</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="walkieTalkie" style="width: 70px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option value="YES">YES</option>
                            <option value="NO">NO</option>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>EMERGENCY NUMBER</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="emergencyNumberText" >911 (US ONLY)</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <input type="tel"  id="phoneNumber" style="width: 70%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="10"></input>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>REMOTE UP FUNC</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="remoteUpText" >TBH</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="remoteUpFunc" style="width: 150px; ; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option  value="CAPTURE">CAPTURE PHOTO</option>
                            <option value="START_STOP_DASHCAM">DASHCAM</option>
                            <option value="BACK_LIGHT">BACK_LIGHT</option>
                            
                        </select>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>REMOTE RT FUNC</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="remoteRtText" >TBH</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="remoteRtFunc" style="width: 150px; ; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option  value="CAPTURE">CAPTURE PHOTO</option>
                            <option value="START_STOP_DASHCAM">DASHCAM</option>
                            <option value="BACK_LIGHT">BACK_LIGHT</option>
                            
                        </select>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>REMOTE LT FUNC</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="remoteLtText" >TBH</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="remoteLtFunc" style="width: 150px; ; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option  value="CAPTURE">CAPTURE PHOTO</option>
                            <option value="START_STOP_DASHCAM">DASHCAM</option>
                            <option value="BACK_LIGHT">BACK_LIGHT</option>
                            
                        </select>
                    </td>
                </tr>
                <tr id="bicycleTurnBlock" >
                    <td style="border: 2px solid black; text-align: center;"><h4>BICYCLE TURN SIGN</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="bicycleTurnSignText" >YES</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="bicycleTurn" style="width: 70px; ; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option  value="YES">YES</option>
                            <option value="NO">NO</option>
                        </select>
                        <div>
                            <select id="turnSignalDuration" style="width: 70px; ; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                                <option  value="3sec">3sec</option>
                                <option value="5sec">5sec</option>
                                <option value="7sec">7sec</option>
                            </select>
                        </div>
                    </td>
                </tr>
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>BLINDSPOT MONITOTING</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><h4 id="blindSpotMonitoringText" >YES</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <select id="blindspot" style="width: 70px; height: 2em; font-size: 1em; text-align: center; padding: 5px; box-sizing: border-box;">
                            <option value="YES">YES</option>
                            <option value="NO">NO</option>
                        </select>
                    </td>
                </tr>
                <tr style="background-color: green;" >
                    <td style="border: 2px solid black; text-align: center;"><h4 style="color: white;" >SAVE?</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="saveSettingsNO" >NO</button></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="saveSettingsYES" >YES</button></td>
                </tr>
                
                <tr style="background-color: RED;" >
                    <td style="border: 2px solid black; text-align: center;"><h4 style="color: white;" >RESET SERVER PASSWORD ?</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetServerPasswordBTN" >YES</button></td>
                </tr>
                <tr style="background-color: RED;" >
                    <td style="border: 2px solid black; text-align: center;"><h4 style="color: white;" >RESET HELMET PASSCODE ?</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetHelmetPassCodeBTN" >YES</button></td>
                </tr>
                <tr style="background-color: RED;" >
                    <td style="border: 2px solid black; text-align: center;"><h4 style="color: white;" >RESET FACTORY ?</h4></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetToFactoryBTN" >YES</button></td>
                </tr>
                
            </table>
            <button style="margin-top: 2vh; margin-bottom: 5vh;" >VIEW CERTIFICATE</button>
        </div>
        <div id="resetServerPasswordUI" hidden = "true" >
            <h3 style="color: red;" >RESET SERVER PASSWORD</h3>
            <table style="border: 5px solid black; width: 25em; margin: auto; border-collapse: collapse; ">
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>SETTING</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <textarea id="resetServerPasswordTextarea" style="width: 90%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="12" placeholder="NEW PASSWORD" ></textarea>
                    </td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetServerPasswordSaveBTN" >SAVE</button></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetServerPasswordCancelBTN" >CANCEL</button></td>
                </tr>
            </table>
        </div>
        <div id="resetHelmetPassCodeUI" hidden = "true" >
            <h3 style="color: red;" >RESET HELMET PASSCODE</h3>
            <table style="border: 5px solid black; width: 25em; margin: auto; border-collapse: collapse; ">
                <tr>
                    <td style="border: 2px solid black; text-align: center;"><h4>SETTING</h4></td>
                    <td style="border: 2px solid black; text-align: center;">
                        <input type="tel"  style="width: 90%; height: 2em; resize: none; padding: 5px; box-sizing: border-box; font-size: 1em; text-align: center;" maxlength="6" minlength="6" placeholder="NEW PASSWORD" id="resetHelmetPassCodeTextarea" ></input>
                    </td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetHelmetPassCodeSaveBTN" >SAVE</button></td>
                    <td style="border: 2px solid black; text-align: center;"><button id="resetHelmetPassCodeCancelBTN" >CANCEL</button></td>
                </tr>
            </table>
        </div>
        <div id="resetFactoryUI" hidden = "true" style="background-color: red; color: white;" >
            <h3 style="color: white;" >RESET HELMET TO FACTORY</h3>
            <table style="border: 5px solid white; width: 25em; margin: auto; border-collapse: collapse; ">
                <tr>
                    <td style="border: 2px solid white; text-align: center;"><h4>BACK TO FACTORY? </h4></td>
                    <td style="border: 2px solid white; text-align: center;"><button id="resetToFactoryYesBTN" >YES</button></td>
                    <td style="border: 2px solid white; text-align: center;"><button id="resetToFactoryCancelBTN" >CANCEL</button></td>
                </tr>
            </table>
        </div>

        <div id="certificateBlock" >
            <h1 style="color: black;" >CERTIFICATE</h1>
            <textarea
                id="certificateText"
                type="text"
                style=" width: 450px;; height: 300px; border-width: 3; border-color: black;"
                disabled
                   
                
            ></textarea>
            
            <div >
                <input id="certificateCheckbox" type="checkbox"  >I HAVE READ THE TERMS AND CONDITIONS.</input>               
            </div>
            <div>
                <div>
                    <H6>EXTENDED WARRANTY CODE: </H6>
                    <input type="number" style="text-align: center;" value="00000" disabled/>
                </div>
                <h6>PLEASE EMAIL EMAIL THIS CODE TO <h4>Zairehelmets@crystralicestudio.com</h4> to get the full 3 years warranty. </h6>
            </div>
            <div style="margin-top: 1vh; display: flex; justify-content: center; align-items: center; "  >
                <h6>Initial here in Upper Case -> </h6>
                <input
                    type="text"
                    style="text-align: center; width:30px; margin-left: 10px; "
                    maxlength="2"
                    id="certificateInitialText"
                />
            </div>
            
            <div style="margin-top: 3vh;" >
                <button id="certificateButton" >SIGN CERTIFICATE</button>
            </div>
        </div>
    
        <div id="passCodeBlock" >
            <h1 style="color: black;" >PASSCODE</h1>
            <input
                type="tel"
                style="text-align: center;"
                maxlength="6"
                id="passCodeBlockText"
            />
            <button id="passCodeBlockBTN" >ENTER</button>
        </div>

    </div>

    <script>
        //Main VIEWS
        var certificateBlock = document.getElementById("certificateBlock");
        var passCodeBlock = document.getElementById("passCodeBlock");
        var ui = document.getElementById("ui");
        var certificateBlockHidden = true;
        var passCodeBlockHidden = true;
        var uiHidden = true;

    //Document OBJ 
        var helmetType    = document.getElementById("typeText");
        
        var bicycleTurnBlock = document.getElementById("bicycleTurnBlock");
        var deviceNameText = document.getElementById("deviceNameText");
        var dateTimeText = document.getElementById("dateTimeText");
        var gpsMetricText = document.getElementById("gpsMetricText");
        var autoDashCamText = document.getElementById("autoDashCamText");
        var walkieTalkieText = document.getElementById("walkieTalkieText");
        var emergencyNumberText = document.getElementById("emergencyNumberText");
        var remoteUpText = document.getElementById("remoteUpText");
        var remoteRtText = document.getElementById("remoteRtText");
        var remoteLtText = document.getElementById("remoteLtText");
        var bicycleTurnSignText = document.getElementById("bicycleTurnSignText");
        var blindSpotMonitoringText = document.getElementById("blindSpotMonitoringText");
        var passCodeBlockText = document.getElementById("passCodeBlockText");
        var passCodeBlockBTN = document.getElementById("passCodeBlockBTN");
        var hourFormat    = document.getElementById("hourFormat");
        var phoneTextArea = document.getElementById("phoneNumber");
        var _12hrDiv      = document.getElementById("12hrDiv");
        var _24hrDiv      = document.getElementById("24hrDiv");
        var monthInput    = document.getElementById("monthInput");
        var dateInput     = document.getElementById("dateInput");
        var yearInput     = document.getElementById("yearInput");
        var hourInput     = document.getElementById("hourInput");
        var minutesInput  = document.getElementById("minutesInput");
        var hourInput24     = document.getElementById("hourInput24");
        var minutesInput24  = document.getElementById("minutesInput24");
        var gpsMetric     = document.getElementById("gpsMetric");
        var autoDashCam   = document.getElementById("autoDashCam");
        var walkieTalkie  = document.getElementById("walkieTalkie");
        var bicycleTurn   = document.getElementById("bicycleTurn");
        var turnSignalDuration= document.getElementById("turnSignalDuration");

    //PassCode Handler
        passCodeBlockBTN.onclick=()=>{
            var server = new XMLHttpRequest(); 
            var code = passCodeBlockText.value;
            var confirmation;

            server.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    confirmation = this.responseText;
                
                }
            }

            server.open("PUT","AUTH_DEVICE_CODE_101?VALUE="+code, false);
            server.send();

            if(confirmation == '1'){
                alert("PASS");
            }else if(confirmation == '555'){
                var opt = confirm("YOU HAVE NOT SIGNED THE CERTIFICATE OF AUTHENTICATION.\nWould you like to that Now?");
                
                if(opt){
                    passCodeBlock.hidden = true;
                    certificateBlock.hidden = false;
                    certificateText.value = "SAMPLE CONTENT -- LEGAL WILL COME FROM SERVER FOR SECURITY.\nZAIRE HELMETS\nCRYSTAL ICE";
                }

            }else{
                alert("WRONG")
            }
        }

    //CERTIFICATE handler
    var certificateCheckbox = document.getElementById("certificateCheckbox");
    var certificateButton = document.getElementById("certificateButton");
    var certificateText = document.getElementById("certificateText");
    var certificateInitialText = document.getElementById("certificateInitialText");
    var checked = false;
    certificateCheckbox.value = checked;

    certificateCheckbox.onchange=()=>{
        checked = !checked;
        certificateCheckbox.value = checked;
    }

    certificateButton.onclick=()=>{ 
        var server = new XMLHttpRequest();
        var certificate = "hello world";
        var confirmation;
        server.onreadystatechange = function() {

                if (this.readyState == 4 && this.status == 200) {
                    confirmation = this.responseText;
                }
        }

        if(checked && certificateInitialText.value.length == 2 && (certificateInitialText.value[0] != ' ' && certificateInitialText.value[1] != ' ') ){
            server.open("PUT", "SIGN_OUT_CERTIFICATE_101?VALUE="+certificate, false);
            server.send();
            if(confirmation == '1'){
                certificateBlock.hidden = true;
                ui.hidden = false;
                _getCurrentSettings();
            }
        }else{
            alert("CERTIFICATE NOT SIGNED");
        }
    }


    //Data rec from helmet 
        //ex: MOTORCYCLE+ZAIRE+12+12-22-2000+12-30-AM+0+0+1+911+2+1+3+1+0
        //ex: BICYCLE+ZAIRE+12+12-22-2000+12-30-AM+0+0+1+911+2+1+3+1+1
        var settingsArray = [];
       
        var deviceType; // Motorcycle or Bicycle
        var currentDeviceName;
        var currentTimeFormat;
        var currentDate;
        var currentTime;
        var currentGpsMetric;
        var currentDashCam;
        var currentWalkie;
        var currentEmNum;
        var currentRmtUp;
        var currentRmtRt;
        var currentRmtLt;
        var currentBicycleTurn; //Bicycle Only
        var currentBlindSpot; 

        const _getCurrentSettings=()=>{

            var server = new XMLHttpRequest(); 
            var serverSettings = "";
            var arrayHolder = [];

            server.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    serverSettings = this.responseText;
                // update some HTML data
                }
            }

            server.open("PUT", "GET_CURRENT_SETTINGS", false);
            server.send();
            const settings = serverSettings.split('+');

            for(let i = 0; i < settings.length; i++){
                settingsArray.push(settings[i]);
            }

            //set remote
            const _setRemote=(id)=>{
                if(id == 0){
                    return "CAPTURE";
                }else if(id == 1){
                    return "DASHCAM";
                }else{
                    return "BACKLIGHT";
                }
            }

            //set settings
            deviceType = settingsArray[0];
            currentDeviceName = settingsArray[1];
            currentTimeFormat = settingsArray[2];
            currentDate = settingsArray[3];
            currentTime = settingsArray[4];
            currentGpsMetric = settingsArray[5];
            currentDashCam = settingsArray[6];
            currentWalkie = settingsArray[7];
            currentEmNum = settingsArray[8];
            currentRmtUp = _setRemote(settingsArray[9]);
            currentRmtRt = _setRemote(settingsArray[10]);
            currentRmtLt = _setRemote(settingsArray[11]);
            currentBicycleTurn = settingsArray[12];
            currentBicycleTurnDuration = settingsArray[13];
            currentBlindSpot = settingsArray[14];

            helmetType.innerText = `Type: ${deviceType}`;
            deviceNameText.innerText = currentDeviceName;
            dateTimeText.innerText = `${currentDate} ${currentTime}`;
            gpsMetricText.innerText = currentGpsMetric?"MPH":"KMH";
            autoDashCamText.innerText = currentDashCam?"YES":"NO";
            walkieTalkieText.innerText = currentWalkie?"YES":"NO"; 
            emergencyNumberText.innerText = `${currentEmNum == 911? currentEmNum + "(USA)" : currentEmNum}`;
            remoteUpText.innerText = currentRmtUp;
            remoteRtText.innerText = currentRmtRt;
            remoteLtText.innerText = currentRmtRt;
            bicycleTurnSignText.innerText = currentBicycleTurn? `YES - ${currentBicycleTurnDuration}`:"NO";
            blindSpotMonitoringText.innerText = currentBlindSpot? "YES":"NO";

            //checking Type
            deviceType == "MOTORCYCLE" ? bicycleTurnBlock.hidden = true: bicycleTurnBlock.hidden = false;
        }

    //Setup
    const _setUp=()=>{
        passCodeBlockHidden = false;
        passCodeBlock.hidden = passCodeBlockHidden;
        certificateBlock.hidden = certificateBlockHidden;
        ui.hidden = uiHidden;

    }
    

    //SAVE SETTINGS
        var saveSettingsYES = document.getElementById("saveSettingsYES");
        var saveSettingsNO  = document.getElementById("saveSettingsNO");

        saveSettingsNO.onclick=()=>_getCurrentSettings();

        saveSettingsYES.onclick=()=>{
            var server = new XMLHttpRequest(); 
            var saveConfirmation;

            server.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    message = this.responseText;
                // update some HTML data
                }
            }
            
            server.open("PUT", "BUTTON_0", false);
            server.send();
            alert(message);
        }


    //RESET SERVER PASSWORD
        var resetServerPasswordBTN = document.getElementById("resetServerPasswordBTN");
        var resetServerPasswordUI  = document.getElementById("resetServerPasswordUI");
        var resetServerPasswordTextarea = document.getElementById("resetServerPasswordTextarea");
        var resetServerPasswordSaveBTN = document.getElementById("resetServerPasswordSaveBTN");
        var resetServerPasswordCancelBTN = document.getElementById("resetServerPasswordCancelBTN");


        resetServerPasswordCancelBTN.onclick=()=>{
            resetServerPasswordUI.hidden = true;
            ui.hidden = false;
        }

        resetServerPasswordBTN.onclick=()=>{
            var btnPressed = confirm("Would you like to reset your HELMET's SERVER's PassWord?");

            if(btnPressed){
                btnPressed = confirm("RESETTING THIS PASSWORD WILL CHANGE THE WIFI PASSWORD YOU USE TO ENTER THE HELMET's SETTING, CONTINUE?");
                if(btnPressed){
                    ui.hidden = true;
                    resetServerPasswordUI.hidden = false;
                }
            }
        }

        resetServerPasswordSaveBTN.onclick=()=>{
            var btnPressed = confirm("ARE YOU READY TO RESET YOUR HELMET's SERVER (WIFI) PASSWORD?");
            
            if(btnPressed){
                if(resetServerPasswordTextarea.value == ""){
                    btnPressed = confirm("YOU DID NOT ENTER A PASSCODE, THIS IS NOT RECOMMENDED. \nSTILL PROCEED?");
                    if(btnPressed){
                        ResetServerPassword(resetServerPasswordTextarea.value);
                    }
                }else{
                    ResetServerPassword(resetServerPasswordTextarea.value);
                }
            }
        }

        const ResetServerPassword=(password)=>{
            //send signal to reset server password with the 'password' as string
            //receive back the ok and confirmation that the password as been reset.
            alert("You will need to forget the device, and reconnect.")
            password == ""? alert("You are all set to go.\nRIDE SAFE - CRYSTAL ICE") : alert(`Your new password: ${password} is set to go.\n RIDE SAFE!! - CRYSTAL ICE`);

        }


    //RESET HELMET PASSCODE
        var resetHelmetPassCodeBTN = document.getElementById("resetHelmetPassCodeBTN");
        var resetHelmetPassCodeUI = document.getElementById("resetHelmetPassCodeUI");
        var resetHelmetPassCodeTextarea = document.getElementById("resetHelmetPassCodeTextarea");
        var resetHelmetPassCodeSaveBTN = document.getElementById("resetHelmetPassCodeSaveBTN");
        var resetHelmetPassCodeCancelBTN = document.getElementById("resetHelmetPassCodeCancelBTN");


        resetHelmetPassCodeCancelBTN.onclick=()=>{
            ui.hidden = false;
            resetHelmetPassCodeUI.hidden = true;
          
        }

        resetHelmetPassCodeBTN.onclick=()=>{
            var btnPressed = confirm("Would you like to reset your HELMET's PassCode?");

            if(btnPressed){
                ui.hidden = true;
                resetHelmetPassCodeUI.hidden = false;
            }
        }

        resetHelmetPassCodeSaveBTN.onclick=()=>{
            var btnPressed = confirm("Ready to change your HELMET's PassCode?");
            var value = resetHelmetPassCodeTextarea.value;
            if(btnPressed){
                if(value > 99999){

                    ResetHelmetPassCode(value);
                }else{
                    alert("Please enter 6 digits.\n'000000' is not accepted for security reasons");
                }
          
            }


        }

        
        const ResetHelmetPassCode=(passcode)=>{

            //send signal to reset helmet passcode with the 'passcode' as string
            //receive back the ok and confirmation that the passcode as been reset.
            alert(`Your passcode: ${passcode} has been set.\nPlease hold down the blue button on your helmet.\nPress OK or Close.\nLet go after the beep`);
            setTimeout(() => {
                location.reload();
            }, 1500);


        }
        
    //RESET TO FACTORY
        var body = document.getElementById("bb");
        var resetFactoryUI = document.getElementById("resetFactoryUI");
        var resetToFactoryBTN = document.getElementById("resetToFactoryBTN");
        var resetToFactoryYesBTN = document.getElementById("resetToFactoryYesBTN");
        var resetToFactoryCancelBTN = document.getElementById("resetToFactoryCancelBTN");


        resetToFactoryCancelBTN.onclick=()=>{
            ui.hidden = false;
            bb.style.backgroundColor = "white";
            bb.style.Color = "black";
            resetFactoryUI.hidden = true;
        }

        resetToFactoryBTN.onclick=()=>{
            var btnPressed = confirm("WOULD YOU LIKE TO FACTORY RESET THE WHOLE HELMET?\nReset Settings\nReset Server PassWord\nReset Helmet PassCode\nReset CERTIFICATE.\nAre you sure?");

            if(btnPressed){
                btnPressed = confirm("THIS ACTION CAN NOT BE REVERTED.\nAre YOU SURE?");
                if(btnPressed){
                    ui.hidden = true;
                    bb.style.backgroundColor = "red"
                    bb.style.Color = "white"
                    resetFactoryUI.hidden = false;
                }
            }
        }

        resetToFactoryYesBTN.onclick=()=>{
            var btnPressed = confirm("THIS CAN NOT BE REVERSED.\nSERVER PASSWORD WILL GO BACK TO FACTORY.\nHELMET PASSCODE WILL GO BACK TO FACTORY.\nCERTIFICATE WILL GO BACK TO FACTORY.\nPROCEED?");
            btnPressed?ResetToFactory():null;
        }

        const ResetToFactory=()=>{
            //send signal to factory reset
            //receive confirmation
            alert("YOUR HELMET HAS BEEN FACTORY RESET");
            location.reload();
        }


    //Input format handlers

    certificateInitialText.addEventListener("input",function(){
        this.value = this.value.replace(/[^A-Z]/g, '');
    
    })

        passCodeBlockText.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        })

        hourFormat.onchange = () => {
            if (hourFormat.value == "12HR") {
                _12hrDiv.style.display = "flex"; // Make 12hrDiv visible
                _24hrDiv.style.display = "none"; // Hide 24hrDiv
            } else {
                _12hrDiv.style.display = "none"; // Hide 12hrDiv
                _24hrDiv.style.display = "flex"; // Make 24hrDiv visible
            }
        };

        bicycleTurn.onchange = () => {
            if (bicycleTurn.value == "YES") {
                turnSignalDuration.hidden = false; // Make 12hrDiv visible
            } else {
                turnSignalDuration.hidden =true; // Hide 12hrDiv
            }
        };

        monthInput.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        //ensure we only get 12 months
            if(this.value > 12){ 
                this.value = null;
            }
        });


        dateInput.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        //ensure we only get 31 days
            if(this.value > 31){
                this.value = null;
            }
        });

        yearInput.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
            
        });

        hourInput.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        // ensure we only get 24hr or 12
            if(this.value > 12 && hourFormat.value == "12HR"){
                this.value = 12;
            }else if(this.value > 23){
                this.value = null;
            }
        });

        minutesInput.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        //ensure we only get 59 minutes
            if(this.value > 59){
                this.value = null;
            }
        });

        hourInput24.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        // ensure we only get 24hr or 12
            if(this.value > 23 && hourFormat.value == "24HR"){
                this.value = 12;
            }
        });

        minutesInput24.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        //ensure we only get 59 minutes
            if(this.value > 59){
                this.value = null;
            }
        });

        phoneTextArea.addEventListener("input", function() {
        // Replace any non-numeric characters
            this.value = this.value.replace(/[^0-9]/g, '');
        });


        window.onload=()=>_setUp();

    </script>
</body>
</html>



)=====";
