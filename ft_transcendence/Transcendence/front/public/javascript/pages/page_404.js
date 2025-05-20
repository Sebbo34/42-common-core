export function render_404() {

    const   container = document.createElement("div");
    container.className = "page-404";

    const   text = document.createElement("div");
    text.className = "message";
    text.textContent = "404: Spooky times ahead but no content here";

    const   ghost = document.createElement("div");
    ghost.className = "ghost";

    const   face = document.createElement("div");
    face.className = "face";

    const   arms = document.createElement("div");
    arms.className = "arms";

    const   bottom = document.createElement("div");
    bottom.className = "bottom";

    ghost.appendChild(face);
    ghost.appendChild(arms);
    ghost.appendChild(bottom);

    const   content = document.createElement("div");
    content.className = "content-container";

    content.appendChild(text);
    content.appendChild(ghost);

    container.appendChild(content);
    return (container);
}
