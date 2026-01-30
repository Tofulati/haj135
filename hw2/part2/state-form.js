document.getElementById("form").addEventListener("submit", function (e) {
    e.preventDefault();

    const endpoint = document.getElementById("endpoint").value;
    const responseBox = document.getElementById("response");

    const data = {
        name: document.getElementById("name").value,
        message: document.getElementById("message").value
    }

    let url = endpoint;
    let options = {
        method: method,
        headers: {}
    };

    if (method === "GET") {
        url += "?" + new URLSearchParams(data).toString();
    } else {
        if (encoding === "application/json") {
            options.headers["Content-Type"] = "application/json";
            options.body = JSON.stringify(data);
        } else {
            options.headers["Content-Type"] = "application/x-www-form-urlencoded";
            options.body = new URLSearchParams(data).toString();
        }
    }

    fetch(url, options)
        .then(res => res.text())
        .then(text => {
            responseBox.textContent = text;
        })
        .catch(err => {
            responseBox.textContent = "Request Failed";
            console.log(err);
        });
});