import { navigate_to } from "../main.js";

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


function create_settings_button(content) {
  const button = document.createElement("button");
  button.className = "btn btn-primary";  
  button.type = "button";
  button.textContent = content;
  return button;
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


function create_player_name(container) {

// Titre avant les inputs
const title = document.createElement("div");
title.classList.add("title_game_setting");
title.textContent = "Player 2"
container.appendChild(title);

// Input principal
const input1 = create_input_field( "p1", 'text', `Player2`)
container.appendChild(input1);
}


function create_number_of_player(param, gameSettings, player_name)
{
const buttons_array = [];
const settings = document.createElement("div");
settings.classList.add("box");
const title = document.createElement("div");
title.classList.add("title_game_setting");
title.textContent = "Number of Player"; 
settings.appendChild(title);
for (let i = 0; i < param.length; i++) 
{
    buttons_array.push(create_settings_button(param[i]));
    settings.appendChild(buttons_array[i]);
    buttons_array[i].addEventListener("click", () => {
      buttons_array[i].style.backgroundColor = 'rgba(240, 165, 146, 0.8)';
      gameSettings["number_of_player"] =  i + 1;
      for (let j = 0; j < buttons_array.length; j++) {
        if (i != j)
          {
            buttons_array[j].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
            player_name.textContent = "";
            if (i == 1)
              create_player_name(player_name);
          } 
      }
    });
}
return (settings);
}

function set_title_game_settings(title)
{
if (!title) return '';
const withSpaces = title.replace(/_/g, ' ');
return withSpaces.charAt(0).toUpperCase() + withSpaces.slice(1);
}

function create_setting(name, param, gameSettings)
{
const buttons_array = [];
const settings = document.createElement("div");
settings.classList.add("box");
const title = document.createElement("div");
title.classList.add("title_game_setting");
title.textContent = set_title_game_settings(name); 
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
        gameSettings[name] =  0.6 + (i *0.1);
      else
        gameSettings[name] =  i + 1;
      for (let j = 0; j < buttons_array.length; j++) {
        if (i != j) buttons_array[j].style.backgroundColor = 'rgba(223, 215, 215, 0.8)';
      }
    });
}
return (settings);
}

function getPlayerInputIds() {
const container = document.getElementById("player_name");
const inputs = container.querySelectorAll("input");
const ids = [];

inputs.forEach(input => {
  ids.push(input.value);
});

return ids;
}


export function render_settings()
{
  const gameSettings = {
      "paddle_size": 0,
      "number_of_player": 0,
      "ball_speed": 0,
      "view": 0,
      "score_to_win": 3,
      "player1": "player1",
      "player2": "AI",
      "local":1
  };
  const gs = document.createElement("div");
  gs.id = "game_settings";
  const title = document.createElement("h1");
  title.textContent = "Game Settings";
  const player_name = document.createElement("div");
  player_name.id = "player_name";
  player_name.classList.add("box");
  gs.appendChild(title);
  gs.appendChild(create_setting("paddle_size", ["Little", "Medium", "Big"], gameSettings));
  gs.appendChild(create_setting("ball_speed", ["Slow", "Normal", "Fast"], gameSettings));
  gs.appendChild(create_setting("view", ["2D", "3D"], gameSettings));
  gs.appendChild(create_score_to_win(gameSettings));
  gs.appendChild(create_number_of_player(["1p", "2p"], gameSettings, player_name));
  gs.appendChild(player_name);
  const play_button = create_settings_button("Play");
  gs.appendChild(play_button);
  play_button.addEventListener("click", async () =>
  {
    let ids = getPlayerInputIds();
  if (ids.length ) {
      gameSettings["player2"] = ids[0]; 
  }
      const allSettingsValid = Object.values(gameSettings).every(value => value !== 0 && value !== "");
      if (allSettingsValid)
      {
          const reponse = await postRequest("/create_local_game/", gameSettings);
          if(reponse != null)
              navigate_to("/game");
          else 
            navigate_to("/home");
      }
  });
  return (gs);
}
