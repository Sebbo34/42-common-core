export function render_footer() {

    const   footer = document.createElement("footer");
    const   footer_content = document.createElement("div");

    footer_content.classList.add("footer-content");

    const   footer_title = document.createElement("p");

    footer_title.classList.add("footer-title");
    footer_title.textContent = "🏓 ft_transcendence by csy, sgandum-, sbo & dcriouet 🏓";

    footer_content.appendChild(footer_title);
    footer.appendChild(footer_content);

    document.body.appendChild(footer);
}
