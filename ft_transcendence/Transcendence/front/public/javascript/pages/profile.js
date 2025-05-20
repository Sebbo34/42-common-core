import { navigate_to, setUserStatus, closeAllSockets } from "../main.js"
import { getFirst, setFirst } from './chat.js';
function closeChatLogout() {
	const chat = document.getElementById("chat");
	const open_container = document.getElementById("open_container");
	const messages = document.getElementById("messages");
	const notif_chat = document.getElementById("notif_chat");

	closeAllSockets();
	setFirst(0);
	if (chat && open_container && messages && notif_chat) {
		notif_chat.textContent = "0";
		messages.textContent = "";
		chat.style.display = "none";
		open_container.style.display = "block";
	}
}

export async function	render_profile() {

	const	container = document.createElement("div");
	container.id = "profile-container";
	container.classList.add("container", "mt-4");

	const	profile_top = document.createElement("div");
	profile_top.id = "profile-top";

	const	avatar = document.createElement("img");
	avatar.id = "avatar";
	avatar.alt = "User Profile Picture";
	avatar.classList.add("img-fluid", "avatar");
	profile_top.appendChild(avatar);

	const	infos_section = document.createElement("section");
	infos_section.id = "infos-section";

	const	create_infosP = (id) => {
		const	p = document.createElement("p");
		p.id = id;
		p.classList.add("profile-txt");
		return (p);
	};

	const	username = create_infosP("username");
	const	email = create_infosP("email");

	infos_section.append(username, email);
	profile_top.appendChild(infos_section);
	container.appendChild(profile_top);

	let	user_data_edit = null;
	try {
		const	user_data = await get_user_profile();
		
		if (!user_data)
			console.log("No user data found");
		else {
			user_data_edit = user_data;
			username.textContent = `Username: ${user_data.username}`;
			if (user_data.email) {
				email.textContent = `Email: ${user_data.email}`;
			}
			else {
				email.textContent = "Email: No email for 42 users."
			}
			avatar.src = `${user_data.avatar}`;
		}
	} catch (error) {
		console.error("Error fetching user data: ", error);
		container.textContent = "Failed to load user data.";
		return (container);
	}

	const	profile_buttons = document.createElement("div");
	profile_buttons.id = "profile-buttons";

	function	create_wrapper_button(button) {
		const	wrapper = document.createElement("div");
		wrapper.classList.add("container-profile-btn");
		wrapper.appendChild(button);
		return (wrapper);
	}

	function	hide_buttons() {
		const	profile_btn = document.getElementById("profile-buttons");
		const	all_btn = profile_btn.querySelectorAll("button");

		all_btn.forEach(button => {
			button.style.display = "none";
		});
	}
	// bouton update
	const	update_profile_btn = document.createElement("button");
	update_profile_btn.id = "update-profile-button";
	update_profile_btn.classList.add("btn", "profile-btn");
	update_profile_btn.textContent = "Update Profile";
	update_profile_btn.addEventListener("click", () => {
		const	profileContainer = document.getElementById("profile-container");
		profileContainer.classList.add("update-mode");

		hide_buttons();
		edit_profile(user_data_edit, infos_section);
	});
	profile_buttons.appendChild(create_wrapper_button(update_profile_btn));
	// bouton dashboard
	const	dashboard_btn = document.createElement("button");
	dashboard_btn.id = "dashboard-button";
	dashboard_btn.classList.add("btn", "profile-btn");
	dashboard_btn.textContent = "Dashboard";

	let	game_history = [];
	load_user_history()
		.then((history) => {
			game_history = history;
		})
		.catch((error) => {
			console.error("Error loading user game history: ", error);
		});
	dashboard_btn.addEventListener("click", () => {
		if (game_history.length === 0) {
			alert("Need to play at least 1 game to access dashboard.\n You will be redirected to Pong page game");
			navigate_to("/pong");
		}
		else
			navigate_to("/dashboard");
	});
	// logout
	const	logout_btn = document.createElement("button");
	logout_btn.id = "logout-button";
	logout_btn.classList.add("btn", "profile-btn");
	logout_btn.textContent = "Logout";
	logout_btn.addEventListener("click", async () => {
		localStorage.removeItem("access_token");
		try {
			const	response = await fetch('/api/logout/', {
				method: 'POST',
				credentials: 'include'
			});
			if (response.ok)
			{
				setUserStatus(false);
				closeChatLogout();
				navigate_to("/home");
			}
		} catch (error) {
			console.error("Error: logout resquest failed: ", error);
		}
	});
	profile_buttons.appendChild(create_wrapper_button(update_profile_btn));
	profile_buttons.appendChild(create_wrapper_button(dashboard_btn));
	profile_buttons.appendChild(create_wrapper_button(logout_btn));
	container.appendChild(profile_buttons);
	return (container);
}

