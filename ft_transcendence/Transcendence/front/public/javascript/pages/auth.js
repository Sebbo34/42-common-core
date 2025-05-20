import { navigate_to } from "../main.js";

const postRequest = async (endpoint, data, token = "") => {
    try {
        let head = {
                "Content-Type": "application/json",
            };
   
        const response = await fetch(`${endpoint}`, {
            method: "POST",
            headers: head,
            credentials: 'include',
            body: JSON.stringify(data)
        });

        const result = await response.json();

        if (!response.ok) {
            return { error: true, status: response.status, message: result };
        }
 
        return { error: false, data: result };
    } catch (error) {
        console.error("Erreur:", error);
        return { error: true, message: "A network error occurred" };
    }
};

function create_input_field( id, type, placeholder, maxLength) {
    const container = document.createElement("div");
    container.classList.add("input-container");

    const input = document.createElement("input");
    input.type = type;
    input.required = true;
    input.id = id;
    input.placeholder = placeholder;

    const label = document.createElement("label");
    label.setAttribute("for", id);
    label.innerText = placeholder;

    input.maxLength = maxLength;
    input.addEventListener("input", () => {
        if (input.value.length === maxLength) {
            console.log("Limite de caractères atteinte");
        }
    });

    container.appendChild(input);
    container.appendChild(label);

    return container;
}

export function render_auth()
{
    const auth = document.createElement("div");
    auth.id = "auth";
    const title = document.createElement("h1");
    title.textContent = 'Transcendence';
    auth.appendChild(title);

    const sign_in = document.createElement("div");
    sign_in.id = "sign_in";

    const username = create_input_field("username",'texte',"Username",15);
    const pswd = create_input_field("pswd",'password',"Password",30);
    const sign_in_button = document.createElement("div");
    sign_in_button.id = "sign_in_button";
    sign_in_button.textContent = "LOGIN";

    const errorMessage = document.createElement("div");
    errorMessage.classList.add("error_message");
    sign_in.appendChild(errorMessage);

    sign_in_button.addEventListener('click', async () =>
    {
        
        if (username.firstChild.value != "" && pswd.firstChild.value != "")
        {
            const reponse = await postRequest("/api/login/", { username:username.firstChild.value , password: pswd.firstChild.value }, "no_token");
            
            if (!reponse.error) {
                navigate_to("/code");
            } else {
                let errorText = "Invalid IDs";

                if (typeof reponse.message === "object") {
                    const firstKey = Object.keys(reponse.message)[0];
                    const firstMsg = reponse.message[firstKey];
                    if (Array.isArray(firstMsg)) {
                        errorText = firstMsg[0];
                    } else if (typeof firstMsg === "string") {
                        errorText = firstMsg;
                    }
                } else if (typeof reponse.message === "string") {
                    errorText = reponse.message;
                }
            
                errorMessage.textContent = errorText;
                errorMessage.style.display = "block";
            }
        }
    });
    
    sign_in.appendChild(username);
    sign_in.appendChild(pswd);
    sign_in.appendChild(sign_in_button);

    const or_title = document.createElement("div");
    or_title.id = "or_title";
    or_title.textContent = '-------- OR --------';

    const api42 = document.createElement("div");
    api42.id = "api42";
    
    const img42 = document.createElement("img");
    img42.src = "../../content/42.png";
    img42.alt = "42 API Logo";
    img42.style.width = "30px";
    img42.style.marginRight = "10px";
    
    const text42 = document.createElement("span");
    text42.innerText = "Sign up with 42";
    
    api42.appendChild(img42);
    api42.appendChild(text42);

    api42.addEventListener('click', async () => {
        window.location.href = `/api/login/42/`;
    });

    const sign_up = document.createElement("div");
    sign_up.id = "sign_up";
    const message = document.createElement("span");
    message.textContent = "Don't have an account ? ";
    
    const signUpLink = document.createElement("a");
    signUpLink.href = "/sign_up";
    signUpLink.textContent = "Sign up";
    signUpLink.style.color = 'rgb(59, 86, 175)';
    signUpLink.setAttribute("data-link", '');

    sign_up.appendChild(message);
    sign_up.appendChild(signUpLink);

    auth.appendChild(sign_in);
    auth.appendChild(or_title);
    auth.appendChild(api42);
    auth.appendChild(sign_up);

    return (auth);
}
