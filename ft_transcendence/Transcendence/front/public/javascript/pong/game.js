import { navigate_to } from "../main.js";

let domain_name = window.location.hostname;

let keydown_handler = null;
let keyup_handler = null;
import { getSocket, closeSocket } from "../main.js";

class Player {
    constructor(x,y, width, height, color, name) {
      this.x = x;
      this.y = y;
      this.width = width;
      this.height = height;
      this.color = color;
      this.power = 0;
      this.username = name;
      this.box = 0;
    }
    draw(ctx, maps)
    {
      ctx.fillStyle = this.color;
      ctx.fillRect(this.x,  maps.height * (this.y/100), this.width, this.height);
    }
    update()
    {
      this.box.position.x = (4.75 * this.y/100) - 2.375;
    } 
  }
  
class Ball
{
    constructor(x, y, r, color) {
      this.x = x;
      this.y = y;
      this.r =r;
      this.color = color;
    }
    draw(ctx, maps)
    {
        ctx.beginPath();
        ctx.fillStyle = this.color;
        ctx.arc(maps.width * (this.x/100), maps.height* (this.y/100), this.r,  0, Math.PI * 2);
        ctx.fill();
    }
    update()
    {
      this.sphere.position.z = 2.45 - (4.9 * this.x/100);
      this.sphere.position.x = (4.70 * this.y/100) - 2.35;
    } 
}

let renderer, camera, scene;

function initScene() {
    if (renderer) {
        renderer.dispose();
        renderer.forceContextLoss();
        if (renderer.domElement && renderer.domElement.parentNode) {
            renderer.domElement.parentNode.removeChild(renderer.domElement);
        }
    }
    if (scene) {
        scene.traverse((object) => {
            if (object.geometry) object.geometry.dispose();
            if (object.material) {
                if (Array.isArray(object.material)) {
                    object.material.forEach(material => material.dispose());
                } else {
                    object.material.dispose();
                }
            }
        });
    }

    camera = null;
    scene = null;
    renderer = null;

    renderer = new THREE.WebGLRenderer();
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.5, 1000);
    scene = new THREE.Scene();

    document.body.appendChild(renderer.domElement);
}


function setScene(player, player2, ball, game)
{
  initScene();
  const texturePadd = new THREE.TextureLoader();
  const PaddTexture = texturePadd.load('../../content/game_content/steel2.jpg'); 
  const PaddMaterial = new THREE.MeshLambertMaterial({ map: PaddTexture });
  player.box = new THREE.Mesh(
    new THREE.BoxGeometry(0.12, 0.12, player.height),
    PaddMaterial         
  );
  player.box.position.y = 0;
  player.box.position.x = 0;
  player.box.position.z = 2.5;
  player.box.rotateY(1.58);

  player2.box = new THREE.Mesh(
    new THREE.BoxGeometry(0.12, 0.12, player.height),
    PaddMaterial
            );
  player2.box.position.y = 0;
  player2.box.position.x = 0;
  player2.box.position.z = -2.5;
  player2.box.rotateY(1.58);
  
  ball.sphere = new THREE.Mesh(
    new THREE.SphereGeometry(0.09, 32, 32),
    new THREE.MeshPhongMaterial({color:  0xFFF0F0})
  );
  ball.sphere.position.y = 0.09;
  ball.sphere.position.x = 0;
  ball.sphere.position.z = 0;
  loadScene(player.box, player2.box, ball.sphere, game);
}

function updateViewportSize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth / 2.5, window.innerHeight * 0.5);
}


