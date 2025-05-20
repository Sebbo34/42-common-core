import { getRequest } from "../main.js";

export async function	render_friends() {
	const	container = document.createElement("div");
	container.className = "friends-page";

	const	title = document.createElement("h1");
	title.textContent = "";
	container.appendChild(title);

	const	addFriendSection = document.createElement("div");
	addFriendSection.className = "add-friend-section";

	const	addFriendTitle = document.createElement("h2");
	addFriendTitle.textContent = "Search for a user:";
	addFriendSection.appendChild(addFriendTitle);

	const	form = document.createElement("form");
	form.className = "add-friend-form";

	const	label = document.createElement("label");
	label.textContent = "";
	label.htmlFor = "friendName";

	const	input = document.createElement("input");
	input.type = "text";
	input.id = "friendName";
	input.name = "friendName";
	input.maxLength = 15;

	const	button = document.createElement("button");
	button.type = "submit";
	button.textContent = "Add";

	button.addEventListener("click", async (event) => {
		event.preventDefault();
		const	friendName = input.value;
		if (!friendName) {
			alert("Please enter a name.");
			return;
		}
		try {
			const	response = await fetch("/api/add-friend/", {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				credentials: "include",
				body: JSON.stringify({ friend_to_add: friendName }),
			});
			const	data = await response.json();
			alert(data.message);
			if (response.ok)
				updateFriendsList(container);
		} catch (error) {
			console.error("Error adding a user: ", error);
		}
	});
	form.append(label, input, button);
	addFriendSection.appendChild(form);
	container.appendChild(addFriendSection);

	const	friendsListSection = document.createElement("div");
	friendsListSection.className = "friends-list-section";

	const	friendsListTitle = document.createElement("h2");
	friendsListTitle.textContent = "Friends List";
	friendsListSection.appendChild(friendsListTitle);

	const	friendsListContainer = document.createElement("div");
	friendsListContainer.className = "friends-list-container scrollable-box";
	friendsListSection.appendChild(friendsListContainer);
	container.appendChild(friendsListSection);

	await updateFriendsList(container);

	return (container);
}

async function	updateFriendsList(container) {
	const	friendsListContainer = container.querySelector(".friends-list-container");
	friendsListContainer.textContent = "";

	try {
		const	response = await getRequest("friend-list/");
		if (!response?.friends) {
			friendsListContainer.textContent = ``;
			return;
		}
		response.friends.forEach((friend) => {
			const	friendItem = document.createElement("div");
			friendItem.className = "friend-item";

			const	avatar = document.createElement("img");
			avatar.src = friend.avatar;
			avatar.alt = `${friend.username} avatar`;

			const	name = document.createElement("p");
			name.textContent = friend.username;

			const	status = document.createElement("p");
			status.textContent = friend.is_online ? "Online" : "Offline";
			status.className = `friend-status ${friend.is_online ? "online" : "offline"}`;

			const	matchHistoryBtn = document.createElement("button");
			matchHistoryBtn.textContent = "History";
			matchHistoryBtn.className = "btn btn-primary";

			const	removeBtn = document.createElement("button");
			removeBtn.textContent = "Delete";
			removeBtn.className = "btn btn-danger";
			removeBtn.style.display = "";

			removeBtn.addEventListener("click", async () => {
				if (!confirm(`Do you really want to delete ${friend.username} ?`)) return;
				try {
					const	res = await fetch("/api/remove-friend/", {
						method: "POST",
						headers: { "Content-Type": "application/json" },
						credentials: "include",
						body: JSON.stringify({ friend_to_remove: friend.username }),
					});
					const	data = await res.json();
					alert(data.message);
					if (res.ok)
						updateFriendsList(container);
				} catch (err) {
					console.error("Error deleting friend user: ", err);
					alert("Error deleting user.");
				}
			});
			const	actions = document.createElement("div");
			actions.className = "action-buttons";
			actions.append(removeBtn);

			friendItem.append(avatar, name, status, matchHistoryBtn, actions);
			friendsListContainer.appendChild(friendItem);

			matchHistoryBtn.addEventListener("click", async () => {
				const	listContainer = container.querySelector(".friends-list-container");
				const	isOpen = listContainer.classList.contains("history-open");

				if (isOpen) {
					const	existingHistory = friendItem.querySelector(".match-history");
					if (existingHistory)
						existingHistory.remove();

					listContainer.classList.remove("history-open");
					friendItem.classList.remove("active");

					removeBtn.style.display = "";

					container.querySelectorAll(".btn-primary").forEach(btn => btn.disabled = false);
					return;
				}
				listContainer.classList.add("history-open");
				friendItem.classList.add("active");

				removeBtn.style.display = "none";

				container.querySelectorAll(".btn-primary").forEach(btn => {
					if (btn !== matchHistoryBtn) btn.disabled = true;
				});
				try {
					await fetchMatchHistory(friend.username, friendItem);
				} catch {
					listContainer.classList.remove("history-open");
					friendItem.classList.remove("active");
					removeBtn.style.display = "";
					container.querySelectorAll(".btn-primary").forEach(btn => btn.disabled = false);
				}
			});
		});
	} catch (error) {
		console.error("Error getting friends list: ", error);
	}
}

async function	fetchMatchHistory(friendName, friendItem) {
	try {
		const	response = 
		await fetch(`/api/match-history/?friend_name=${encodeURIComponent(friendName)}`, {
				method: "GET",
				headers: { "Content-Type": "application/json" },
				credentials: "include",
			}
		);
		if (!response.ok)
			throw new Error("Error getting user history matches.");

		const	matchHistory = await response.json();
		const	historyContainer = document.createElement("div");
		historyContainer.className = "match-history";

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
