import { navigate_to } from "../main.js";

const postRequest = async (endpoint, data, token = "") => {
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

        const result = await response.json();
        if (!response.ok) {
            return { error: true, status: response.status, message: result };
        }

        return { error: false, data: result };

    } catch (error) {
        console.error("Network error:", error);
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

export function render_sign_up()
{
    const auth = document.createElement("div");
    auth.id = "auth";
    const title = document.createElement("h1");
    title.textContent = 'Welcome to Transcendence';
    auth.appendChild(title);

    const sign_up = document.createElement("div");
    sign_up.id = "sign_in";

    const username = create_input_field("username",'texte',"Username",15);
    const email = create_input_field("email",'texte',"Email",200);
    const pswd = create_input_field("pswd",'password',"Password",30);
    const sign_up_button = document.createElement("div");
    sign_up_button.id = "sign_in_button";
    sign_up_button.textContent = "Create account";

    const errorMessage = document.createElement("div");
    errorMessage.classList.add("error_message");
    sign_up.appendChild(errorMessage);

    sign_up_button.addEventListener('click', async () =>
    {
        errorMessage.style.display = "none";
        if (username.firstChild.value != "" && pswd.firstChild.value != "" && email.firstChild.value != "")
        {
            const reponse = await postRequest("/sign-in/", { username:username.firstChild.value ,email:email.firstChild.value, password: pswd.firstChild.value }, "no_token");

            if (reponse.error) {
                let errorText = "Unknown error";
            
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
            else {
                navigate_to("/auth");
            }

       }
    });
    
    sign_up.appendChild(username);
    sign_up.appendChild(email);
    sign_up.appendChild(pswd);
    sign_up.appendChild(sign_up_button);

    auth.appendChild(sign_up);

    const sign_in = document.createElement("div");
    sign_in.id = "sign_up";
    const message = document.createElement("span");
    message.textContent = "Have an account ? ";sign_up_button
    
    const signInLink = document.createElement("a");
    signInLink.href = "/auth";
    signInLink.textContent = "Login";
    signInLink.style.color = 'rgb(59, 86, 175)';
    signInLink.setAttribute("data-link", '');

    sign_in.appendChild(message);
    sign_in.appendChild(signInLink);
    auth.appendChild(sign_in);
    return (auth);
}
