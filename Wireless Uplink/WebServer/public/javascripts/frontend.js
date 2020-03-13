var amountOfCards = 0;

function checkedOutElementCreator(name,timestamp){
    console.log('Out ' + name + '  ' + timestamp);
    timestamp = timestamp.replace('T', ' ').replace('Z', '').substring(0, timestamp.length-5);
    var mainDiv = document.getElementById('main');
    if(amountOfCards%5 === 0){
        mainDiv.innerHTML += '<div class="w-100 d-none d-xl-block"><!-- wrap every 5 on xl--></div>'
    }
    mainDiv.innerHTML += '<div class="card border-danger mb-3" style="width: 15rem;">\n' +
        '  <div class="card-body">\n' +
        `    <h5 class="card-title">${name}</h5>\n` +
        '    <div>\n' +
        `    <p class="card-text" style="float: left; margin-right: 2rem">${timestamp}</p>\n` +
        '      <span class="badge badge-danger" style="float: left; margin-top: 5px">Checked-Out</span>\n' +
        '    </div>\n' +
        '  </div>\n' +
        '  <p style="font-family: \'Comic Sans MS\';font-size: 10px;text-align: center">Made by: JFD©®™</p>\n' +
        '</div>\n'
    amountOfCards += 1;
}

function checkedInElementCreator(name,timestamp){
    console.log('In ' + name + '  ' + timestamp);
    timestamp = timestamp.replace('T', ' ').replace('Z', '').substring(0, timestamp.length-5);
    var mainDiv = document.getElementById('main');
    if(amountOfCards%5 === 0){
        mainDiv.innerHTML += '<div class="w-100 d-none d-xl-block"><!-- wrap every 5 on xl--></div>'
    }
    mainDiv.innerHTML += '<div class="card border-primary mb-3" style="width: 15rem;">\n' +
        '  <div class="card-body">\n' +
        `    <h5 class="card-title">${name}</h5>\n` +
        '    <div>\n' +
        `    <p class="card-text" style="float: left; margin-right: 2rem">${timestamp}</p>\n` +
        '      <span class="badge badge-primary" style="float: left; margin-top: 5px">Checked-In</span>\n' +
        '    </div>\n' +
        '  </div>\n' +
        '  <p style="font-family: \'Comic Sans MS\';font-size: 10px;text-align: center">Made by: JFD©®™</p>\n' +
        '</div>\n'
    amountOfCards += 1;
}


function clearMainDiv() {
    var mainDiv = document.getElementById('main');
    mainDiv.innerHTML = '';
    amountOfCards = 0;
}

function connect() {
    var socket = io.connect('http://localhost:3000');
    socket.on('update', function (data) {
        console.table(data);
        clearMainDiv();
        for (index in data){
            obj = data[index];
            if(obj.status === 'IN'){
                checkedInElementCreator(obj.name,obj.dt)
            } else if(obj.status === 'OUT'){
                checkedOutElementCreator(obj.name,obj.dt)
            }
        }
    });
    fetch('http://www.localhost:3000/ws');
}

connect();

