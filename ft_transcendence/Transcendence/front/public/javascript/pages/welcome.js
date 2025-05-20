import {create_elem_class, create_img, create_text}
from './create_function.js'

export function create_cat_flip() {

    const   col = create_elem_class("div", "mb-auto");
    const   card = create_elem_class("div", "card");
    const   panel = create_elem_class("div", "card-header d-flex justify-content-center");
    const   gif = create_img("content/home_cat_pong.gif", "pong cat gif", "img-fluid");

    gif.setAttribute("data-bs-toggle", "collapse");
    gif.setAttribute("data-bs-target", "#multi_collapse");
    gif.setAttribute("aria-expanded", "false");
    gif.setAttribute("aria-controls", "multi_collapse");
    gif.addEventListener("click", () => {
        gif.style.display = "none";
        collapse.classList.add("show");
    });
    panel.appendChild(gif);
    card.appendChild(panel);

    const   collapse = create_elem_class("div", "collapse");
    collapse.id = "multi_collapse";

    const   body_card = create_elem_class("div", "card-body card-cat");
    const   row = create_elem_class("div", "row");
    const   gif_col = create_elem_class("div", "col-md-6 d-flex justify-content-center align-items-center");
    const   second_gif = create_img("content/cat_2.gif", "pong cat gif 2", "img-fluid");

    second_gif.style.cursor = "pointer";
    second_gif.addEventListener("click", () => {
        collapse.classList.remove("show");
        gif.style.display = "block";
    });
    gif_col.appendChild(second_gif);

    const   text_col = create_elem_class("div", "col-md-6 d-flex flex-column justify-content-center align-items-center text-col");
    const   text = create_text(`Pong is one of the first computer games ever created, this "tennis like" game features two paddles and a ball.

        The goal is to defeat your opponent by scoring more points than your opponent.
        A player gets a point once the opponent misses a ball. The game can be played with two human players or one player against a computer controlled paddle.
        
        The game was originally developed by Allan Alcorn and released in 1972 by Atari corporations.
        Pong became a huge success and became the first commercially successful game.
        
        Today, the Pong Game is considered to be the game which started the video games industry.`);

    text_col.appendChild(text);
    row.appendChild(gif_col);
    row.appendChild(text_col);

    body_card.appendChild(row);
    collapse.appendChild(body_card);
    card.appendChild(collapse);
    col.appendChild(card);

    return (col);
}

