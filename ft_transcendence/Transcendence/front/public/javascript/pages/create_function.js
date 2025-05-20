export function	create_text(html) {

	const	p = document.createElement("p");
	p.innerHTML = html;

	return (p);
}

export function	create_img(src, alt, class_name) {

	const	image = document.createElement("img");
	image.src = src;
	image.alt = alt;
	image.className = class_name;

	return (image);
}

export function	create_elem_class(html, class_name) {

	const	elem = document.createElement(html);
	elem.className = class_name;

	return(elem);
}

export function	create_button({
	class_name,
	type,
	text,
	data_toggle,
	data_target,
	aria_expanded,
	aria_controls,
	href,
	font_size,
	padding,
	target,
}) {

	let	custom_button;

	if (href) {
		custom_button = document.createElement("a");
	}
	else {
		custom_button = document.createElement("button");
	}
	custom_button.className = class_name;
	custom_button.textContent = text;

	if (href) {

		custom_button.href = href;
		custom_button.target = target || '';
		if (font_size) {
			custom_button.style.fontSize = font_size;
		}
		if (padding) {
			custom_button.style.padding = padding;
		}
	}
	else {
		custom_button.type = type || "button";
		
		if (data_toggle) {
			custom_button.setAttribute("data-bs-toggle", data_toggle);
		}
		if (data_target) {
			custom_button.setAttribute("data-bs-target", data_target);
		}
		if (aria_controls) {
			custom_button.setAttribute("aria-controls", aria_controls);
		}
		if (aria_expanded != undefined) {
			custom_button.setAttribute("aria-expanded", aria_expanded);
		}
	}
	return (custom_button);
}
