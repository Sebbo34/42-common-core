let domain_name = window.location.hostname;
import { navigate_to } from "../main.js";
import { getSocket, closeSocket, is_logged, getUserStatus } from "../main.js";

function drawLine(ctx, from, mid, to) {
const rect1 = from.getBoundingClientRect();
const rect2 = mid.getBoundingClientRect();
const rect3 = to.getBoundingClientRect();

const x1 = rect1.left + rect1.width / 2;
const y1 = rect1.top;

const x2 = rect2.left + rect2.width / 2;
const y2 = rect2.top;

const x3 = rect3.left + rect3.width / 2;
const y3 = rect3.top + rect3.height;

const midX = x1;
const midY1 = y1 - 30;

ctx.beginPath();
ctx.moveTo(x1, y1);
ctx.lineTo(midX, midY1);
ctx.stroke();

const midX2 = x2;

const midY2 = y2 - 30;
ctx.beginPath();
ctx.moveTo(x2, y2);
ctx.lineTo(midX2, midY2);
ctx.stroke();

ctx.beginPath();
ctx.moveTo(midX, midY1); 
ctx.lineTo(midX2, midY2); 
ctx.stroke();
//
const midX3 = (midX2 + midX) / 2;
ctx.beginPath();
ctx.moveTo(x3, y3);
ctx.lineTo(midX3, midY2);
ctx.stroke();

}

function get_display_name() {
  const container = document.getElementById("display_name");
  const inputs = container.querySelectorAll("input");
  const ids = [];

  inputs.forEach(input => {
    ids.push(input.value);
  });

  return ids;
}

function create_score_to_win(gameSettings)
{
  const settings = document.createElement("div");
  settings.classList.add("box");
  const title = document.createElement("div");
  title.classList.add("title_game_setting");
  title.textContent = "score to win"; 
  settings.appendChild(title);
  const button = document.createElement("button");
  button.className = "btn btn-primary";
  button.type = "button";
  button.style.backgroundColor = "transparent";
  button.style.border = "none";
  const add = create_settings_button(">");
  const content = create_settings_button(gameSettings["score_to_win"].toString());
  const substract = create_settings_button("<");
  substract.addEventListener("click", () => {
    content.textContent = '';
    if (gameSettings["score_to_win"] > 3)
      gameSettings["score_to_win"] = gameSettings["score_to_win"] - 1;
    content.textContent = gameSettings["score_to_win"].toString();
  });
  add.addEventListener("click", () => {
    content.textContent = '';
    if (gameSettings["score_to_win"] < 21)
      gameSettings["score_to_win"] = gameSettings["score_to_win"] + 1;
    content.textContent = gameSettings["score_to_win"].toString();
  });
  button.appendChild(substract);
  button.appendChild(content);
  button.appendChild(add);
  settings.appendChild(button);
  return (settings);
}

function create_input_field(id, type, placeholder) {
  const container = document.createElement("div");
  container.classList.add("player-input-container");

  const input = document.createElement("input");
  input.type = type;
  input.required = true;
  input.id = id;
  input.placeholder = placeholder;
  input.maxLength = 15

  const label = document.createElement("label");
  label.setAttribute("for", id);
  label.innerText = placeholder;

  container.appendChild(input);
  container.appendChild(label);

  return container;
}


function create_display_name(container) {

  const settings = document.createElement("div");
  settings.classList.add("box");
  settings.id = "display_name";
  const title = document.createElement("div");
  title.classList.add("title_game_setting");
  title.textContent = "Display Name"
  settings.appendChild(title);

  const input1 = create_input_field( "p1", 'text', `Display Name`)
  settings.appendChild(input1);
  container.appendChild(settings);

}
function create_setting(name, param, gameSettings)
{
  const buttons_array = [];
  const settings = document.createElement("div");
  settings.classList.add("box");
  const title = document.createElement("div");
  title.classList.add("title_game_setting");
  title.textContent = name;
  settings.appendChild(title);
  for (let i = 0; i < param.length; i++) 
  {
      buttons_array.push(create_settings_button(param[i]));
      settings.appendChild(buttons_array[i]);
      buttons_array[i].addEventListener("click", () => {
        buttons_array[i].style.backgroundColor = 'rgba(240, 165, 146, 0.8)';
        if (name == "paddle_size")
          gameSettings[name] =  100/(9 - i * 2);
        else if (name == "ball_speed")
          gameSettings[name] =  0.3 + (i *0.1);
        else
          gameSettings[name] =  i + 1;
        for (let j = 0; j < buttons_array.length; j++) {
          if (i != j) buttons_array[j].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
        }
      });
  }
  return (settings);
}

