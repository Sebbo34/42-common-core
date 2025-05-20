import { navigate_to, setGlobalUser, getUserStatus, is_logged, getSocket, closeSocket } from "../main.js";

let domain_name = window.location.hostname;
let first = 0;

export function getFirst() {
  return first;
}

export function setFirst(value) {
  first = value;
}

const postRequest = async (endpoint, data) => {
    try {
        let head = {
                "Content-Type": "application/json",
            };
   

        const response = await fetch(`/api/${endpoint}`, {
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

function createMenuItem(menu,socket, label, action,sender) { 
    const item = document.createElement("div");
    item.className = "menu-item";
    item.textContent = label;
    item.onclick = () => menuAction(socket, menu, action,sender);
    return item;
}

function createCustomAlert(socket, message, target) {
    // Overlay
    let buttons;
    let cancelBtn;
    let okBtn;
    const overlay = document.createElement('div');
    overlay.className = 'alert-overlay';

    // Box
    const box = document.createElement('div');
    box.className = 'alert-box';

    // Message
    const text = document.createElement('p');
    text.id = 'alert-message';
    text.textContent = message;
    const progress = document.createElement('div');
    progress.className = 'progress-bar';
    box.appendChild(text);
    if (message != "Waiting")
    {
        buttons = document.createElement('div');
        buttons.className = 'alert-buttons';
    
        okBtn = create_settings_button('Ready');
        okBtn.onclick = async () => {
          document.body.removeChild(overlay);
          const rep = await postRequest("/create_game_without_lobby/", {target:target});
          socket.send(JSON.stringify({type:"is_ready", target:target}));
          navigate_to("/gs_invite");
        };
    
        cancelBtn = create_settings_button('Cancel');
        cancelBtn.onclick = () => {
            socket.send(JSON.stringify({type:"send_cancel", target:target}));
          document.body.removeChild(overlay);
          buttons.appendChild(okBtn);
          buttons.appendChild(cancelBtn);
        };
        buttons.appendChild(okBtn);
        buttons.appendChild(cancelBtn);
        box.appendChild(buttons);
    }

    box.appendChild(progress);

    overlay.appendChild(box);
    document.body.appendChild(overlay);
    const autoClose = setTimeout(() => {
        if (document.body.contains(overlay)) {
          document.body.removeChild(overlay);
        }
      }, 10000); 
    return overlay;
}

function menuAction(socket, menu, action, target) {
    let tmp = {
        type:action,
        target:target};
    if (action == 'see_profile')
    {
        setGlobalUser(target);
        navigate_to("/users_profile");
        return
    }
    socket.send(JSON.stringify(tmp));
    menu.style.display = "none";
}

function add_invit(messages, sender, socket) {
    const messageContainer = document.createElement("div");
    messageContainer.className = "invitation-message";

    const senderLabel = document.createElement("div");
    senderLabel.className = "sender";
    senderLabel.textContent = sender + " invited you to play";

    const accept =create_settings_button("V");
    const reject =create_settings_button("X");
    accept.style.backgroundColor = "green";
    reject.style.backgroundColor = "red";
    accept.addEventListener("click", async ()=> {
        socket.send(JSON.stringify({type:"accept_invit", host:sender}));
        messageContainer.style.display = "none";
    });
    reject.addEventListener("click", async ()=> {
        socket.send(JSON.stringify({type:"reject_invit", host:sender}));
        messageContainer.style.display = "none";
    });
    messageContainer.appendChild(senderLabel);
    messageContainer.appendChild(accept);
    messageContainer.appendChild(reject);
    messages.appendChild(messageContainer);
    messages.scrollTop = messages.scrollHeight;
}

function add_message(socket, sender, messages, value, is_alert)
{
    const message = document.createElement("div");
    message.classList.add("message");

    const senderLabel = document.createElement("div");
    senderLabel.classList.add("sender");
    senderLabel.textContent = sender;
    message.appendChild(senderLabel);

    const messageText = document.createElement("div");
    messageText.classList.add("message-text");
    messageText.textContent = value;
    message.appendChild(messageText);

    const menu = document.createElement("div");
    menu.id = "contextMenu";
    menu.style.display = "none";
    menu.appendChild(createMenuItem(menu,socket,"Invite", "invite",sender));
    menu.appendChild(createMenuItem(menu,socket,"Block", "block",sender));
    menu.appendChild(createMenuItem(menu,socket,"See Profile", "see_profile",sender));
    if (is_alert == 0)
    {
        message.addEventListener("contextmenu", (event) => {
            event.preventDefault(); 
            event.stopPropagation();
            menu.style.display = "block";
            menu.style.left = `${event.pageX}px`;
            menu.style.top = `${event.pageY}px`;
        });   
    }
 
    document.body.appendChild(menu);
    document.addEventListener("click", () => {
        menu.style.display = "none";
    });
    messages.appendChild(message);
    messages.scrollTop = messages.scrollHeight;
}

export function render_chat()
{
    let number_notif = 0;
    let overlay;
    let msg = {
        type : 'send_message',
        message:''
    };
    const chat_container = document.createElement("div");
    chat_container.id = "chat_container";
    
    const chat = document.createElement("div");
    chat.id = "chat";
    
    const open = create_settings_button("Chat General");
    open.id = "open";
    open.style.backgroundColor = "rgba(223, 183, 183, 0.2)";
    open.style.borderBlockColor = "rgba(180, 189, 201, 0.2)";
    open.style.border = "2px solid transparent";
    open.style.position = "relative";
    
    const notif = document.createElement("div");
    notif.id = "notif_chat";
    notif.textContent = number_notif.toString();
    
    const open_container = document.createElement("div");
    open_container.id = "open_container";
    open_container.appendChild(notif);
    open_container.appendChild(open);
    
    chat_container.appendChild(open_container);
    chat_container.appendChild(chat);

    const title = document.createElement("h1");
    title.textContent = 'Chat general';
    title.id = "close_chat";
    title.addEventListener("click",()=>{
        open_container.style.display = "block";
        chat.style.display = "none";
        number_notif = 0;
        notif.textContent = number_notif.toString();
    });
    chat.appendChild(title);

    const messages = document.createElement("div");
    messages.id = "messages";
    chat.appendChild(messages);

    const input_box = document.createElement("div");
    input_box.id = "input_box";
    input_box.placeholder = "Write a message...";

    let input = document.createElement("input");
    input.type = "text";
    input.id = "messageInput";
    input.placeholder = "Write a message...";

    input.maxLength = 300;
    input.addEventListener("input", () => {
        if (input.value.length === 300) {
            console.log("Too many characters.");
        }
    });
    let socket;
    input_box.appendChild(input);
    const button = create_settings_button("Send");
    open.addEventListener("click", async()=>{
        await is_logged();
        if (!getUserStatus()) {
            alert("You must be logged in to use the live chat.");
            return;
        }
        number_notif = 0;
        notif.textContent = number_notif.toString();
        if (getFirst() == 1)
        {
            open_container.style.display = "none";
            chat.style.display = "block";
        }
        socket = getSocket("", "chat");
        if (socket && getFirst() == 0)
        {
            setFirst(1);
            socket.onopen = () => {
                    console.log('Connecté au serveur WebSocket');
            };
        socket.addEventListener('message',async  (event) => {
            await is_logged();
            if (!getUserStatus()) {
                closeSocket("chat");
                alert("You must be logged in to use the live chat.");
                return;
            }
            const data = JSON.parse(event.data);
            if (open_container.style.display == 'block' || getFirst() == 1)
                number_notif += 1;
            notif.textContent = number_notif.toString();
            if (data["type"] == 'chat_message')
            {
                add_message(socket, data.sender, messages, data.message, 0);
            }
            if (data["type"] == 'send_invit')
            {
                add_invit( messages, data.sender, socket);
            }
            if (data["type"] == 'send_rejection')
            {
                add_message( socket,"Alert", messages, data.sender + " reject your invitation", 1);
            }
            if (data["type"] == 'send_acceptation')
            {
                if (window.location.pathname != "/game" && window.location.pathname != "/gs_invite")
                    createCustomAlert(socket, data["sender"] + " accept your invitation!",data["sender"]);
            }
            if (data["type"] == 'start_play')
            {
                if (overlay)
                    document.body.removeChild(overlay);
               navigate_to("/gs_invite");
            }
            if (data["type"] == 'cancel_invitation')
            {
                document.body.removeChild(overlay);
            }
            if (data["type"] == 'set_waiting')
            {                
                if (window.location.pathname != "/game" && window.location.pathname != "/gs_invite")
                    overlay = createCustomAlert(socket, "Waiting");
            }
            if (data["type"] == 'block')
                add_message( socket, "Alert", messages, "you block " +  data.sender, 1);
            if (data["type"] == 'Tournament_alert')
                add_message( socket, "Alert", messages, "Get ready to play a tournament game!", 1);
    
        });
    
        socket.onclose = () => {
            console.log('Déconnecté du serveur WebSocket');
        };

        button.addEventListener("click",() => {
            if (input.value.length > 0) {
                msg.message = input.value;
                socket.send(JSON.stringify(msg));
                input.value = ''; 
            }
        });
        input.addEventListener("keydown", (event) => {
            if (event.key === "Enter") { 
                if (input.value.length > 0) {
                    msg.message = input.value;
                    socket.send(JSON.stringify(msg));
                    input.value = ''; 
                }
            }
        });   
    }
    });
    input_box.appendChild(button);
    chat.appendChild(input_box);
    chat.style.display = "none";
    document.body.appendChild(chat_container);
    return (chat_container);
}
