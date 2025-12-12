// --------------------------------------------
// USER + SYSTEM SETTINGS (stubbed for now)
// In real firmware these will be injected/overwritten by C.
// --------------------------------------------



// For demo: store passcode & recovery in JS
var deviceSecurity = {
  passcode: null, // "123456"
  recovery_number: null // "0".."9"
};




// --------------------------------------------
// APPLY LANGUAGE TO DOM
// --------------------------------------------
function applyLanguage(langCode) {
  const lang = i18n[langCode] ? langCode : "en";
  userSettings.device_lang = lang;

  const dict = i18n[lang];

  // Update lang + dir on <html>
  document.documentElement.lang = lang === "cn" ? "zh-CN" : lang;
  if (lang === "ar") {
    document.documentElement.dir = "rtl";
  } else {
    document.documentElement.dir = "ltr";
  }

  // Text nodes
  document.querySelectorAll("[data-i18n]").forEach((el) => {
    const key = el.getAttribute("data-i18n");
    if (dict[key]) {
      el.textContent = dict[key];
    }
  });

  // Placeholders
  document.querySelectorAll("[data-i18n-placeholder]").forEach((el) => {
    const key = el.getAttribute("data-i18n-placeholder");
    if (dict[key]) {
      el.placeholder = dict[key];
    }
  });

  // Language-continue button label (it may be also in dict)
  const langContinueBtn = document.getElementById("language-continue");
  if (langContinueBtn && dict.btn_lang_continue) {
    // If currently visible, override its text
    if (!langContinueBtn.classList.contains("hidden")) {
      langContinueBtn.textContent = dict.btn_lang_continue;
    }
  }
}

// --------------------------------------------
// DOM HOOKS
// --------------------------------------------
const homeRoot       = document.getElementById("home-root");
const home_start_btn = document.getElementById("home-start-btn");

const languageSelect  = document.getElementById("language-select");
const languageOptions = document.querySelectorAll(".language-option");
const langContinueBtn = document.getElementById("language-continue");

const wizardMainTitle = document.querySelector(".wizard-main-title");

// Wizard steps
const nameCard        = document.getElementById("name-card");
const nameInput       = document.getElementById("user-name-input");
const nameError       = document.getElementById("name-error");
const nameContinueBtn = document.getElementById("name-continue");

const deviceNameCard     = document.getElementById("device-name-card");
const deviceNameInput    = document.getElementById("device-name-input");
const deviceNameError    = document.getElementById("device-name-error");
const deviceNameContinue = document.getElementById("device-name-continue");

const unitsCard        = document.getElementById("units-card");
const unitOptions      = document.querySelectorAll(".unit-option");
const unitsError       = document.getElementById("units-error");
const unitsContinueBtn = document.getElementById("units-continue");

const themeCard        = document.getElementById("theme-card");
const themeOptions     = document.querySelectorAll(".theme-option");
const themeError       = document.getElementById("theme-error");
const themeContinueBtn = document.getElementById("theme-continue");

const newPasscodeCard    = document.getElementById("new-passcode-card");
const newPasscodeInput   = document.getElementById("new-passcode-input");
const newPasscodeConfirm = document.getElementById(
  "new-passcode-confirm-input"
);
const newPasscodeError   = document.getElementById("new-passcode-error");
const newPasscodeContinue = document.getElementById(
  "new-passcode-continue"
);

const recoveryCard        = document.getElementById('recovery-card');
const recoveryDigits      = document.querySelectorAll('.recovery-digit');
const recoveryError       = document.getElementById('recovery-error');
const recoveryContinueBtn = document.getElementById('recovery-continue');
const savingCard          = document.getElementById('saving-card');


// 👇 NEW: Back buttons
const nameBackBtn        = document.getElementById("name-back");
const deviceNameBackBtn  = document.getElementById("device-name-back");
const unitsBackBtn       = document.getElementById("units-back");
const themeBackBtn       = document.getElementById("theme-back");
const newPasscodeBackBtn = document.getElementById("new-passcode-back");
const recoveryBackBtn    = document.getElementById("recovery-back");

// Login
const passcodeCard   = document.getElementById("passcode-card");
const passcodeInput  = document.getElementById("passcode-input");
const passcodeError  = document.getElementById("passcode-error");
const passcodeButton = document.getElementById("passcode-button");

// Welcome elements
const welcomeTitle = document.querySelector(".welcome-title");
const enterBtn     = document.querySelector(".enter-btn");
const logoElement  = document.querySelector(".logo");
const iLetter      = document.querySelector(".logo .i");

// --------------------------------------------
// WELCOME MULTI-LANGUAGE CYCLE
// --------------------------------------------
let welcomeCycleInterval = null;