function loadScene(player1, player2, ball) {
  renderer.domElement.style.borderRadius = "20px";
  renderer.domElement.style.border = "2px solid white";
  renderer.domElement.style.display = "block";
  renderer.domElement.style.margin = "0 auto";
  camera.rotation.y = Math.PI;
    renderer.setSize(window.innerWidth, window.innerHeight);
    const game_header = create_game_header();
    game.appendChild(game_header);
    game.appendChild(renderer.domElement);
    renderer.setPixelRatio(2.5);
    const textureLoaderScene = new THREE.TextureLoader();
    const backgroundTexture = textureLoaderScene.load('../../content/game_content/bleu.jpg');
    scene.background = backgroundTexture;
    scene.add(player1);;
    scene.add(player2);
    scene.add(ball);

    const textureWall = new THREE.TextureLoader();
    const WallTexture = textureWall.load('../../content/game_content/woodC.png');
    const WallMaterial = new THREE.MeshLambertMaterial({ map: WallTexture });
    var leftWall = new THREE.Mesh(
      new THREE.BoxGeometry(0.25, 0.25, 5),
      WallMaterial
    );
    leftWall.position.y = 0;
    leftWall.position.x = 2.5;
    leftWall.position.z = 0;
    scene.add(leftWall);
    
    var rightWall = new THREE.Mesh(
      new THREE.BoxGeometry(0.25, 0.25, 5),
      WallMaterial
    );
    rightWall.position.y = 0;
    rightWall.position.x = -2.5;
    rightWall.position.z = 0;
    scene.add(rightWall);
    
    const textureLoader = new THREE.TextureLoader();
    const groundTexture = textureLoader.load('../../content/game_content/wood.jpg');
    const groundMaterial = new THREE.MeshLambertMaterial({ map: groundTexture });
    const ground = new THREE.Mesh(
        new THREE.PlaneGeometry(),
        groundMaterial
    );
    ground.rotation.x = -Math.PI / 2;
    ground.position.y = 0;    
    ground.scale.setScalar(5);
    scene.add(ground);
    var sun = new THREE.DirectionalLight();
    sun.position.set(2, 2, 1);
    scene.add(sun);

    camera.position.x = 0;
    camera.position.y = 3;
    camera.position.z = 5;
    camera.lookAt(ground.position);
    
    renderer.shadowMap.enabled = true;
    ground.receiveShadow = true;
    player1.castShadow = true;
    player2.castShadow = true;
    ball.castShadow = true;
    sun.castShadow = true;
    window.addEventListener("resize", updateViewportSize);
    updateViewportSize();
}
  
function drawMiddleLine(ctx, maps)
{
    ctx.strokeStyle = 'white'; 
    ctx.lineWidth = 2;       
    ctx.beginPath();
    ctx.moveTo(maps.width/2, 0);      
    ctx.lineTo(maps.width/2, maps.height);    
    ctx.stroke();
}

function updateScore(name, sc, canvaName,view)
{
  const score = document.getElementById(canvaName);
  const ctx2 = score.getContext("2d");
  ctx2.clearRect(0, 0, score.width, score.height);
  ctx2.font = "48px arial";
  ctx2.fillStyle = "white"
  ctx2.fillText(name, 50, 50);
  ctx2.fillText(sc, 50, 100);
}


function updatePlayer(newPos, p)
{
    p.y = newPos;
}

function updateBall(newBall, ball)
{
  ball.x = newBall['x'];
  ball.y = newBall['y'];
}

const keysAlreadySent = {};

function send_keydown(socket, input) {
  function trySend(key, sender, action) {
    if (keysPressed[key] && !keysAlreadySent[key]) {
      input["sender"] = sender;
      input["input"] = action;
      input["event"] = "keydown";
      if (socket.readyState === WebSocket.OPEN) {
        socket.send(JSON.stringify(input));
        keysAlreadySent[key] = true;
      }
    }
  }

  trySend(P1key1, "p1", "Up");
  trySend(P1key2, "p1", "Down");
  trySend(P2key1, "p2", "Up");
  trySend(P2key2, "p2", "Down");

  if (keysPressed["p"] && !keysAlreadySent["p"]) {
    input["input"] = "break";
    input["event"] = "keydown";
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(JSON.stringify(input));
      keysAlreadySent["p"] = true;
    }
  }
}


function send_keyup(socket, input, key) {
  let inputName = "";
  let sender = "";

  if (key === P1key1) {
    inputName = "Up";
    sender = "p1";
  } else if (key === P1key2) {
    inputName = "Down";
    sender = "p1";
  } else if (key === P2key1) {
    inputName = "Up";
    sender = "p2";
  } else if (key === P2key2) {
    inputName = "Down";
    sender = "p2";
  }

  if (inputName && sender) {
    input["sender"] = sender;
    input["input"] = inputName;
    input["event"] = "keyup";
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(JSON.stringify(input));
    }
    keysPressed[key] = false;
    keysAlreadySent[key] = false;
  }

  if (key === 'p') {
    keysPressed['p'] = false;
    keysAlreadySent['p'] = false;
  }
}


function create_game_header()
{
    const   game_header = document.createElement("div");
    game_header.id = "game_header";
    const score_player1 = document.createElement("canvas");
    score_player1.id = 'score_player1';
    const score_player2 = document.createElement("canvas");
    score_player2.id = 'score_player2';
    game_header.appendChild(score_player1);
    game_header.appendChild(score_player2);
    return(game_header);
}

