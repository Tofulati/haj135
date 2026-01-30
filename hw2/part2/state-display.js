function getCookie(name) {
    const match = document.cookie.match(new RegExp('(^|;\\s*)' + name + '=([^;]*)'));
    return match ? decodeURIComponent(match[2]) : null;
}

const display = document.getElementById("cookie-display");
const clear_cookies_btn = document.getElementById("clear-cookies-btn");

const username = getCookie("username");
const message = getCookie("message");

clear_cookies_btn.hidden = true;

if (username && message) {
    display.innerHTML = `
    <h3>Name</h3>
    <p>${username}</p>
    <h3>Message</h3>
    <p>${message}</p>
    `;

    clear_cookies_btn.hidden = false;

    clear_cookies_btn.addEventListener("click", function () {
        
        document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
        document.cookie = "message=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";

        // Reload the page to update the UI
        location.reload();
    });

} else {
    display.innerHTML = `
    <h3>Cookies Not Found</h3>
    <p>Set cookies with <a href="/hw2/part2/state-form.html">State Form</a></p>
    `;
}