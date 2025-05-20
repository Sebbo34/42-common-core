import { navigate_to, setGlobalUser } from "../main.js";

const getRequest = async (endpoint) => {
    try {
        const   response = await fetch(`/api/${endpoint}`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json'
            },
            credentials: 'include'
        });
        if (!response.ok) {
            throw new Error(`Error ${response.status}: ${await response.text()}`);
        }
        const   res = await response.json();
        console.log("Response: ", res);
        return (res);
    } catch (error) {
        console.error("Error fetching: ", error);
        return (null);
    }
};

function get_users(searchResult, users)
{
    if (users.length == 0)
        return;
    searchResult.style.display = "block";
    searchResult.textContent = "";
    for (let i = 0; i < users.length; i++) {
        let user = document.createElement("div");
        user.className = "users";

        user.addEventListener("click", () => {
            setGlobalUser(users[i].username);
            navigate_to("/users_profile");
        });

        const avatar = document.createElement("img");
		avatar.src = users[i].avatar.startsWith("http") 
			? users[i].avatar 
			: `/media/${users[i].avatar}`;
		avatar.alt = `${users[i].username}'s avatar`;
		avatar.className = "avatar-img user-avatar";
        avatar.style.cursor = "pointer";
		avatar.style.objectFit = "cover";

        const name = document.createElement("h7");
        name.className = "username";
        name.textContent = users[i].username;
    
        user.appendChild(avatar);
        user.appendChild(name);
        searchResult.appendChild(user);
    }    
}

export async function render_social() {

    const   container = document.createElement("div");

    container.id = "social-content";
    container.className = "container d-flex position-relative justify-content-center align-items-center";

    const   row_content = document.createElement("div");
    row_content.className = "d-flex flex-row position-relative align-items-center";

    const users = await getRequest("social/");
	if (users) {
        console.log(users);
        get_users(container,users);
	}
    document.getElementById("app").appendChild(container);
    document.body.classList.add("no-scroll");

    return (container);
}