function create_win_header(result, winner, loser) {
  const win = document.createElement("div");
  win.id = "win";

  // Fond animé
  const gifBackground = document.createElement("div");
  gifBackground.className = "gif-background";
  win.appendChild(gifBackground);

  // Titre "Game Over"
  const winHeader = document.createElement("div");
  winHeader.id = "winHeader";
  winHeader.textContent = "Game Over";
  win.appendChild(winHeader);

  // Résumé
  const resume = document.createElement("div");
  resume.id = "resume";
  let duel = winner + " vs " + loser;
  resume.innerHTML = `<p>${duel}</o><br>${result}`;
  win.appendChild(resume);

  return win;
}


function set_key_event(socket, input)
{
    if (keydown_handler) {
        document.removeEventListener("keydown", keydown_handler);
    }
    if (keyup_handler) {
        document.removeEventListener("keyup", keyup_handler);
    }
    keydown_handler =(event) => {
        keysPressed[event.key] = true;
        send_keydown(socket, input);
    }
    keyup_handler = (event) => {
        send_keyup(socket, input, event.key);

    }
    document.addEventListener('keydown', (event) => keydown_handler(event, socket, input));
    document.addEventListener('keyup', (event) => keyup_handler(event, socket, input));
}

let     keysPressed = {};
let P1key1 = '';
let P1key2 = '';
let P2key1 = '';
let P2key2 = '';

function load_maps(game)
{
    const game_header = create_game_header();
    const maps = document.createElement("canvas");
    maps.id = "maps";
    game.appendChild(game_header);
    game.appendChild(maps);
    const ctx = maps.getContext('2d');
    return ctx;
}

function create_pause_menu(socket,game) {
  let input = {
    type : 'handle_input',
    event: '',
    sender:"p1",
    input:""
};
  const pause_menu = document.createElement("div");
  pause_menu.id = "pause";
  
  const pause_text = document.createElement("h2");
  pause_text.textContent = "Game Paused";
  pause_menu.appendChild(pause_text);


  const RH = document.createElement("div");
  RH.id = "RH2";

  // Home
  const home = document.createElement("div");
  home.id = "Home";
  home.style.height = "7vh";
  home.style.width = "4vw";
  home.style.left = "0";
  RH.appendChild(home);
  home.addEventListener("click",()=>{
    socket.close();
    navigate_to("/home");
  });
  // Replay
  const restart = document.createElement("div");
  restart.id = "restart";
  RH.appendChild(restart);
  restart.addEventListener("click", ()=>
  {
    input["input"] = "break";
    input["event"] = "keydown";
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(JSON.stringify(input));
    }
  });
  // Ajout de RH dans win
  pause_menu.appendChild(RH);
  game.appendChild(pause_menu);
  return pause_menu;
}


