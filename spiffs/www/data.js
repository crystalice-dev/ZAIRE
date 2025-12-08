// -----------------------
// ZAIRE VISION UI STATE
// -----------------------
const ZState = {
  userName: "ZAIRE Rider",
  avatarInitials: "ZR",

  // Units
  speedUnits: "mph", // or "km/h"

  // Bluetooth
  btConnected: true,
  btDeviceName: "Yann’s Phone",
  btAutoConnect: true,
  btAudioActive: true,

  // Photos
  photosCount: 12,
  photosMax: 30,
  photosLastTime: "14:32",

  // Top stats (session)
  topSpeed: 28.4, // mph
  topHeight: 212, // meters
  topAccel: 4.7,  // m/s²

  // Walkie peers (max 8) — 3 fake connections
  walkiePeers: [
    {
      id: "A1",
      name: "Helmet #2",
      lastComm: "14:21",
      lastPosition: "Trailhead A",
      audioMuted: false,
      micMuted: false,
    },
    {
      id: "B7",
      name: "Helmet #3",
      lastComm: "14:18",
      lastPosition: "Lift 3 base",
      audioMuted: false,
      micMuted: true,
    },
    {
      id: "C4",
      name: "Helmet #4",
      lastComm: "14:10",
      lastPosition: "Ridge lookout",
      audioMuted: true,
      micMuted: false,
    },
  ],
};

// -----------------------
// RENDER HELPERS
// -----------------------

function renderDashboard() {
  // Header
  const userEl = document.getElementById("dash-username");
  const avatarEl = document.getElementById("dash-avatar");
  if (userEl) userEl.textContent = ZState.userName;
  if (avatarEl) {
    const span = avatarEl.querySelector("span");
    if (span) span.textContent = ZState.avatarInitials;
  }

  // Bluetooth hero card
  const btStateEl = document.getElementById("bt-state");
  const btDeviceNameEl = document.getElementById("bt-device-name");
  const btAutoEl = document.getElementById("bt-autoconnect");
  const btAudioEl = document.getElementById("bt-audio");
  const btPill = document.getElementById("bt-device-pill");
  const btIconBtn = document.getElementById("bt-icon-btn");

  if (btStateEl) {
    btStateEl.textContent = ZState.btConnected ? "Connected" : "Disconnected";
    btStateEl.style.color = ZState.btConnected ? "#22c55e" : "#f97373";
  }
  if (btDeviceNameEl) {
    btDeviceNameEl.textContent = ZState.btConnected
      ? ZState.btDeviceName
      : "No device";
  }
  if (btAutoEl) btAutoEl.textContent = ZState.btAutoConnect ? "ON" : "OFF";
  if (btAudioEl)
    btAudioEl.textContent = ZState.btAudioActive
      ? "Active"
      : ZState.btConnected
      ? "Available"
      : "Idle";

  if (btPill) {
    btPill.style.backgroundColor = ZState.btConnected
      ? "rgba(34,197,94,0.16)"
      : "rgba(148,163,184,0.16)";
    btPill.style.borderColor = ZState.btConnected
      ? "rgba(34,197,94,0.75)"
      : "rgba(148,163,184,0.75)";
  }

  if (btIconBtn) {
    btIconBtn.style.borderColor = ZState.btConnected
      ? "#22c55e"
      : "#1f2937";
  }

  // Photos card
  const photosCountEl = document.getElementById("photos-count");
  const photosMaxEl = document.getElementById("photos-max");
  const photosLastEl = document.getElementById("photos-last");
  if (photosCountEl) photosCountEl.textContent = ZState.photosCount.toString();
  if (photosMaxEl) photosMaxEl.textContent = ZState.photosMax.toString();
  if (photosLastEl) photosLastEl.textContent = ZState.photosLastTime;

  // Top speed
  const topSpeedEl = document.getElementById("top-speed");
  const topSpeedUnitEl = document.getElementById("top-speed-unit");
  if (topSpeedEl) topSpeedEl.textContent = ZState.topSpeed.toFixed(1);
  if (topSpeedUnitEl) topSpeedUnitEl.textContent = ZState.speedUnits;

  // Top height
  const topHeightEl = document.getElementById("top-height");
  if (topHeightEl) topHeightEl.textContent = ZState.topHeight.toFixed(0);

  // Top acceleration
  const topAccelEl = document.getElementById("top-accel");
  if (topAccelEl) topAccelEl.textContent = ZState.topAccel.toFixed(1);

  // Walkie peers count (dashboard card)
  const walkiePeersEl = document.getElementById("walkie-peers");
  if (walkiePeersEl) {
    const count = Array.isArray(ZState.walkiePeers)
      ? ZState.walkiePeers.length
      : 0;
    walkiePeersEl.textContent = count.toString();
  }
}