export async function	get_user_profile() {

	try {
		const	token = localStorage.getItem('access_token');

		const	headers = {
			'Content-Type': 'application/json'
		};
		if (token)
			headers['Authorization'] = `Bearer ${token}`;
		const	response = await fetch('/api/user-profil/', {
			method: 'GET',
			credentials: 'include',
			headers,
		});
		if (!response.ok) {
			const	err_msg = await response.text();
			throw new Error(`Error fetching user data: ${response.statusText} - ${err_msg}`);
		}
		return await (response.json());
	} catch (error) {
		console.error("Failed to load user data: ", error);
		throw error;
	}
}

export async function edit_profile(data_edit, infos_section) {
	// Clear previous content
	infos_section.textContent = "";

	// USERNAME
	// Create label for username field
	const username_label = document.createElement("label");
	username_label.setAttribute("for", "usr_input");
	username_label.textContent = "Username: ";
	// Create input field for username
	const usr_input = document.createElement("input");
	usr_input.setAttribute("type", "text");
	usr_input.setAttribute("class", "edit-input");
	usr_input.setAttribute("id", "usr_input");
	usr_input.setAttribute("value", data_edit.username);
	usr_input.setAttribute("maxlength", 15);

	// EMAIL
	// Create label for email field
	const email_label = document.createElement("label");
	email_label.setAttribute("for", "email_input");
	email_label.textContent = "Email: ";
	// Create input field for email
	let email_input;
	if (data_edit.email !== null && data_edit.email !== undefined) {
		// Classic case : editable email
		email_input = document.createElement("input");
		email_input.setAttribute("type", "email");
		email_input.setAttribute("class", "edit-input");
		email_input.setAttribute("id", "email_input");
		email_input.setAttribute("value", data_edit.email);
		email_input.setAttribute("maxlength", 200);
	} 
	else {
		// Email null : desactivated field
		email_input = document.createElement("input");
		email_input.setAttribute("type", "text");
		email_input.setAttribute("class", "edit-input");
		email_input.setAttribute("id", "email_input");
		email_input.setAttribute("value", "Email unavailable");
		email_input.setAttribute("disabled", "true");
		email_input.style.color = "gray";
	}

	// AVATAR
	// Create label for avatar field
	const avatar_label = document.createElement("label");
	avatar_label.setAttribute("for", "avatar_input");
	avatar_label.textContent = "Avatar: ";
	// Create input field Avatar
	const avatar_input = document.createElement("input");
	avatar_input.setAttribute("type", "file");
	avatar_input.setAttribute("id", "avatar_input");
	avatar_input.setAttribute("accept", "image/*");
	avatar_input.classList.add("edit-input");
	// To display file name
	const file_preview = document.createElement("span");
	file_preview.setAttribute("id", "file-preview");

	// Create container for avatar
	const avatar_div = document.createElement("div");
	avatar_div.appendChild(avatar_label);
	avatar_div.appendChild(avatar_input);
	avatar_div.appendChild(file_preview);

	// Retrieve and display file name
	avatar_input.addEventListener("change", (event) => {
		const fileName = event.target.files[0]?.name || "No file chosen";
		file_preview.textContent = `Selected file: ${fileName}`;
	});

	// Create save button
	const save_button = document.createElement("button");
	save_button.setAttribute("id", "save-button-edit");
	save_button.classList.add("btn", "profile-button");
	save_button.textContent = "save edit";

	// Create return button
	const previous_button = document.createElement("button");
	previous_button.setAttribute("id", "previous-button");
	previous_button.classList.add("btn", "profile-button");
	previous_button.textContent = "return";

	// Create container for buttons
	const button_container = document.createElement("div");
	button_container.setAttribute("id", "button-container");
	button_container.appendChild(save_button);
	button_container.appendChild(previous_button);

	// Add elements to the section
	infos_section.appendChild(username_label);
	infos_section.appendChild(usr_input);
	infos_section.appendChild(email_label);
	infos_section.appendChild(email_input);
	infos_section.appendChild(avatar_div);
	infos_section.appendChild(button_container);

	// Handle the return button click
	previous_button.addEventListener("click", () => {
		navigate_to("/profile");
	});

	// Handle the save button click
	save_button.addEventListener("click", async (event) => {
		event.preventDefault();

		// Retrieve new username and email, and update objects
		const update_username = usr_input.value;
		const update_email = email_input.value;
		data_edit.username = update_username;
		data_edit.email = update_email;

		// Send modified data and avatar to backend
		await save_edit_profil(data_edit);
		const avatar_file = avatar_input.files[0];
		if (avatar_file) await save_new_avatar(avatar_file);

		navigate_to("/profile");
	});
}

