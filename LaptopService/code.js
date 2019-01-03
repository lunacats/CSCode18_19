const forward = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':0,p:-10}");
    const myJson = await response.json(); //extract JSON from the http response
    // do something with myJson
}
const back = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':1,p:-10}");
    const myJson = await response.json(); //extract JSON from the http response
    // do something with myJson
}
const left = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':2,p:-10}");
    const myJson = await response.json(); //extract JSON from the http response
    // do something with myJson
}
const right = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':3,p:-10}");
    const myJson = await response.json(); //extract JSON from the http response
    // do something with myJson
}
const stop = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':4}");
    const myJson = await response.json(); //extract JSON from the http response
    // do something with myJson
}

const loadPixy = async () => {

    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':5}");
    const myJson = await response.json(); //extract JSON from the http response

    const count = myJson["C"];


    const pixyView = document.getElementById('pixyViewBox');

    pixyView.innerHTML = '';

    for(i = 0; i < count; i++) {
        const width  = myJson["W"+i]/320;
        const height = myJson["H"+i]/200;

        const x = myJson["X"+i]/320 - width/2;
        const y = myJson["Y"+i]/200 - height/2;



        const box = document.createElement("DIV");
        box.setAttribute("class","pixyImg");

        // <div id = "sig 1" class="pixyImg" style="width: 50px; height: 50px;"></div>
        box.setAttribute("style",
            "width: "+width*100+"%;" +
            " height: "+height*100+"%;" +
            " left:"+x*100+"%;" +
            " top:"+y*100+"%;");

        box.innerHTML = myJson["S"+i];

        pixyView.appendChild(box);
    }



}
const loadLidar = async () => {
    const response = await fetch("http://172.16.50.154:5000/cmd/{'c':6}");
    const myJson = await response.json(); //extract JSON from the http response

    const dist = myJson["L"];


    document.getElementById("lidarDistance").setAttribute("value",dist);

}


const sendCode = async () => {
    const code = document.getElementById("code").value;

    console.log(code);

    try {
        const response = await fetch("http://172.16.50.154:5000/cmd/{'c':7,'v':'"+code+"'}");
        const myJson = await response.json(); //extract JSON from the http response


        log.value = myJson["R"];
    }
    catch(err) {
        log.value = "An error has occoured:\n"+err.message;
    }

}


function startup() {
    //setInterval(loadLidar,3000);
    //setInterval(loadPixy,3000);
}
window.onload = startup;