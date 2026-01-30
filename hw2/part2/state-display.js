function getCookie(name) {
    // The regular expression looks for the cookie name with optional leading 
    // characters and a semicolon or end of string as a boundary.
    const match = document.cookie.match(new RegExp('(^|;\\s*)' + name + '=([^;]*)'));
    return match ? decodeURIComponent(match[2]) : null;
}

const display = document.getElementById("cookie-display");
const clear_cookies_btn = document.getElementById("clear-cookies-btn")
const username = getCookie("name");
const message = getCookie("message");

clear_cookies_btn.hidden = true;

// Display cookies if set
if (username && message) {
    display.innerHTML = `
    <h3>Name</h3>
    <p>${username}</p>
    <h3>Message</h3>
    <p>${message}</p>
    `;

    clear_cookies_btn.hidden = false;
    clear_cookies_btn.addEventListener("submit", function (e) {
        e.preventDefault();

    });
} else {
    display.innerHTML = `
    <h3>Cookies Not Found</h3>
    <p>Set cookies with <a href="/hw2/part2/state-form.html">State Form</a></p>
    `;
}