export async function	save_edit_profil(user_data) {

	try {
		const	formData = new FormData();

		if (user_data.username)
			formData.append("username", user_data.username);
		if (user_data.email)
			formData.append("email", user_data.email)
		if (user_data.avatar instanceof File)
			formData.append("avatar", user_data.avatar);

		const	response = await fetch("/api/update-profil/", {
			method: 'PUT',
			credentials: 'include',
			body: formData
		});
		if (!response.ok) {
			const error_msg = await response.json();
			console.error("Server response:", error_msg);
			throw new Error(`Error: ${response.status}`);
		}
		const	res = await response.json();
		console.log("update-profile response: ", res.message);

		return (res);
	} catch (error) {
		console.error(`Error updating profile: `, error.message);
		alert("Error while updating profile. Try again.");
	}
}

function	validate_avatar(file) {

	const	max_size = 2;
	const	allowed_types = ["image/jpeg", "image/jpg", "image/png", "image/gif"];

	if (!file)
		return {valid: false, message: "No file selected."};
	if (!allowed_types.includes(file.type))
		return {valid: false, message: "Invalid file type: only jpeg, jpg, png and gif allowed."};
	if (file.size > max_size * 1024 * 1024)
		return {valid: false, message: `File too large: max size allowed is ${max_size}MB.`};
	return {valid: true};
}

export async function	save_new_avatar(avatar_file) {

	const	validation = validate_avatar(avatar_file);

	if (!validation.valid) {
		alert(validation.message);
		return;
	}
	try {
		const	formData = new FormData();
		formData.append("avatar", avatar_file);

		const	response = await fetch("/api/update-profil/", {
			method: 'PUT',
			credentials: 'include',
			body: formData
		});
		if (!response.ok) {
			const	error_msg = await response.json();
			console.error("Server response: ", error_msg);
			throw new Error(`Error: ${response.status}`);
		}
		const	res = await response.json();
		console.log("Avatar successfully updated: ", res.avatar);
		return (res);
	} catch (error) {
		console.error("Error updating user avatar: ", error);
		alert("Error while updating user avatar.");
	}
}

export async function	load_user_history() {

	try {
		const	accessToken = localStorage.getItem("accessToken") || "";
		const	headers = {
			"Authorization": "Bearer" + accessToken,
			"Content-Type" : "application/json"
		};
		const	response = await fetch("/api/match-history/", {
			method: 'GET',
			headers: headers
		});
		if (!response.ok) {
			const	error_msg = await response.json();
			console.error("Error server: ", error_msg);
			throw new Error(error_msg.error);
		}
		const	game_history = await response.json();
		return (game_history);
	} catch (error) {
		console.error("Error: failed to load user history game", error);
		throw error;
	}
}
