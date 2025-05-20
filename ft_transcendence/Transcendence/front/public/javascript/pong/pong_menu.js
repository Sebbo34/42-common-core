import { navigate_to } from '../main.js';

function    create_gif(img, text) {

    const   gif = document.createElement("img");

    gif.src = img;
    gif.alt = `{text}`;
    gif.className = "gif-pong-menu";

    return (gif);
}

function    create_button_gif({id, text, img}) {

    const   button = document.createElement("button");

    button.id = id;
    button.className = "pong-menu-button";
    button.textContent = text;

    const   gif = create_gif(img, text);

    button.appendChild(gif);
    return (button);
}

function    create_div_menu(id, class_name) {

    const   div = document.createElement("div");

    if (id)
        div.id = id;
    if (class_name)
        div.className = class_name;
    return (div);
}

function    create_pong_menu() {

    const   menu = create_div_menu("pong-menu", "pong-menu");
    const   menu_buttons = create_div_menu("", "menu-buttons");
    const   buttons_data = [
        { id: "single-play-button", text: "LOCAL", img: "content/single.gif" },
        { id: "tournament-button", text: "TOURNAMENT", img: "content/tournament.gif" }
    ];
    let i = 0;
    buttons_data.forEach(buttons_data => {

        const   button = create_button_gif(buttons_data);
        if (i == 0)
        {
            button.addEventListener("click",() =>
                {
                    navigate_to("/game_settings");
                });
        }
        else if (i == 1)
            {
                button.addEventListener("click",() =>
                {
                    navigate_to("/tournament_lobby");
                });
            }
        i++;
        menu_buttons.appendChild(button);
    });
    menu.appendChild(menu_buttons);
    return (menu);
}

function    create_menu_container() {

    const   container = document.createElement("div");

    container.id = "pong-page";
    container.className = "container-fluid p-0";

    return (container);
}

export function render_pong() {

    const   container = create_menu_container();
    const   menu = create_pong_menu();

    container.appendChild(menu);
    return (container);
}