function add_event_socket(socket,game,restore_data)
{
  let c = 0;
  let run = 0;
  let ball;
  let player;
  let player2;
  let ctx;
  let pause_menu;
  let view;
  keysPressed = {};
  P1key1 = '';
  P1key2 = '';
  P2key1 = '';
  P2key2 = '';
  const settings = restore_data['settings'];
  if (settings["view"] == 1)
  {
    view = "2D";
    P1key1 = "w";
    P1key2 = "s";
  }
  else
  {
    P1key1 = "a";
    P1key2 = "d";
    view = "3D";
  }
  if (settings["number_of_player"] == 2 &&  settings["local"] == 1)
  {
    if (view == "2D")
    {
      P2key1 = "ArrowUp";
      P2key2 = "ArrowDown";
    }
    if (view == "3D")
    {
      P2key1 = "ArrowLeft";
      P2key2 = "ArrowRight";
    }
  }
  socket.addEventListener('open', () => { 
    socket.send(JSON.stringify(restore_data));
  });
  socket.addEventListener('message', (event) => {
    const data = JSON.parse(event.data);
    if (data["type"] == 'game_state')
    {
      if (c == 0)
      {
        c = 1;
        pause_menu = create_pause_menu(socket,game);
      }
      updateScore(data['player1']['username'],data['player1']['score'], "score_player1",view);
      updateScore(data['player2']['username'],data['player2']['score'], "score_player2",view);
      updatePlayer(data['player1']['pos'], player);
      updatePlayer(data['player2']['pos'], player2);
      updateBall(data['ball'], ball);
      if (view == '2D')
      {        
        ctx.clearRect(0, 0, maps.width, maps.height);
        drawMiddleLine(ctx,maps);
        ball.draw(ctx,maps);
        player.draw(ctx,maps);
        player2.draw(ctx,maps);
      }
      else
      {
          ball.update();
          player.update();
          player2.update();
          renderer.render(scene, camera);
      }
      if (data["game_state"] == "on")
      {
        pause_menu.style.display = "none";
      }   
      else
      {
        pause_menu.style.display = "flex";
      }   
    }
    else if (data["type"] == "countdown")
  {
        // Supprime les anciens comptes à rebours s'il y en a
        const oldCountdown = document.getElementById("countdown");
        if (oldCountdown) oldCountdown.remove();
    
        const countdown = document.createElement("div");
        countdown.id = "countdown";
        countdown.textContent = data.message;
         // Ajout du style directement en JS
        countdown.style.fontSize = "100px";
        countdown.style.fontWeight = "bold";
        countdown.style.color = "black";
        countdown.style.textAlign = "center";
        countdown.style.position = "absolute";
        countdown.style.top = "50%";
        countdown.style.left = "50%";
        countdown.style.transform = "translate(-50%, -50%)";
        countdown.style.animation = "scaleDown 1s ease-in-out";
    
        // Ajout de l'animation avec un style global si pas déjà présent
        if (!document.getElementById("countdown-style")) {
            const style = document.createElement("style");
            style.id = "countdown-style";
            style.innerHTML = `
                @keyframes scaleDown {
                    0% { transform: scale(1.5) translate(-50%, -50%); opacity: 0; }
                    50% { opacity: 1; }
                    100% { transform: scale(1) translate(-50%, -50%); opacity: 0.8; }
                }
            `;
            document.head.appendChild(style);
        }
    
        game.appendChild(countdown);
    }
    else if (data.type === "start_game") 
    {
      game.textContent = '';
      if (view == '2D')
      {
        ctx = load_maps(game);
        ball = new Ball(50, 50, 2, 'white');
        player = new Player(0, 0, 3, maps.height/((1 / settings["paddle_size"]) * 100), 'white', 'p1');
        player2 = new Player(maps.width - 3, 10, 3, maps.height/((1 / settings["paddle_size"]) * 100), 'white', 'p2');
      }
      else if (view == '3D')
      {
        ball = new Ball(50, 50, 2, 'white');
        player = new Player(0, 0, 3, 4.5/((1 / settings["paddle_size"]) * 100), 'white', 'p1');
        player2 = new Player(0, 10, 3, 4.75/((1 / settings["paddle_size"]) * 100), 'white', 'p2');
        setScene(player,player2,ball,game);
      }
      run = 1;
    }
    else if (data["type"] == "result")
    {
      P1key1 = '';
      P1key2 = '';
      P2key1 = '';
      P2key2 = '';
      game.textContent = "";
      game.appendChild(create_win_header(data["result"], data["winner"], data["loser"]));
      closeSocket("game")
    }
    else if (data["type"] == "disconnect")
    {
      P1key1 = '';
      P1key2 = '';
      P2key1 = '';
      P2key2 = '';
      game.textContent = "";
      game.appendChild(create_win_header("Your opponnent has been disconnected", data["user"], data["player_disconnect"]));
      closeSocket("game")
    }
    else if (data["type"] == "result_tournament")
      {
        navigate_to("/tournament_lobby");
      }
  });
  socket.addEventListener('error', (error) => {console.error('Erreur WebSocket :', error);});
  socket.addEventListener('close', () => {console.log('Connexion WebSocket fermée');});
}

const getRequest = async (url) => {
  const headers = {
    "Content-Type": "application/json"
  }
  try {
    const response = await fetch(url, {
      method: "GET",
      headers:headers,
      credentials: "include"
    });
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    const data = await response.json(); 
    return data;
  } catch (error) {
    return null;
  }
};

let socket = null;

export async function render_game()
{
    let game_id;
    let input = {
        type : 'handle_input',
        event: '',
        sender:"p1",
        input:""
    };
    
    const   game = document.createElement("div");
    game.id = "game";
    let url = `/api/game-info/`
    const data = await getRequest(url); 
    if (data)
    {
      game_id = data.game['game_id'];
      url = `wss://${domain_name}:8443/api/ws/game/${game_id}/`; 
      socket = getSocket(url, "game");
      data.game['type'] = "set_first_co";
      add_event_socket(socket, game, data.game);
      set_key_event(socket, input)
    }
    else
    {
      alert("Game not Found");
      navigate_to("/home");
    }
    return (game); 
}