function set_game_settings(gameSettings)
{
  const gs = document.createElement("div");
  gs.id = "game_settings_tour";
  const title = document.createElement("h1");
  title.textContent = "Tournament Settings";
  gs.appendChild(title);
  gs.appendChild(create_setting("paddle_size", ["Little", "Medium", "Big"], gameSettings));
  gs.appendChild(create_setting("ball_speed", ["Slow", "Normal", "Fast"], gameSettings));
  gs.appendChild(create_setting("view", ["2D", "3D"], gameSettings));
  gs.appendChild(create_score_to_win(gameSettings));
  create_display_name(gs,gameSettings, "player1_tournament");

return (gs);
}

function create_settings_button(content) {
    const button = document.createElement("button");
    button.className = "btn btn-primary"; 
    button.type = "button";
    button.textContent = content;
    return button;
  }

function create_player(socket, players,number_of_match,i,user_in)
{
  const player = document.createElement("div");
  player.className = "player";
  player.id = `match-${number_of_match}-${i}`;

  const playerImg = document.createElement("img");
  playerImg.src = players[number_of_match][i]["profile_picture"]; 
  playerImg.alt = "profil picture"; 
  playerImg.className = "player-image"; 
  player.appendChild(playerImg);

  let tournament_status = players[number_of_match][i]['tournament_status'];
  const playerName = document.createElement("div");
  playerName.className = "name"; 
  playerName.textContent = players[number_of_match][i].username;
  player.appendChild(playerName);
  const status = create_settings_button(tournament_status);
  status.style.transform = "translate(3%, 30%)";
  if (tournament_status == "Unready" || tournament_status == "Eliminated")
    status.style.backgroundColor = "red";
  else 
    status.style.backgroundColor = "blue";
  if (tournament_status == "Register" && user_in == players[number_of_match][i].username)
  {
    status.textContent = "Leave";
    status.style.backgroundColor = "red";
  }
  if (user_in == players[number_of_match][i].username)
  {
    status.addEventListener("click",()=>{
      if (tournament_status == "Unready")
      {
        socket.send(JSON.stringify({type:"get_ready","tournament_id":players["tournament"]})); 
        status.style.backgroundColor = "blue";
      }
      else if(tournament_status == "Ready")
      {
        socket.send(JSON.stringify({type:"change_status","status":"Unready","tournament_id":players["tournament"]})); 
        status.style.backgroundColor = "red";
      }
      else if (tournament_status == "Register")
      {
        socket.send(JSON.stringify({type:"unjoin_tournament"}));
        navigate_to("/home");
      }
    });
  }
  player.appendChild(status);
  return(player);
}

function create_player_undefined(number_of_match,i)
{
  const player = document.createElement("div");
  player.className = "player";
  player.id = `match-${number_of_match}-${i}`;


  const playerImg = document.createElement("img");
  playerImg.alt = "profil picture"; 
  playerImg.className = "player-image";
  playerImg.src = '../../content/game_content/default.png'; 
  player.appendChild(playerImg);
  const playerName = document.createElement("div");
  playerName.className = "name"; 
  playerName.textContent = "undefined";
  player.appendChild(playerName);
  return(player);
}

function create_winner(socket, players, winner, tournament_lobby)
{
  const winner_round = document.createElement("div");
  winner_round.id = `winner_round`; 
  if (winner == "")
  {
    players["elem"]["0"] = [];
    const player = document.createElement("div");
    player.className = "player";
    player.id = `winner`;
    winner_round.appendChild(player);
  
    const playerImg = document.createElement("img");
    playerImg.alt = "profil picture";
    playerImg.className = "player-image";
    playerImg.src = '../../content/game_content/default.png'; 
    player.appendChild(playerImg);
    const playerName = document.createElement("div");
    playerName.className = "name";
    playerName.textContent = "undefined";
    player.appendChild(playerName);
    players["elem"]["0"].push(player);
  }
  else
  {
    players["elem"]["0"] = [];
    const player = document.createElement("div");
    player.className = "player";
    player.id = `winner`;
    winner_round.appendChild(player);
  
    const playerImg = document.createElement("img");
    playerImg.alt = "profil picture";
    playerImg.className = "player-image";
    playerImg.src = winner["profile_picture"]; 
    player.appendChild(playerImg);
    const playerName = document.createElement("div");
    playerName.className = "name";
    playerName.textContent = winner.username;
    player.appendChild(playerName);
    players["elem"]["0"].push(player);
    const create_new_tournament = create_settings_button("create_new_tournamen");
    create_new_tournament.style.position = "absolute";
    create_new_tournament.style.left = "-168px";
    create_new_tournament.style.top = "-130px";
    create_new_tournament.addEventListener("click", () => {
      socket.send(JSON.stringify({type:"set_unactive",})); 
      closeSocket("tournament");
      navigate_to("/tournament_lobby");
  });
    tournament_lobby.appendChild(create_new_tournament);
  }

  return(winner_round);
}


