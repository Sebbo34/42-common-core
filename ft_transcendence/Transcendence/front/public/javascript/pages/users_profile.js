import { getGlobalUser } from "../main.js";

const getRequest = async (endpoint, data) => {
    try {
        const response = await fetch(`/api/${endpoint}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
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

export async function render_users_profile(usernameTarget = getGlobalUser()) {
	const container = document.createElement("div");
	container.id = "users-profile-container";
	container.classList.add("container", "mt-4");

	const profileTop = document.createElement("div");
	profileTop.id = "profile-top";

	const avatar = document.createElement("img");
	avatar.id = "avatar";
	avatar.alt = `${usernameTarget}'s Profile Picture`;
	avatar.classList.add("img-fluid", "avatar");

	avatar.style.cursor = "pointer";
	avatar.title = "Return";
	avatar.addEventListener("click", () => {
		window.history.back();
	});
	profileTop.appendChild(avatar);

	const infosSection = document.createElement("section");
	infosSection.id = "infos-section";

	const username = document.createElement("p");
	username.id = "username";
	username.classList.add("profile-txt");

	infosSection.append(username);
	profileTop.appendChild(infosSection);
	container.appendChild(profileTop);

	const historyContainer = document.createElement("div");
	historyContainer.className = "users-match-history";
	container.appendChild(historyContainer);

	try {
		const user_data = await getRequest("user-profil/", {"friend_name":getGlobalUser()});
		if (!user_data) throw new Error("No user data returned");
		username.textContent = `Username: ${user_data.username}`;
		avatar.src = `${user_data.avatar}`;

		await fetchMatchHistory(usernameTarget, historyContainer);
	} catch (err) {
		console.error("Failed to load user profile:", err);
		container.textContent = "Error loading profile.";
	}

	return container;
}

async function	fetchMatchHistory(friendName, friendItem) {
	try {
		const	response = await getRequest("match-history/", {"friend_name":getGlobalUser()});
		if (!response)
			throw new Error("Error getting user history matches.");

		const	matchHistory = response;
		const	historyContainer = document.createElement("div");
		historyContainer.className = "users-match-history";

		const	historyTitle = document.createElement("p");
		historyTitle.textContent = `Game History of ${friendName}`;
		historyContainer.appendChild(historyTitle);

		const	historyTable = document.createElement("table");
		historyTable.className = "table";

		const	thead = document.createElement("thead");
		const	headerRow = document.createElement("tr");
		["Date", "Rival", "User points", "Rival points"].forEach(text => {
			const	th = document.createElement("th");
			th.textContent = text;
			headerRow.appendChild(th);
		});
		thead.appendChild(headerRow);
		historyTable.appendChild(thead);

		const	tbody = document.createElement("tbody");
		matchHistory.forEach(match => {
			const	row = document.createElement("tr");

			const	dateCell = document.createElement("td");
			dateCell.textContent = new Date(match.date).toLocaleDateString();

			const normalizeName = name => name.trim().toLowerCase();
			const oppName = normalizeName(match.player1) === normalizeName(friendName)
				? match.player2
				: (normalizeName(match.player2) === normalizeName(friendName)
					? match.player1
					: "AI");			

			const	oppCell = document.createElement("td");
			oppCell.textContent = oppName;

			const	friendPoints = document.createElement("td");
			friendPoints.textContent =
				match.player1 === friendName ? match.player1_score : match.player2_score;

			const	oppPoints = document.createElement("td");
			oppPoints.textContent =
				match.player1 === friendName ? match.player2_score : match.player1_score;
				
			row.append(dateCell, oppCell, friendPoints, oppPoints);
			tbody.appendChild(row);
		});
		historyTable.appendChild(tbody);
		historyContainer.appendChild(historyTable);
		friendItem.appendChild(historyContainer);

	} catch (error) {
		console.error(`Error getting games history of ${friendName} :`, error);
	}
}