function startWelcomeCycle() {
  if (!welcomeTitle || !enterBtn) return;

  const cycle = [
    { text: "WELCOME", enter: "ENTER" },
    { text: "BIENVENIDO", enter: "ENTRAR" }, // ES
    { text: "BIENVENUE", enter: "ENTRER" }, // FR
    { text: "أهلاً وسهلاً", enter: "استمرار" }, // AR
    { text: "欢迎", enter: "进入" }, // CN
    { text: "स्वागत है", enter: "प्रवेश करें" }, // HI
    { text: "ようこそ", enter: "入る" }, // JP
    { text: "환영합니다", enter: "입장" }, // KR
    { text: "BEM-VINDO", enter: "ENTRAR" }, // PT
    { text: "Добро пожаловать", enter: "Войти" } // RU
  ];

  let index = 0;

  welcomeTitle.innerText = cycle[index].text;
  enterBtn.innerText     = cycle[index].enter;
  welcomeTitle.style.opacity = "1";
  enterBtn.classList.add("show");

  welcomeCycleInterval = setInterval(() => {
    index = (index + 1) % cycle.length;

    // Fade only welcome text (keep button visible)
    welcomeTitle.style.opacity = "0";

    setTimeout(() => {
      welcomeTitle.innerText = cycle[index].text;
      enterBtn.innerText     = cycle[index].enter;
      welcomeTitle.style.opacity = "1";
    }, 400);
  }, 2200);
}

function stopWelcomeCycle() {
  if (welcomeCycleInterval) {
    clearInterval(welcomeCycleInterval);
    welcomeCycleInterval = null;
  }
}

// --------------------------------------------
// ZAIRE logo intro animation (first_boot only)
// --------------------------------------------
window.addEventListener("load", function () {
  const letters = Array.from(document.querySelectorAll(".logo .letter"));

  if (systemSettings.first_boot) {
    if (!letters.length || !welcomeTitle || !enterBtn || !iLetter) return;

    const letterDuration = 75; // ms
    const letterGap = 95; // ms

    letters.forEach((letter, index) => {
      setTimeout(() => {
        letter.classList.add("letter--show");

        if (index === letters.length - 1) {
          setTimeout(() => {
            welcomeTitle.classList.add("show");
            startWelcomeCycle();

            setTimeout(() => {
              enterBtn.classList.add("show");

              setTimeout(() => {
                iLetter.classList.add("i-highlight");
              }, 200);
            }, 200);
          }, letterDuration - 150);
        }
      }, index * (letterDuration + letterGap));
    });
  } else {
    // Non-first_boot: show static logo and login card, no splash animation
    letters.forEach((letter) => letter.classList.add("letter--show"));
    if (iLetter) iLetter.classList.add("i-highlight");
    if (welcomeTitle) welcomeTitle.classList.add("hidden");
    if (enterBtn) enterBtn.classList.add("hidden");
    if (languageSelect) languageSelect.classList.add("hidden");

    applyLanguage(userSettings.device_lang || "en");

    if (passcodeCard) {
      passcodeCard.classList.remove("hidden");
      if (passcodeInput) passcodeInput.focus();
    }
  }
});

// --------------------------------------------
// ENTER handler: for first_boot only
// --------------------------------------------
if (home_start_btn) {
  home_start_btn.addEventListener("click", () => {
    if (!systemSettings.first_boot) {
      // On real device we'd probably never get here in non-first_boot
      return;
    }

    if (logoElement) {
      logoElement.classList.add("shift-up");
    }

    if (welcomeTitle) {
      stopWelcomeCycle();
      welcomeTitle.classList.remove("show");
      welcomeTitle.style.opacity = "0";
    }

    home_start_btn.classList.remove("show");
    home_start_btn.style.opacity = "0";
    home_start_btn.style.pointerEvents = "none";

    if (languageSelect) {
      languageSelect.classList.remove("hidden");
    }
  });
}

// --------------------------------------------
// LANGUAGE SELECTION (step 0)
// --------------------------------------------
let selectedLang = "en";

languageOptions.forEach((option) => {
  option.addEventListener("click", () => {
    languageOptions.forEach((o) => o.classList.remove("selected"));
    option.classList.add("selected");

    const langCode = option.dataset.lang || "en";
    selectedLang = langCode;

    if (langContinueBtn) {
      const label = option.dataset.continueLabel || "Continue";
      langContinueBtn.textContent = label;
      langContinueBtn.classList.remove("hidden");
    }
  });
});

if (langContinueBtn) {
  langContinueBtn.addEventListener("click", () => {
    if (!selectedLang) return;

    // Apply language to wizard UI
    applyLanguage(selectedLang);

    // Hide language selector and show wizard main title + first card
    if (languageSelect) languageSelect.classList.add("hidden");
    if (wizardMainTitle) wizardMainTitle.classList.remove("hidden");

    if (nameCard) {
      nameCard.classList.remove("hidden");
      if (nameInput) nameInput.focus();
    }
  });
}

