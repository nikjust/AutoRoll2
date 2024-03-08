let socket = new WebSocket(`ws://${window.location.hostname}/ws`);
socket.binaryType = 'arraybuffer';

socket.onopen = function(e) {
    console.log("[open] Соединение установлено");
    console.log("Отправляем данные на сервер");
};

socket.onmessage = function(event) {
    console.log(`[message] Данные получены с сервера: ${event.data}`);
};

socket.onclose = function(event) {
    if (event.wasClean) {
        console.log(`[close] Соединение закрыто чисто, код=${event.code} причина=${event.reason}`);
    } else {
        // например, сервер убил процесс или сеть недоступна
        // обычно в этом случае event.code 1006
        console.log('[close] Соединение прервано');
    }
};

socket.onerror = function(error) {
    console.log(`[error]`);
};

function sendInt(num){
    const uint8 = new Uint8Array(4);
    uint8[0] = 0x34;
    uint8[1] = 0xAA;
    uint8[2] = num;
    uint8[3] = 0;

    socket.send(uint8)
}

window.onload = (event) => {
    let openButton = document.getElementById("open")
    openButton.onclick = (event) => {
        sendInt(201)
    }
    let closeButton = document.getElementById("close")
    closeButton.onclick = (event) => {
        sendInt(202)
    }
    console.log("[init] Кнопки проинициализированы")
}