// -----------------------
// DEMO TICK (optional)
// -----------------------

function tickDemo() {
  // Fake a tiny bit of life for demo:

  // Simulate photo count creeping up
  if (Math.random() < 0.2 && ZState.photosCount < ZState.photosMax) {
    ZState.photosCount += 1;
    ZState.photosLastTime = new Date().toTimeString().slice(0, 5);
  }

  // Simulate minor top stat changes
  if (Math.random() < 0.15) {
    ZState.topSpeed += 0.2;
  }
  if (Math.random() < 0.15) {
    ZState.topHeight += 1;
  }
  if (Math.random() < 0.15) {
    ZState.topAccel += 0.05;
  }

  renderDashboard();
}

// -----------------------
// INIT (dashboard metrics)
// -----------------------

document.addEventListener("DOMContentLoaded", () => {
  renderDashboard();

  // For live demo only. On device, remove this
  // and just call renderDashboard() when new data arrives.
  setInterval(tickDemo, 1500);
});

// -----------------------
// VIEW SWITCHING, PHOTOS, WALKIE
// (moved from inline <script> in homeScreen.html)
// -----------------------

document.addEventListener("DOMContentLoaded", () => {
  const dashboardView = document.getElementById("dashboard-view");

  const navDashboard = document.getElementById("nav-dashboard");
  const navPhotos = document.getElementById("nav-photos");
  const navWalkie = document.getElementById("nav-walkie");
  const navSettings = document.getElementById("nav-settings");

  const walkieView = document.getElementById("walkie-view");
  const walkieList = document.getElementById("walkie-list");
  const walkieTotalLabel = document.getElementById("walkie-total-label");

  const settingsView = document.getElementById("settings-view");



  const photosView = document.getElementById("photos-view");
  const photosGrid = document.getElementById("photos-grid");
  const photosCard = document.getElementById("photos-card");
  const photoOverlay = document.getElementById("photo-overlay");
  const photoOverlayBackdrop = document.getElementById("photo-overlay-backdrop");
  const photoLarge = document.getElementById("photo-large");

  const walkieOverlay = document.getElementById("walkie-overlay");
  const walkieOverlayBackdrop = document.getElementById("walkie-overlay-backdrop");
  const walkieOverlayName = document.getElementById("walkie-overlay-name");
  const walkieOverlayId = document.getElementById("walkie-overlay-id");
  const walkieOverlayStatus = document.getElementById("walkie-overlay-status");
  const walkieMuteAudioBtn = document.getElementById("walkie-mute-audio-btn");
  const walkieMuteMicBtn = document.getElementById("walkie-mute-mic-btn");
  const walkieMuteAllBtn = document.getElementById("walkie-mute-all-btn");

  let currentOverlayPeerId = null;

  // --- helper to switch nav active state ---
  function setActiveNav(button) {
    document.querySelectorAll(".dash-nav .nav-item")
      .forEach((btn) => btn.classList.remove("nav-item--active"));
    if (button) button.classList.add("nav-item--active");
  }

  // --- show/hide views ---
  function showDashboard() {
    dashboardView.classList.remove("hidden");
    photosView.classList.add("hidden");
    walkieView.classList.add("hidden");
    settingsView.classList.add("hidden");
    setActiveNav(navDashboard);
  }

  function showPhotos() {
    dashboardView.classList.add("hidden");
    photosView.classList.remove("hidden");
    walkieView.classList.add("hidden");
    settingsView.classList.add("hidden");
    setActiveNav(navPhotos);
  }

  function showWalkie() {
    dashboardView.classList.add("hidden");
    photosView.classList.add("hidden");
    walkieView.classList.remove("hidden");
    settingsView.classList.add("hidden");
    setActiveNav(navWalkie);
  }

   function showSettings() {
    dashboardView.classList.add("hidden");
    photosView.classList.add("hidden");
    walkieView.classList.add("hidden");
    settingsView.classList.remove("hidden");
    setActiveNav(navSettings);
  }

  // --- click handlers to switch to photos / dashboard / walkie views ---
  if (photosCard) {
    photosCard.style.cursor = "pointer";
    photosCard.addEventListener("click", showPhotos);
  }
  if (navPhotos) {
    navPhotos.addEventListener("click", showPhotos);
  }
  if (navDashboard) {
    navDashboard.addEventListener("click", showDashboard);
  }
  if (navWalkie) {
    navWalkie.addEventListener("click", showWalkie);
  }

  if(navSettings) {
    navSettings.addEventListener("click", showSettings);
  }

  // -----------------------------
  // PHOTOS: build fake thumbnails
  // -----------------------------
  const totalPhotos =
    window.ZState && typeof ZState.photosCount === "number"
      ? ZState.photosCount
      : Math.floor(Math.random() * 15) + 8; // 8–22 photos

  const totalLabel = document.getElementById("photos-total-label");
  if (totalLabel) totalLabel.textContent = totalPhotos.toString();

  const dashPhotosCount = document.getElementById("photos-count");
  if (dashPhotosCount) dashPhotosCount.textContent = totalPhotos.toString();

  for (let i = 0; i < totalPhotos; i++) {
    const thumb = document.createElement("div");
    thumb.className = "photo-thumb";
    thumb.dataset.index = i.toString();
    thumb.style.backgroundImage = `linear-gradient(135deg,
      rgba(255,255,255,0.06),
      rgba(0,0,0,0.9)),
      url('')`;
    photosGrid.appendChild(thumb);
  }

  photosGrid.addEventListener("click", (e) => {
    const target = e.target.closest(".photo-thumb");
    if (!target) return;

    photoLarge.style.backgroundImage = `linear-gradient(135deg,
      rgba(255,255,255,0.1),
      rgba(0,0,0,0.9))`;
    photoOverlay.classList.remove("hidden");
  });

  function closePhotoOverlay() {
    photoOverlay.classList.add("hidden");
  }

  if (photoOverlayBackdrop) {
    photoOverlayBackdrop.addEventListener("click", closePhotoOverlay);
  }
  photoOverlay.addEventListener("click", (e) => {
    if (e.target === photoOverlay) closePhotoOverlay();
  });

  // -----------------------------
  // WALKIE VIEW: build peer list
  // -----------------------------
  const peers = ZState.walkiePeers
    // window.ZState && Array.isArray(ZState.walkiePeers)
    //   ? ZState.walkiePeers
    //   : [];

  if (walkieTotalLabel) {
    walkieTotalLabel.textContent = peers.length.toString();
  }

  const dashWalkieCount = document.getElementById("walkie-peers");
  if (dashWalkieCount) {
    dashWalkieCount.textContent = peers.length.toString();
  }

  function renderWalkieList() {
    if (!walkieList) return;
    walkieList.innerHTML = "";

    peers.forEach((peer) => {
      const row = document.createElement("div");
      row.className = "walkie-peer-card";
      row.dataset.peerId = peer.id;

      const main = document.createElement("div");
      main.className = "walkie-peer-main";

      const nameEl = document.createElement("div");
      nameEl.className = "walkie-peer-name";
      nameEl.textContent = peer.name;

      const metaEl1 = document.createElement("div");
      metaEl1.className = "walkie-peer-meta";
      metaEl1.textContent = `Last comm: ${peer.lastComm}`;

      const metaEl2 = document.createElement("div");
      metaEl2.className = "walkie-peer-meta";
      metaEl2.textContent = `Last position: ${peer.lastPosition}`;

      main.appendChild(nameEl);
      main.appendChild(metaEl1);
      main.appendChild(metaEl2);

      const actions = document.createElement("div");
      actions.className = "walkie-peer-actions";

      const audioBtn = document.createElement("button");
      audioBtn.className = "walkie-peer-btn walkie-peer-btn-audio";
      audioBtn.dataset.peerId = peer.id;
      audioBtn.textContent = "🔊";
      if (peer.audioMuted) audioBtn.classList.add("is-muted");

      const micBtn = document.createElement("button");
      micBtn.className = "walkie-peer-btn walkie-peer-btn-mic";
      micBtn.dataset.peerId = peer.id;
      micBtn.textContent = "🎤";
      if (peer.micMuted) micBtn.classList.add("is-muted");

      actions.appendChild(audioBtn);
      actions.appendChild(micBtn);

      row.appendChild(main);
      row.appendChild(actions);

      walkieList.appendChild(row);
    });
  }

  renderWalkieList();

  function findPeerById(id) {
    return peers.find((p) => p.id === id) || null;
  }

  function updateOverlayStatus(peer) {
    if (!peer || !walkieOverlayStatus) return;

    const audioText = peer.audioMuted ? "Audio muted" : "Audio on";
    const micText = peer.micMuted ? "Mic muted" : "Mic on";

    walkieOverlayStatus.innerHTML = `
      <div>Last comm: ${peer.lastComm}</div>
      <div>Last position: ${peer.lastPosition}</div>
      <div>${audioText} · ${micText}</div>
    `;

    if (walkieMuteAudioBtn) {
      walkieMuteAudioBtn.classList.toggle("is-muted", peer.audioMuted);
    }
    if (walkieMuteMicBtn) {
      walkieMuteMicBtn.classList.toggle("is-muted", peer.micMuted);
    }
  }

  function openWalkieOverlay(peerId) {
    const peer = findPeerById(peerId);
    if (!peer) return;
    currentOverlayPeerId = peerId;

    if (walkieOverlayName) walkieOverlayName.textContent = peer.name;
    if (walkieOverlayId) walkieOverlayId.textContent = `ID: ${peer.id}`;
    updateOverlayStatus(peer);

    walkieOverlay.classList.remove("hidden");
  }

  function closeWalkieOverlay() {
    walkieOverlay.classList.add("hidden");
    currentOverlayPeerId = null;
  }

  // Delegate clicks in walkie list
  if (walkieList) {
    walkieList.addEventListener("click", (e) => {
      const audioBtn = e.target.closest(".walkie-peer-btn-audio");
      const micBtn = e.target.closest(".walkie-peer-btn-mic");
      const card = e.target.closest(".walkie-peer-card");

      if (audioBtn) {
        const id = audioBtn.dataset.peerId;
        const peer = findPeerById(id);
        if (!peer) return;
        peer.audioMuted = !peer.audioMuted;
        audioBtn.classList.toggle("is-muted", peer.audioMuted);
        if (currentOverlayPeerId === id) {
          updateOverlayStatus(peer);
        }
        return;
      }

      if (micBtn) {
        const id = micBtn.dataset.peerId;
        const peer = findPeerById(id);
        if (!peer) return;
        peer.micMuted = !peer.micMuted;
        micBtn.classList.toggle("is-muted", peer.micMuted);
        if (currentOverlayPeerId === id) {
          updateOverlayStatus(peer);
        }
        return;
      }

      if (card) {
        const id = card.dataset.peerId;
        openWalkieOverlay(id);
      }
    });
  }

  // Overlay buttons
  if (walkieMuteAudioBtn) {
    walkieMuteAudioBtn.addEventListener("click", () => {
      if (!currentOverlayPeerId) return;
      const peer = findPeerById(currentOverlayPeerId);
      if (!peer) return;
      peer.audioMuted = !peer.audioMuted;
      updateOverlayStatus(peer);
      renderWalkieList();
    });
  }

  if (walkieMuteMicBtn) {
    walkieMuteMicBtn.addEventListener("click", () => {
      if (!currentOverlayPeerId) return;
      const peer = findPeerById(currentOverlayPeerId);
      if (!peer) return;
      peer.micMuted = !peer.micMuted;
      updateOverlayStatus(peer);
      renderWalkieList();
    });
  }

  if (walkieMuteAllBtn) {
    walkieMuteAllBtn.addEventListener("click", () => {
      if (!currentOverlayPeerId) return;
      const peer = findPeerById(currentOverlayPeerId);
      if (!peer) return;
      peer.audioMuted = true;
      peer.micMuted = true;
      updateOverlayStatus(peer);
      renderWalkieList();
    });
  }

  // Clicking backdrop or outer overlay closes it
  if (walkieOverlayBackdrop) {
    walkieOverlayBackdrop.addEventListener("click", closeWalkieOverlay);
  }
  walkieOverlay.addEventListener("click", (e) => {
    if (e.target === walkieOverlay) {
      closeWalkieOverlay();
    }
  });
});