// --------------------------------------------
// FIRST-BOOT WIZARD FLOW
// --------------------------------------------

// Step 1: Name -> Device Name
if (nameContinueBtn) {
  nameContinueBtn.addEventListener("click", () => {
    if (!nameInput || !nameError || !nameCard || !deviceNameCard) return;

    const val = nameInput.value.trim();
    nameError.textContent = "";

    if (!val) {
      nameError.textContent = "Please enter a name.";
      return;
    }

    userSettings.user_name = val;

    nameCard.classList.add("hidden");
    deviceNameCard.classList.remove("hidden");

    if (deviceNameInput && !deviceNameInput.value) {
      deviceNameInput.value = userSettings.device_name || "ZAIRE VISION";
    }
    if (deviceNameInput) deviceNameInput.focus();
  });
}

// 👇 NEW: Back Name -> Language
if (nameBackBtn) {
  nameBackBtn.addEventListener("click", () => {
    if (!nameCard || !languageSelect) return;

    nameCard.classList.add("hidden");
    if (wizardMainTitle) wizardMainTitle.classList.add("hidden");
    languageSelect.classList.remove("hidden");
  });
}

// Step 2: Device Name -> Units
if (deviceNameContinue) {
  deviceNameContinue.addEventListener("click", () => {
    if (
      !deviceNameInput ||
      !deviceNameError ||
      !deviceNameCard ||
      !unitsCard
    )
      return;

    const val = deviceNameInput.value.trim();
    deviceNameError.textContent = "";

    if (!val) {
      deviceNameError.textContent = "Please enter a device name.";
      return;
    }

    userSettings.device_name = val;

    deviceNameCard.classList.add("hidden");
    unitsCard.classList.remove("hidden");
  });
}

// 👇 NEW: Back Device Name -> Name
if (deviceNameBackBtn) {
  deviceNameBackBtn.addEventListener("click", () => {
    if (!deviceNameCard || !nameCard) return;

    deviceNameCard.classList.add("hidden");
    nameCard.classList.remove("hidden");
    if (nameInput) nameInput.focus();
  });
}

// Step 3: Units -> Theme
unitOptions.forEach((btn) => {
  btn.addEventListener("click", () => {
    unitOptions.forEach((b) => b.classList.remove("selected"));
    btn.classList.add("selected");
    unitsError.textContent = "";

    const units = btn.dataset.units || "metric";
    userSettings.device_units = units;

    if (unitsContinueBtn) {
      unitsContinueBtn.classList.remove("hidden");
    }
  });
});

if (unitsContinueBtn) {
  unitsContinueBtn.addEventListener("click", () => {
    if (!unitsCard || !themeCard) return;

    const selected = Array.from(unitOptions).some((b) =>
      b.classList.contains("selected")
    );
    if (!selected) {
      unitsError.textContent = "Please select a unit system.";
      return;
    }

    unitsCard.classList.add("hidden");
    themeCard.classList.remove("hidden");
  });
}

// 👇 NEW: Back Units -> Device Name
if (unitsBackBtn) {
  unitsBackBtn.addEventListener("click", () => {
    if (!unitsCard || !deviceNameCard) return;

    unitsCard.classList.add("hidden");
    deviceNameCard.classList.remove("hidden");
    if (deviceNameInput) deviceNameInput.focus();
  });
}

// Step 4: Theme -> Create Passcode
themeOptions.forEach((opt) => {
  opt.addEventListener("click", () => {
    themeOptions.forEach((o) => o.classList.remove("selected"));
    opt.classList.add("selected");
    themeError.textContent = "";

    const theme = opt.dataset.theme || "dark";

    // 🔴 Live switch the UI theme as soon as user taps
    applyThemeMode(theme);

    if (themeContinueBtn) {
      themeContinueBtn.classList.remove("hidden");
    }
  });
});

if (themeContinueBtn) {
  themeContinueBtn.addEventListener("click", () => {
    if (!themeCard || !newPasscodeCard) return;

    const selected = Array.from(themeOptions).some((o) =>
      o.classList.contains("selected")
    );
    if (!selected) {
      themeError.textContent = "Please select a theme.";
      return;
    }

    themeCard.classList.add("hidden");
    newPasscodeCard.classList.remove("hidden");

    if (newPasscodeInput) newPasscodeInput.focus();
  });
}

// 👇 NEW: Back Theme -> Units
if (themeBackBtn) {
  themeBackBtn.addEventListener("click", () => {
    if (!themeCard || !unitsCard) return;

    themeCard.classList.add("hidden");
    unitsCard.classList.remove("hidden");
  });
}

