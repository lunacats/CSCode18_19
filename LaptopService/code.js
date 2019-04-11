//Commands and the numbers they're represented as
const forwardCmd = 0;
const backCmd = 1;
const leftCmd = 2;
const rightCmd = 3;
const stopCmd = 4;
const getPixyInfoCmd = 5;
const getLidarInfoCmd = 6;

//TODO: Implement these on raspberry Pi
const startAutoCmd    = 7;
const stopAutoCmd     = 8;

//Ip address that the program connects to
const ip = "http://10.0.10.10:5000"

//Standard power assigned to each motor
const buttonPower = -10;

//This creates the json string for a drive command with a given ammount of power
function createDriveCommandWithPower (cmd, power) {
  return ip+"/cmd/{'c':"+cmd+",'p':"+power+"}";
}
//This creates the json string for a drive command with a standard ammount of power
function createDriveCommand (cmd) {
  return createDriveCommandWithPower(cmd,buttonPower)
}

//This sends the json to the raspberry pi and gets a response
async function sendJson(json){
  console.log("Sent:\t"+json);
  const response = fetch(json, {mode: 'cors'});
  console.log("Got:\t"+response);
  return response;
}

//This sends a drive command with a standard ammount of power to the robot
function sendDriveCommand (cmd) {
  return sendJson(createDriveCommand(cmd))
}
//This sends a json string with just a cmd specified to the robot
function sendCmd(cmd) {
  return sendJson(ip+"/cmd/{'c':"+cmd+"}");
}

//These are used by the buttons in drivePage.html
const forward = async () => {
    const myJson = await sendDriveCommand(forwardCmd)
}
const back = async () => {
    const myJson = await sendDriveCommand(backCmd)
}
const left = async () => {
    const myJson = await sendDriveCommand(leftCmd)
}
const right = async () => {
    const myJson = await sendDriveCommand(rightCmd)
}
const stop = async () => {
    const myJson = await sendDriveCommand(stopCmd)
}

const startAuto = async () => {
    const myJson = await sendCmd(startAutoCmd)
}
const stopAuto = async () => {
    const myJson = await sendCmd(stopAutoCmd)
}





//This sets up the pixy view
setInterval( loadPixy = async () => {

    const response = await sendCmd(getPixyInfoCmd);

    const myJson = response.json(); //extract JSON from the http response

    console.log("Got:"+myJson);
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


},5000);
//This gets the lidar distance from the robot
const loadLidar = async () => {
    const response = await sendCmd(getLidarInfoCmd);
    const myJson = await response.json(); //extract JSON from the http response

    const dist = myJson["L"];

    document.getElementById("lidarDistance").setAttribute("value",dist);

}
