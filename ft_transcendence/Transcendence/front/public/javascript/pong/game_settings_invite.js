let domain_name = window.location.hostname;
import { getSocket, closeSocket,  navigate_to, setUserStatus } from "../main.js";


const postRequest = async (endpoint, data) => { 
    try {
        let head = {
                "Content-Type": "application/json",
            };
        const response = await fetch(`/api${endpoint}`, {
            method: "POST",
            headers: head,
            credentials: 'include',
            body: JSON.stringify(data)
        });
        if (!response.ok) {
            throw new Error(`Erreur ${response.status}: ${await response.text()}`);
        }
        const result = await response.json();
        return result;
    } catch (error) {
        console.error("Erreur:", error);
        return null;
    }
};

function create_score_to_win(gameSettings, socket,player2)
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
    socket.send(JSON.stringify({"type":"send_gs","player2":player2,"gameSettings":gameSettings}));
  });
  add.addEventListener("click", () => {
    content.textContent = '';
    if (gameSettings["score_to_win"] < 21)
      gameSettings["score_to_win"] = gameSettings["score_to_win"] + 1;
    content.textContent = gameSettings["score_to_win"].toString();
    socket.send(JSON.stringify({"type":"send_gs","player2":player2,"gameSettings":gameSettings}));
  });
  button.appendChild(substract);
  button.appendChild(content);
  button.appendChild(add);
  settings.appendChild(button);
  return (settings);
}


function create_setting(name, param, gameSettings, socket, player2)
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
        socket.send(JSON.stringify({"type":"send_gs","player2":player2,"gameSettings":gameSettings}));
      });
  }
  return (settings);
}

function display_setting(name, param, gameSettings)
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
      if (name == "paddle_size")
      {
        if (gameSettings[name] ==  100/(9 - i * 2))
          buttons_array[i].style.backgroundColor = 'rgba(240, 165, 146, 0.8)';
        else
          buttons_array[i].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
      }
      else if (name == "ball_speed")
      {
        if (gameSettings[name] ==  0.3 + (i *0.1))
          buttons_array[i].style.backgroundColor = 'rgba(240, 165, 146, 0.8)';
        else
          buttons_array[i].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
      }
      else
      {
        if (gameSettings[name] ==  i + 1)
          buttons_array[i].style.backgroundColor = 'rgba(240, 165, 146, 0.8)';
        else
          buttons_array[i].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
      }
  }
  return (settings);
}

function display_game_settings(gameSettings)
{
  const gs = document.createElement("div");
  gs.id = "game_settings_invite";
  const title = document.createElement("h1");
  title.textContent = "Game Settings";
  gs.appendChild(title);
  gs.appendChild(display_setting("paddle_size", ["Little", "Medium", "Big"], gameSettings));
  gs.appendChild(display_setting("ball_speed", ["Slow", "Normal", "Fast"], gameSettings));
  gs.appendChild(display_setting("view", ["2D", "3D"], gameSettings));
  gs.appendChild(display_setting("score_to_win", [gameSettings['score_to_win']], gameSettings));
return (gs);
}

function set_game_settings(socket, gameSettings, player2)
{
  const gs = document.createElement("div");
  gs.id = "game_settings_invite";
  const title = document.createElement("h1");
  title.textContent = "Game Settings";
  gs.appendChild(title);
  gs.appendChild(create_setting("paddle_size", ["Little", "Medium", "Big"], gameSettings, socket, player2));
  gs.appendChild(create_setting("ball_speed", ["Slow", "Normal", "Fast"], gameSettings, socket, player2));
  gs.appendChild(create_setting("view", ["2D", "3D"], gameSettings, socket, player2));
  gs.appendChild(create_score_to_win(gameSettings, socket, player2));
return (gs);
}

function create_settings_button(content) { 
  const button = document.createElement("button");
  button.className = "btn btn-primary"; 
  button.type = "button";
  button.textContent = content;
  return button;
}

export function render_gs_invite()
{
  let gameSettings = {
    "paddle_size": 0,
    "number_of_player": 2,
    "ball_speed": 0,
    "view": 0,
    "score_to_win": 3,
    "player1": "player1",
    "player2": "player2",
    "local":-1
};
    let url = `wss://${domain_name}:8443/api/ws/create_gs/`;

    const socket = getSocket(url, "gs");
    socket.onopen = function(event) {
    };

    // Événement : Message reçu du serveur
    socket.onmessage = function(event) {
        const data = JSON.parse(event.data);
        if (data["type"] == 'display_settings')
        {
            gs_without_lobby.textContent = "";
            const settings =  set_game_settings(socket, gameSettings, data["player2"]);
            const play_button = create_settings_button("Play");
            settings.appendChild(play_button);
            play_button.addEventListener("click", async () =>
            {
               
                const allSettingsValid = Object.values(gameSettings).every(value => value !== 0 && value !== "");
                if (allSettingsValid)
                {
                    const reponse = await postRequest("/gs_without_lobby/", gameSettings);
                    if(reponse != null)
                    {
                        socket.send(JSON.stringify({"type":"start_play"}));
                        navigate_to("/game");
                    }
                }
            });
            gs_without_lobby.appendChild(settings);
        }
        if (data["type"] == 'start_play')
        {
          closeSocket("gs");
          navigate_to("/game");
        }
        else if (data["type"] == 'waiting')
        {
          gs_without_lobby.textContent = "";
          if (data['gameSettings'] != "")
          {
            gameSettings = data['gameSettings'];
          }
          const settings = display_game_settings(gameSettings);
          gs_without_lobby.appendChild(settings);
        }
        if (data["type"] == 'disconnect')
        {
          if (data["alert"]) {
            alert(data["alert"]);
          }
          closeSocket("gs");
          navigate_to("/home");
        }
    };
    socket.onerror = function(error) {
      navigate_to("/home");
      console.error("Erreur WebSocket :", error);
    };
    socket.onclose = function(event) {
      console.log("Connexion WebSocket fermée");
    };

    let gs_without_lobby = document.createElement("div");
    gs_without_lobby.id = "game_settings";
      return (gs_without_lobby);
}