// Step 5: Create + Confirm Passcode -> Recovery
function setupPasscodeInputFiltering(inputElem) {
  if (!inputElem) return;
  inputElem.addEventListener("input", () => {
    let val = inputElem.value;
    val = val.replace(/\D/g, "");
    if (val.length > 6) val = val.slice(0, 6);
    inputElem.value = val;
  });
}

setupPasscodeInputFiltering(newPasscodeInput);
setupPasscodeInputFiltering(newPasscodeConfirm);
setupPasscodeInputFiltering(passcodeInput);

function validateNewPasscode() {
  if (!newPasscodeInput || !newPasscodeConfirm || !newPasscodeError)
    return false;

  const code = newPasscodeInput.value.trim();
  const codeConf = newPasscodeConfirm.value.trim();
  newPasscodeError.textContent = "";

  if (code.length !== 6 || codeConf.length !== 6) {
    newPasscodeError.textContent =
      "Passcode and confirmation must be 6 digits.";
    return false;
  }

  if (code !== codeConf) {
    newPasscodeError.textContent = "Passcodes do not match.";
    return false;
  }

  deviceSecurity.passcode = code;
  return true;
}

if (newPasscodeContinue) {
  newPasscodeContinue.addEventListener("click", () => {
    if (!newPasscodeCard || !recoveryCard) return;

    if (!validateNewPasscode()) return;

    newPasscodeCard.classList.add("hidden");
    recoveryCard.classList.remove("hidden");
  });
}

// 👇 NEW: Back Passcode -> Theme
if (newPasscodeBackBtn) {
  newPasscodeBackBtn.addEventListener("click", () => {
    if (!newPasscodeCard || !themeCard) return;

    newPasscodeCard.classList.add("hidden");
    themeCard.classList.remove("hidden");
  });
}

// Step 6: Recovery Number -> Finish
recoveryDigits.forEach((btn) => {
  btn.addEventListener("click", () => {
    recoveryDigits.forEach((b) => b.classList.remove("selected"));
    btn.classList.add("selected");
    recoveryError.textContent = "";

    const digit = btn.dataset.digit;
    deviceSecurity.recovery_number = digit;
  });
});

if (recoveryContinueBtn) {
    recoveryContinueBtn.addEventListener('click', () => {
        if (!recoveryError) return;

        if (deviceSecurity.recovery_number === null) {
            recoveryError.textContent = 'Please select a recovery number.';
            return;
        }

        // In real firmware:
        //  - Persist userSettings + deviceSecurity (NVS / flash)
        //  - Set first_boot = false on the device side
        console.log('Setup complete!');
        console.log('User settings:', userSettings);
        console.log('Security:', deviceSecurity);

        systemSettings.first_boot = false;   // local JS view
        goToDashboard();                     // jump to /wwww/homeScreen.html
    });
}




// 👇 NEW: Back Recovery -> Passcode
if (recoveryBackBtn) {
  recoveryBackBtn.addEventListener("click", () => {
    if (!recoveryCard || !newPasscodeCard) return;

    recoveryCard.classList.add("hidden");
    newPasscodeCard.classList.remove("hidden");
  });
}

// --------------------------------------------
// LOGIN PASSCODE LOGIC (non-first_boot)
// --------------------------------------------
function validatePasscode() {
    if (!passcodeInput || !passcodeError) return;

    const code = passcodeInput.value.trim();
    passcodeError.textContent = '';

    if (code.length !== 6) {
        passcodeError.textContent = 'Passcode must be 6 digits.';
        return;
    }

    // In real firmware: compare with stored passcode securely.
    console.log('Passcode entered (stub):', code);

    // For now, any 6-digit passcode is accepted in the UI demo
    goToDashboard();
}


if (passcodeButton) {
    passcodeButton.addEventListener('click', () => {
        validatePasscode();
    });
}

if (passcodeInput) {
    passcodeInput.addEventListener('keyup', (e) => {
        if (e.key === 'Enter') validatePasscode();
    });
}


// --------------------------------------------
// APPLY VISUAL THEME (DARK / LIGHT)
// --------------------------------------------
function applyThemeMode(mode) {
  const body = document.body;
  if (!body) return;

  // Fallback to dark if invalid
  const theme = (mode === "light") ? "light" : "dark";

  body.classList.remove("theme-dark-mode", "theme-light-mode");
  body.classList.add(theme === "light" ? "theme-light-mode" : "theme-dark-mode");

  userSettings.device_color_theme = theme;
}


// --------------------------------------------
// MAIN DASHBOARD NAVIGATION
// --------------------------------------------
function goToDashboard() {
    const lang = (userSettings && userSettings.device_lang) ? userSettings.device_lang : "en";

    // Single dashboard file under /wwww now.
    // We pass lang as a query param so homeScreen can load lang.json later.
    const target = "/www/homeScreen.html";
    window.location.href = target;
}
