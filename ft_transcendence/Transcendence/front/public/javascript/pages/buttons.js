import {create_button}
from './create_function.js'

function    toggle_button(event) {

    const   button = event.currentTarget;
    
    if (button.disabled) {
        button.disabled = false;
        button.style.display = 'inline-block';
    }
    else {
        button.disabled = true;
        button.style.display = 'none';
    }
}

export function create_home_button() {
    
    const   button = create_button({

        className: 'btn btn-home',
        type: 'button',
        text: 'Pong',
        data_toggle: 'collapse',
        data_target: '#multi_collapse',
        aria_expanded: 'true',
        aria_controls: '#multi_collapse',
    });
    button.addEventListener('click', toggle_button);
    return (button)
}    
