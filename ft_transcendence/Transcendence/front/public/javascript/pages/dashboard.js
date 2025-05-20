import { navigate_to } from "../main.js"

export async function	render_dashboard() {

	const	container = document.createElement("div");
	container.id = "dashboard-container";
	container.classList.add("container", "mt-2");

	const	button_wrapper = document.createElement("div");
	button_wrapper.id = "title-btn-wrapper";

	const	title = document.createElement("p");
	title.textContent = "STATISTICS";
	title.id = "stats-title";

	button_wrapper.appendChild(title);
	container.appendChild(button_wrapper);

	const	block_wrapper = document.createElement("div");
	block_wrapper.id = "dashboard-blocks-wrapper";

	const	stats_pie = document.createElement("div");
	stats_pie.id = "stats-pie-wrapper";

	const	stats_summary = document.createElement("div");
	stats_summary.id = "stats-summary";

	const	total_gameP = document.createElement("p");
	total_gameP.textContent = "Total matches: ";
	const	total_game_span = document.createElement("span");
	total_game_span.id = "total-games";
	total_game_span.textContent = "";
	total_gameP.appendChild(total_game_span);
	stats_summary.appendChild(total_gameP);

	const	win_gameP = document.createElement("p");
	win_gameP.textContent = "Wins: ";
	const	win_span = document.createElement("span");
	win_span.id = "wins";
	win_span.textContent = "";
	win_gameP.appendChild(win_span);
	stats_summary.appendChild(win_gameP);

	const	loss_gameP = document.createElement("p");
	loss_gameP.textContent = "Losses: ";
	const	loss_span = document.createElement("span");
	loss_span.id = "losses";
	loss_span.textContent = "";
	loss_gameP.appendChild(loss_span);
	stats_summary.appendChild(loss_gameP);

	const	pie_chart_container = document.createElement("div");
	pie_chart_container.id = "pie-chart-container";

	const	canvas = document.createElement("canvas");
	canvas.id = "res-chart"
	canvas.width = 350;
	canvas.height = 350;
	pie_chart_container.appendChild(canvas);

	stats_pie.appendChild(stats_summary);
	stats_pie.appendChild(pie_chart_container);

	// details
	const	detail_container = document.createElement("div");
	detail_container.id = "games-details-container";

	const	detail_title = document.createElement("p");
	detail_title.textContent = "Game Details";
	detail_title.id = "title-game-details"
	detail_container.appendChild(detail_title);

	const	table = document.createElement("table");
	table.id = "games-details";

	const	thead = document.createElement("thead");
	const	header_row = document.createElement("tr");
	const	headers = ["Date", "Opponent", "Your Points", "Opponent Points", "Results"];

	headers.forEach(text => {
		const	th = document.createElement("th");
		th.textContent = text;
		header_row.appendChild(th);
	});
	thead.appendChild(header_row);
	table.appendChild(thead);

	// table
	const	tbody = document.createElement("tbody");
	table.appendChild(tbody);
	detail_container.appendChild(table);

	block_wrapper.appendChild(stats_pie);
	block_wrapper.appendChild(detail_container);

	const	return_btn = document.createElement("button");
	return_btn.textContent = "Return";
	return_btn.id = "return-button";
	return_btn.classList.add ("btn", "btn-secondary");
	return_btn.addEventListener("click", () => {
		navigate_to("/profile");
	});
	container.appendChild(title);
	container.appendChild(block_wrapper);
	container.appendChild(return_btn);

	// chart
	function	render_chart(wins, losses) {
		const	ctx = document.getElementById("res-chart").getContext("2d");
		new Chart(ctx, {
			type: "pie",
			data: {
				labels: ["Wins", "Losses"],
				datasets: [{
					data: [wins, losses],
					backgroundColor: ["#d1e7e0", "#b41635"],
					hoverOffset: 4
				}]
			},
			options: {
				responsive: false,
				maintainAspectRatio: false
			}
		});
	}
	const	app = document.getElementById("app");
	if (!app) {
		console.error("Failed to load data");
		return (null);
	}
	app.textContent = "";
	app.appendChild(container);

	let	user;
	try {
		const	response = await fetch("/api/user-profil/", {credentials: "include"});
		if (!response.ok)
			throw new Error("Error fetching user data");
		console.log(response);
		const	data = await response.json();
		user = data.username;
	} catch (error) {
		console.error("Error fetching user profile data: ", error);
		return;
	}
	// display stats
	function	display_stats(stats) {
		total_game_span.innerText = stats.totalGames;
		win_span.innerText = stats.wins;
		loss_span.innerText = stats.losses;
	}
	// details aff games
	function	display_game_details(gamesTab) {

		tbody.textContent = "";
		gamesTab.forEach(detail => {
			const	row = document.createElement("tr");

			const	date = document.createElement("td");
			date.textContent = detail.datePlayed;
			row.appendChild(date);

			const	opponent = document.createElement("td");
			opponent.textContent = detail.opponentName;
			row.appendChild(opponent);

			const	user_points = document.createElement("td");
			user_points.textContent = detail.userPoints;
			row.appendChild(user_points);

			const	opp_points = document.createElement("td");
			opp_points.textContent = detail.opponentPoints;
			row.appendChild(opp_points);

			const	res = document.createElement("td");
			res.textContent = detail.result;
			row.appendChild(res);
			tbody.appendChild(row);
		});
	}
	try {
		const	game_reponse = await fetch("/api/match-history/", {credentials: "include"});
		if (!game_reponse.ok)
			throw new Error("Error fetching game data");
		const	games = await game_reponse.json();
		console.log(games);

		const	stats = {
			totalGames: games.length,
			wins: 0,
			losses: 0,
			opponents: new Set()
		};
		const	detailGames = [];
		games.forEach(game => {
			let opponent = "";
			let userPoints = 0;
			let opponentPoints = 0;
			let result = "";
			let gameDate = "";

			if (game.player1 === user && game.player2 != user) {
				opponent = game.player2;
				userPoints = game.player1_score;
				opponentPoints = game.player2_score;
			}
			else if (game.player2 === user && game.player1 != user) {
				opponent = game.player1;
				userPoints = game.player2_score;
				opponentPoints = game.player1_score;
			}
			else {
				opponent = "AI";
				userPoints = game.player1_score;
				opponentPoints = game.player2_score;
			}

			if (game.winner === user) {
				result = "Win";
				stats.wins++;
			}
			else {
				result = "Loss";
				stats.losses++;
			}
			if (opponent)
				stats.opponents.add(opponent);

			if (game.date)
				gameDate = new Date(game.date).toLocaleDateString();
			else
				game = "N/A";

			detailGames.push({
				datePlayed: gameDate,
				opponentName: opponent,
				userPoints: userPoints,
				opponentPoints: opponentPoints,
				result: result
			});
		});
		console.log(detailGames);
		stats.opponents = Array.from(stats.opponents);
		display_stats(stats);
		display_game_details(detailGames);
		render_chart(stats.wins, stats.losses);

	} catch (error) {
		console.error("Error fetching user data game: ", error);
	}
	return (container);
}
