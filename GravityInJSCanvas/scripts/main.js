window.onload = function() {
    onReady();
}

let upButton;
let rightButton;
let leftButton;
let downButton;
let canvas;
let cordX = 5;
let cordY = 5;
let ctx;
let sec;//second
let endOfFor = false;
let sumSecs;//sum of seconds

const onReady = () => {
    upButton = document.getElementById('u');
    downButton = document.getElementById('d');
    leftButton = document.getElementById('l');
    rightButton = document.getElementById('r');
    canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');
    upButton.addEventListener("click", goUp);
    downButton.addEventListener("click", goToBottom);
    leftButton.addEventListener("click", goLeft);
    rightButton.addEventListener("click", goRight);
    document.addEventListener('keydown', function(event) {
        if (event.code == 'KeyZ' && (event.ctrlKey || event.metaKey)) {
          alert('Отменить!')
        }
        if (event.code == 'ArrowLeft') goLeft();
        if (event.code == 'ArrowRight') goRight();
        if (event.code == 'ArrowDown') goToBottom();
        if (event.code == 'ArrowUp') goUp();
      });

    ctx.beginPath();
    ctx.rect(cordX, cordY, 100, 50);
    ctx.fillStyle = 'green';
    ctx.fill();
};

const goRight = () => {
    cordX+=10;
    if (cordX >= 698)cordX-=10;
    resetCanvas();
};

const goLeft = () => {
    cordX-=10;
    if (cordX <= 2)cordX+=10;
    resetCanvas();
};

const goUp = () => {
    cordY-=10;
    if (cordY <= 2)cordY+=10;
    resetCanvas();
};

const goDown = () => {
    cordY+=10;
    if (cordY >= 248)cordY-=10;
    resetCanvas();
};

const resetCanvas = () => {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.beginPath();
    ctx.rect(cordX, cordY, 100, 50);
    ctx.fillStyle = 'green';
    ctx.fill();
};

const goToBottom = () => {
    sec = 0.000244140625;
    sumSecs = sec;
    for (var i=0;i<=250;i++) {
        (function(ind) {setTimeout(function(){
            console.log(ind);
            sec*=2;
            sumSecs=1024 + sec;
            cordY++;
            if (cordY >= 250){
                cordY=245;
            }
            resetCanvas();
        }, sumSecs)})(i);
        if (cordY === 250){
            break;
        }
    } 
};

/*
Math.pow(2, ind));
*/