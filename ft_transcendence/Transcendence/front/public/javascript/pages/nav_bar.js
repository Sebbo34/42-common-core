import { getUserStatus } from "../main.js";

export function create_nav_bar() {

    const   nav = document.createElement("nav");
    nav.id = "main-navbar";
    nav.className = "navbar navbar-expand-lg navbar-fixed-top py-2";

    const   container = document.createElement("div");
    container.className = "container d-flex justify-content-center align-items-center";

    const   nav_list = document.createElement("ul");
    nav_list.className = "navbar-nav d-flex flex-row justify-content-between";

    const   nav_items = [
        { href: '/home', text: "HOME"},
        { href: '/pong', text: "PONG"},
        { href: '/profile', text: "PROFILE"},
        { href: '/friends', text: "FRIENDS"},
        { href: '/social', text: "SOCIAL"}
    ];

    if (!getUserStatus()) {
        nav_items.push({ href: '/auth', text: 'SIGN IN/SIGN UP'});
    }
    nav_items.forEach(item => {

        const   li = document.createElement("li");
        li.className = "nav-items";

        const   a = document.createElement("a");
        a.href = item.href;
        a.setAttribute("data-link", "");
        a.className = "nav-link me-3";
        a.textContent = item.text;

        li.appendChild(a);
        nav_list.appendChild(li);
    });
    container.appendChild(nav_list);
    nav.appendChild(container);
    return (nav);
}

export function render_nav_bar() {
    const   nav_bar = create_nav_bar();
    document.body.insertAdjacentElement("afterbegin", nav_bar);
}