function drawLineWithAnimation(ctx, players, number_of_match, i) {
  // Calculer les coordonnées à dessiner
  let player1;
  let player2;
  let player3;
  if (number_of_match == 1)
  {
    player1 = players["elem"][number_of_match][0];
    player2 = players["elem"][number_of_match][1];
    player3 = players["elem"]["0"][0];
  }
  else
  {
    player1 = players["elem"][number_of_match][i * 2];
    player2 = players["elem"][number_of_match][(i * 2) + 1];
    player3 = players["elem"][number_of_match / 2][i];
  }
    // Créer une fonction pour l'animation frame
  function animate() {
      drawLine(ctx, player1, player2, player3);
  }
  requestAnimationFrame(animate);
}


function create_match(tournament_lobby, socket, round, canvas, players, number_of_match, user_in,active)
{
  const ctx = canvas.getContext('2d');
  let default_pp = players[2][0]["profile_picture"];
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.strokeStyle = "#333";
  ctx.lineWidth = 2;
  let empty = 1;
  if ( number_of_match != 2 || user_in !="")
    empty = 0;
if (!players["elem"][number_of_match]) {
    players["elem"][number_of_match] = [];
}
  const match = document.createElement("div");
  match.className = "match";
  for (let i = 0; i < number_of_match; i++) {
    const match = document.createElement("div");
    match.className = "match";
    match.id = `match-${number_of_match}-${i}`;
    if (i * 2 < players[number_of_match].length)
      players["elem"][number_of_match].push(create_player(socket, players, number_of_match, i*2,user_in));
    else
    {
      players["elem"][number_of_match].push(create_player_undefined(number_of_match,i));
      if (empty)
      {
        let display_name;
        display_name = "";
          empty = 0;
          const display_name_div = create_settings_button("Change display name");
          display_name_div.style.position = "absolute";
          display_name_div.style.left = "-168px";
          display_name_div.style.top = "-90px";

          display_name_div.addEventListener("click", () => {
            display_name = prompt("Enter your display name:");
            if (display_name !== null && display_name.trim() !== "") {
              display_name = display_name.trim();
              if (display_name.length > 15) {
                display_name = display_name.substring(0, 15);
              }
              display_name_div.textContent = "";
              display_name_div.textContent = "Display name : " + display_name;            }
        });
          tournament_lobby.appendChild(display_name_div);
          const join_button = create_settings_button("join");
          players["elem"][number_of_match][i*2].appendChild(join_button);
          join_button.addEventListener("click",()=>{
            socket.send(JSON.stringify({type:"join_tournament","tournament_id":players["tournament"],"display_name":display_name})); 
          });
      }
    }
    if (i * 2 + 1< players[number_of_match].length)
      players["elem"][number_of_match].push(create_player(socket, players, number_of_match, i*2 + 1,user_in));
    else
    {
      players["elem"][number_of_match].push(create_player_undefined(number_of_match,i));
      if (empty)
        {
          let display_name;
          display_name = "";
          empty = 0;
          const display_name_div = create_settings_button("Change display name");
          display_name_div.style.position = "absolute";
          display_name_div.style.left = "-168px";
          display_name_div.style.top = "-90px";

          display_name_div.addEventListener("click", () => {
            display_name = prompt("Enter your display name:");
            if (display_name !== null && display_name.trim() !== "") {
              display_name = display_name.trim();
              if (display_name.length > 15) {
                display_name = display_name.substring(0, 15);
              }
              display_name_div.textContent = "";
              display_name_div.textContent = "Display name : " + display_name;
            }
        });
          tournament_lobby.appendChild(display_name_div);
          const join_button = create_settings_button("join");
          players["elem"][number_of_match][i*2 + 1].appendChild(join_button);
          join_button.addEventListener("click",()=>{
            socket.send(JSON.stringify({type:"join_tournament","tournament_id":players["tournament"],"display_name":display_name})); 
          });
        }
    }
    match.appendChild(players["elem"][number_of_match][i*2]);
    match.appendChild(players["elem"][number_of_match][(i*2)+1]);
    round.appendChild(match);
      window.addEventListener("resize", () => {      

        const canvas = document.getElementById("tournamentCanvas");
        if (canvas) {
          canvas.width = window.innerWidth; 
          canvas.height = window.innerHeight;
        }
      
        drawLineWithAnimation(ctx, players, number_of_match, i);
      });
      drawLineWithAnimation(ctx, players, number_of_match, i);
}
}

