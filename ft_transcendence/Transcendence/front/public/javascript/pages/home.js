import {create_cat_flip}
from './welcome.js'

export function render_home() {

    const   container = document.createElement("div");

    container.id = "home-content";
    container.className = "container d-flex position-relative justify-content-center align-items-center";

    const   row_content = document.createElement("div");
    
    row_content.className = "d-flex flex-row position-relative align-items-center";
    row_content.appendChild(create_cat_flip());
    container.appendChild(row_content);

    document.getElementById("app").appendChild(container);
    document.body.classList.add("no-scroll");

    return (container);
}
