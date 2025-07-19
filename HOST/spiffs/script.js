
//Window
let ip = "192.168.4.2";
let port = "8801";
//const goHome = document.getElementById("backHome");

// goHome.addEventListener('click', ()=>{
//     homeView.hidden = false;
//     photoView.hidden = true
// })

//Views
const homeView = document.getElementById('home');
const photoView = document.getElementById('photoViewer');

//PhotoViewer
const img = document.getElementById('slideshow');
const viewPhotos = document.getElementById('viewPhotosBtn');
const viewPhotosBTN_Left = document.getElementById('prev');
const viewPhotosBTN_Right = document.getElementById('next');
let totalIMG = 4;
let index = 0;

function updateImage() {
  img.src = `http://${ip}:${port}/Photos/pic.png`;
}

viewPhotosBTN_Left.addEventListener('click', () => {
  index = (index - 1 + totalIMG) % totalIMG;
  updateImage();
});

viewPhotosBTN_Right.addEventListener('click', () => {
  index = (index + 1) % totalIMG;
  updateImage();
});

viewPhotos.addEventListener('click', () => {
  homeView.hidden = true;
  photoView.hidden = false;
  updateImage();
});