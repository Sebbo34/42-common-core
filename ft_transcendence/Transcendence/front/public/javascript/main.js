import { render_footer  } from "./pages/footer.js";
import { render_home  } from "./pages/home.js";
import { render_nav_bar } from "./pages/nav_bar.js";
import { render_profile } from "./pages/profile.js";
import { render_pong  } from "./pong/pong_menu.js";
import { render_game  } from "./pong/game.js";
import { render_settings  } from "./pong/game_settings.js";
import { render_auth  } from "./pages/auth.js";
import { render_code  } from "./pages/code.js";
import { render_sign_up } from "./pages/sign_up.js";
import { render_dashboard  } from "./pages/dashboard.js";
import { render_404 } from "./pages/page_404.js";
import { render_tournament_lobby  } from "./pages/tournament_lobby.js";
import { render_chat  } from "./pages/chat.js";
import { render_gs_invite  } from "./pong/game_settings_invite.js";
import { render_social  } from "./pages/social.js";
import { render_friends } from "./pages/friends.js";
import { render_users_profile } from "./pages/users_profile.js";

let domainName = window.location.hostname;

let isUserLog = false;

export function setUserStatus(status) {
    isUserLog = status;
    update_navBar();
}

export function getUserStatus() {
    return (isUserLog);
}

let globalUser = null;

export function setGlobalUser(status) {
    globalUser = status;
}

export function getGlobalUser() {
    return (globalUser);
}

const sockets = {};

export function getSocket(url,path) {
    if (!sockets[path] || sockets[path].readyState > 1) {
        sockets[path] = new WebSocket(url);
        if (path == "chat")
        {
            const open = document.getElementById("open");
            if (open) {
              open.click();
            }
        }
    }
    return sockets[path];
}

export function closeSocket(path) {
    if (sockets[path]) {
        sockets[path].close();
        delete sockets[path];
    }
}

export function closeAllSockets() {
    Object.values(sockets).forEach(sock => sock.close());
    Object.keys(sockets).forEach(key => delete sockets[key]);
}


export const getRequest = async (endpoint) => {
    try {
        const response = await fetch(`/api/${endpoint}`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json'
            },
            credentials: 'include'
        });

        const res = await response.json();
            return res;
    }
    catch (error) {
            return null;
        }
};

export const is_logged = async () => {
    const response = await getRequest("my_infos/");
    if (response){
        if (response.username && response.is_online) {
                setUserStatus(true);
                let url = `wss://${domainName}:8443/api/ws/chat/`;
                getSocket(url, "chat"); 
                console.log('User is logged in:', getUserStatus());
        }
        else {

            setUserStatus(false);
            console.log('User is not logged in');
        }
    }
};

function    update_navBar() {
    const   old_nav = document.getElementById("main-navbar");
    if (old_nav)
        old_nav.remove();
    render_nav_bar();
}

const   restricted_routes = {
    '/pong': "You must be logged in to access Pong game.",
    '/profile': "You must be logged in to access your profile",
    '/dashboard': "You must be logged in to access your dashboard.",
    '/friends': "You must be logged in to access your friend's page",
    '/social': "You must be logged in to access the social page",
};

const   restrict_log = {
    '/auth': "You are already logged in.",
    '/code': "You are already logged in.",
    '/sign_up': "You are already logged in.",
};

const route_config = [

    { path: "", title: "Home", view: render_home },
    { path: "/home", title: "Home", view: render_home },
    { path: "/pong", title: "Pong Game", view: render_pong },
    { path: "/profile", title: "My Profile", view: render_profile},
    { path: "/social", title: "Social", view: render_social},
    { path: "/game", title: "Pong Game", view: render_game },
    { path: "/game_settings", title: "Game Settings", view: render_settings },
    { path: "/auth",title: "Auth", view: render_auth},
    { path: "/sign_up",title: "Sign Up", view: render_sign_up},
    { path: "/code",title: "Code", view: render_code},
    { path: "/dashboard", title: "Dashboard", view: render_dashboard },
    { path: "/tournament_lobby", title: "Tournament lobby", view: render_tournament_lobby },
    { path: "/gs_invite", title: "Game Settings", view: render_gs_invite },
    { path: "/friends", title: "Friends", view: render_friends },
    { path: "/users_profile", title: "Users Profile", view: render_users_profile },
];

const   clean_path = path => path.replace(/\/$/, "") || "/home";
const   find_route = path => route_config.find(r => r.path === path) || { path: '/404', title: 'Page Not Found', view: render_404 };

async function  update_view(route) {

    document.title = route.title;
    const   app = document.getElementById("app");

    try {
        const   content = await route.view();
        if (typeof content === "string")
            app.textContent = content;
        else {
            app.textContent = "";
            app.appendChild(content);
        }
    } catch (error) {
        console.log("❌ Error rendering view: ", error);
        app.innerHTML = "<p> Failed to load page <p>";
    }
}

export const    navigate_to = async (path, {pushHistory = true} = {}) => {
    
    const   cleaned = clean_path(path);

    await is_logged();
    if (!getUserStatus() && restricted_routes[cleaned]) {
        alert(restricted_routes[cleaned]);
        return (navigate_to("/sign_up"));
    }
    if (getUserStatus() && restrict_log[cleaned]) {
        alert(restrict_log[cleaned]);
        return (navigate_to("/home"));
    }
    const   route = find_route(cleaned);
    if (pushHistory)
        history.pushState(null, "", cleaned);
    document.title = route.title;
    console.log(`navigating to: ${path}`);
    if (path != "/game")
        {
            closeSocket("game");
        }
    if (path != "/tournament_lobby")
    {
        closeSocket("tournament");
    }
    if (path != "/gs_invite")
    {
        closeSocket("gs");
    }
    await update_view(route);
};

function    set_navigation() {
    document.body.addEventListener("click", async event => {
        const   link = event.target.closest("a[data-link]");

        if (!link)
            return;
        event.preventDefault();
        await navigate_to(link.getAttribute("href"), {pushHistory: true});
    });
    window.addEventListener("popstate", () => {
        navigate_to(window.location.pathname, {pushHistory: false});
    });
    navigate_to(window.location.pathname, {pushHistory: false});
}

window.addEventListener("DOMContentLoaded", () => {
    render_chat();
    update_navBar();
    render_footer();
    set_navigation();
});
