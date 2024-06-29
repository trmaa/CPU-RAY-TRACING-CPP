let DISPLAY = document.querySelector("#canvas").children;
let CTX = [];
for (let i = 0; i < DISPLAY.length; i++) {
	CTX[i] = DISPLAY[i].getContext("2d");
}

CTX.forEach(c=>{c.fillStyle="#fff"; c.fillRect(0,0,200,200)});
