import { navigate_to, setUserStatus } from "../main.js";

const postRequest = async (endpoint, data) => {
    try {
        const response = await fetch(`/api${endpoint}`, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
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

function updateCodeValue(inputs) {
    const codeValue = inputs.map(input => input.value).join("");
    return(codeValue);
}

export function render_code()
{
    const auth = document.createElement("div");
    auth.id = "auth";
    const title = document.createElement("h1");
    title.textContent = 'Please enter your code :';
    auth.appendChild(title);


    const codeContainer = document.createElement("div");
    codeContainer.className = "code-container";
    
    const inputs = [];
    for (let i = 0; i < 6; i++) {
        const input = document.createElement("input");
        input.type = "text";
        input.className = "code-input";
        input.maxLength = 1;
        input.setAttribute("pattern", "[0-9]*");

        input.addEventListener("keydown", (e) => {
            if (!/^[0-9]$/.test(e.key) && e.key !== "Backspace") {
                e.preventDefault();
            }
        });

        input.addEventListener("input", (e) => {
            if (e.target.value.length === 1 && i < 5) {
                inputs[i + 1].focus();
            }
        });

        input.addEventListener("keydown", (e) => {
            if (e.key === "Backspace" && i > 0 && input.value === "") {
                inputs[i - 1].focus();
            }
        });

        inputs.push(input);
        codeContainer.appendChild(input);
    }
    const button = document.createElement("div");
    button.id = "code_button";
    button.textContent = "send";
    button.addEventListener('click', async () =>
    {
        const code = updateCodeValue(inputs);
        if (code.length == 6)
        {            
            const data = await postRequest("/code-2fa/", {code:code}); 
            if(!data)
            {
                navigate_to("/auth");
            }
            else
            {
                setUserStatus(true);
                navigate_to("/home");
            }
        }
    });
    auth.appendChild(codeContainer);
    auth.appendChild(button);
    return (auth);
}