function create_tournament(tournament_lobby, players, socket,user_in,active)
{  
  if (!players["elem"]) {
    players["elem"] = {};
}

  const canvas = document.createElement("canvas");
  canvas.id = "tournamentCanvas";
  tournament_lobby.appendChild(canvas);

  const tournament_tree = document.createElement("div");
  tournament_tree.id = "tournament_tree";
  let winner;
  if (players["winner"])
  {
    winner = create_winner(socket, players, players["winner"],tournament_lobby);
  }
  else
    winner = create_winner(socket, players, "",tournament_lobby);
  const final = document.createElement("div");
  final.id = "final";
  create_match(tournament_lobby, socket,final,canvas,players, 1,user_in,active);
  
  const demi = document.createElement("div");
  demi.id = "demi";
  create_match(tournament_lobby, socket,demi,canvas,players, 2,user_in,active);
  tournament_tree.appendChild(winner);
  tournament_tree.appendChild(final);
  tournament_tree.appendChild(demi);
  tournament_lobby.appendChild(tournament_tree);
}


export function render_tournament_lobby()
{
  let socket = null;
  let url = `wss://${domain_name}:8443/api/ws/tournament_lobby/`;
  
    socket = getSocket(url,"tournament");
    socket.addEventListener('open', () => {
          console.log('Connexion ouverte avec le serveur WebSocket');
        });
        
        socket.addEventListener('message', async (event) => {
          const data = JSON.parse(event.data);
          await is_logged();
           if (!getUserStatus()) {
              closeSocket("tournament");
              alert("You must be logged.");
              return;
           }

        if (data.type == 'available_tournament')
        {
          if (data["players"][2].length == 0)
            navigate_to("/home");
          tournament_lobby.textContent = "";
          create_tournament(tournament_lobby, data["players"],socket,data["user_in"],0);
        }
        if (data.type == 'active_tournament')
        {
          tournament_lobby.textContent = "";
          create_tournament(tournament_lobby, data["players"],socket, data["user_in"],1);
        }
        else if (data.type == 'start_tournament_game')
        {
          navigate_to("/game");
        }
        else if (data.type == 'start_tournament')
        {
          socket.send(JSON.stringify({type:"send_active_tournament"})); 
        }
        else if (data.type == "tournament_registration")
          socket.send(JSON.stringify({type:"send_available_tournament","available_tournament":data["available_tournament"]})); 
        else if(data.type == "display_create")
        {
          let gameSettings = {
            "paddle_size": 0,
            "number_of_player": 2,
            "ball_speed": 0,
            "view": 0,
            "score_to_win": 3,
            "player1": "player1",
            "player2": "player2",
            "local":-2
        };       
          const settings =  set_game_settings(gameSettings);
          tournament_lobby.appendChild(settings);
          const create = create_settings_button("Create my tournament");
          create.id = "create_tournament_button";
          tournament_lobby.appendChild(create);
          create.addEventListener("click", ()=>{
            let ids = get_display_name();
            const allSettingsValid = Object.values(gameSettings).every(value => value !== 0);
            if (allSettingsValid)
            {
              socket.send(JSON.stringify({type:"create_tournament","gameSettings":gameSettings, "display_name":ids[0]})); 
            }
          });
        }
    });
    socket.addEventListener('error', (error) => {
        navigate_to("/home");
        console.error('Erreur WebSocket :', error);
      });
  
    socket.addEventListener('close', () => {
        console.log('Tournament socket close');
      });
      const tournament_lobby = document.createElement("div");
      tournament_lobby.id = "tournament_lobby";
    return (tournament_lobby); 
}
