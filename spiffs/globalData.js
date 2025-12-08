// --------------------------------------------
// USER + SYSTEM SETTINGS (stubbed for now)
// In real firmware these will be injected/overwritten by C.
// --------------------------------------------

//<-------------- USER SETTINGS--------------->//
var userSettings = {
  user_name: "USER",
  device_name: "ZAIRE VISION",
  device_lang: "en", // "en", "es", "fr", "cn", "hi", "jp", "kr", "pt", "ru", "ar"
  device_units: "metric", // "metric" or "imperial"
  device_color_theme: "dark", // "dark" or "light"
  device_auto_record: "0",
  device_mute_record_audio: "0",
  device_lower_bt_volume_on_walkie: "1",
  device_auto_bt_enable_on_powerup: "1"
};
//<--------------------- END --------------------->//

//<-------------- SYSTEM SETTINGS ------------->//
var systemSettings = {
  first_boot: false, // set to true/false based on real device state
  firmware_version: "v1.0.0",
  hardware_version: "v1.0.0",
  build_date: "2025-12-14",
  build_time: "12:00:00"
};
//<--------------------- END --------------------->//
